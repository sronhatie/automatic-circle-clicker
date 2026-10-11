#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "hook.h"
#include "osu_process.h"
#include "signatures.h"

extern int isExecutablePage(DWORD protect);
extern int memCmpWildcard(unsigned char *buffer, unsigned char *signature,
                          char *mask);
extern unsigned char hook_stub[];
extern unsigned char hook_stub_end[];

#define STOLEN_BYTES_SIZE 17
#define ABSOLUTE_JUMP_SIZE 14

const unsigned char jump_bytes[6] = {0xFF, 0x25, 0x00, 0x00, 0x00, 0x00};

uintptr_t get_osu_game_desktop_ptr(void) {
  uintptr_t target =
      find_pattern(osu_process.process_handle, update_after_children_signature,
                   update_after_children_mask);

  if (target == 0) {
    return 0;
  }

  unsigned char original_bytes[STOLEN_BYTES_SIZE];
  SIZE_T bytes_read = 0;
  if (!ReadProcessMemory(osu_process.process_handle, (LPCVOID)target,
                         original_bytes, STOLEN_BYTES_SIZE, &bytes_read)) {
    return 0;
  }

  if (bytes_read != STOLEN_BYTES_SIZE) {
    return 0;
  }

  // allocates bytes inside osu
  // we use uintptr_t for pointer arithmetics
  uintptr_t remote_memory = (uintptr_t)VirtualAllocEx(
      osu_process.process_handle, NULL,
      0x1000, // allocates 4096 bytes. a lot more than we need. will need to
              // figure out smth
      MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

  if (remote_memory == 0) {
    return 0;
  }

  // where OsuGame pointer will be
  uintptr_t captured_ptr_address = remote_memory;
  // where the original 17 bytes will be
  uintptr_t original_bytes_address = remote_memory + sizeof(uintptr_t);
  // where the original address will be
  uintptr_t target_address = original_bytes_address + STOLEN_BYTES_SIZE;
  // the rest of the bytes are for hook_stub assembly code
  uintptr_t stub_address = target_address + sizeof(uintptr_t);

  // write the 17 bytes inside the osu memory we allocated.
  // so our asm program can use it to restore them.
  if (!WriteProcessMemory(osu_process.process_handle,
                          (LPVOID)original_bytes_address, original_bytes,
                          STOLEN_BYTES_SIZE, NULL)) {
    return 0;
  }

  // write the address of original UpdateAfterChildren
  // so asm knows where to restore the original instructions
  if (!WriteProcessMemory(osu_process.process_handle, (LPVOID)target_address,
                          &target, sizeof(target), NULL)) {
    return 0;
  }

  SIZE_T stub_size = (SIZE_T)((uintptr_t)hook_stub_end - (uintptr_t)hook_stub);

  if (stub_size == 0) {
    return 0;
  }

  // write the assembly code inside osu. so osu can execute our code.
  SIZE_T bytes_written = 0;
  if (!WriteProcessMemory(osu_process.process_handle, (LPVOID)stub_address,
                          hook_stub, stub_size, &bytes_written)) {
    return 0;
  }

  if (bytes_written != stub_size) {
    return 0;
  }

  // the cpu cant detect the change we made, so we flush it.
  // otherwise it might still use the original osu code.
  FlushInstructionCache(osu_process.process_handle, (LPCVOID)stub_address,
                        stub_size);

  // constructs an array containing jump opcode bytes and destination address
  // bytes basically JMP [some_address]
  unsigned char jump[ABSOLUTE_JUMP_SIZE];
  memcpy(jump, jump_bytes, sizeof(jump_bytes));
  memcpy(jump + sizeof(jump_bytes), &stub_address, sizeof(stub_address));

  // constructs an array jump opcode + destination address the rest NOP bytes to
  // fill 17 BYTES
  unsigned char patch[STOLEN_BYTES_SIZE];
  memset(patch, 0x90, sizeof(patch));
  memcpy(patch, jump, ABSOLUTE_JUMP_SIZE);

  // change memory protection so code can be modified
  DWORD old_protect = 0;
  if (!VirtualProtectEx(osu_process.process_handle, (LPVOID)target,
                        STOLEN_BYTES_SIZE, PAGE_EXECUTE_READWRITE,
                        &old_protect)) {
    return 0;
  }

  // writes the hook.
  // makes UpdateAfterChildren jump to our hook_stub
  SIZE_T patch_bytes_written = 0;
  if (!WriteProcessMemory(osu_process.process_handle, (LPVOID)target, patch,
                          STOLEN_BYTES_SIZE, &patch_bytes_written)) {
    return 0;
  }

  if (patch_bytes_written != STOLEN_BYTES_SIZE) {
    return 0;
  }

  // modofied osu code, so have to flush, otherwise it might run original osu
  // code instead of our own. i dont know, microsoft reccommends it
  // Applications should call FlushInstructionCache if they generate or modify
  // code in memory. The CPU cannot detect the change, and may execute the old
  // code it cached.
  FlushInstructionCache(osu_process.process_handle, (LPCVOID)target,
                        STOLEN_BYTES_SIZE);

  // wait until the assembly code changes captured_ptr_address to the pointer
  uintptr_t osu_game_desktop_ptr = 0;
  while (osu_game_desktop_ptr == 0) {
    if (!ReadProcessMemory(osu_process.process_handle,
                           (LPCVOID)captured_ptr_address, &osu_game_desktop_ptr,
                           sizeof(osu_game_desktop_ptr), NULL)) {
      return 0;
    }
    Sleep(1);
  }

  // change the page protection back to what it was
  DWORD unused_protect;
  if (!VirtualProtectEx(osu_process.process_handle, (LPVOID)target,
                        STOLEN_BYTES_SIZE, old_protect, &unused_protect)) {
    return 0;
  }

  // flush it after changing osu code
  FlushInstructionCache(osu_process.process_handle, (LPCVOID)target,
                        STOLEN_BYTES_SIZE);

  return osu_game_desktop_ptr;
}

uintptr_t find_pattern(HANDLE process_handle, unsigned char *signature,
                       char *mask) {
  // TODO: check for bad inputs
  MEMORY_BASIC_INFORMATION mbi;
  uintptr_t address = 0;
  size_t signature_length = strlen(mask);

  // scans the memory in 1MB chunks
  const SIZE_T chunk_size = 1024 * 1024;
  unsigned char *buffer = malloc(chunk_size);
  // TODO: check if it fails

  // checks what memory region exists and fills mbi
  // the loop ends once it reaches the end (sizeof(mbi))
  while ((VirtualQueryEx(process_handle, (LPCVOID)address, &mbi,
                         sizeof(mbi))) == sizeof(mbi)) {
    // only scans memory that is usable and is executable
    if (mbi.State == MEM_COMMIT && isExecutablePage(mbi.Protect)) {
      uintptr_t regionBase = (uintptr_t)mbi.BaseAddress;
      SIZE_T region_size = mbi.RegionSize;
      SIZE_T region_offset = 0;

      while (region_offset < region_size) {
        SIZE_T to_read = chunk_size;
        // if theres less than 1MB left it only reads the remaining amount
        if (region_offset + to_read > region_size) {
          to_read = region_size - region_offset;
        }

        SIZE_T bytes_read = 0;
        ReadProcessMemory(process_handle, (LPCVOID)(regionBase + region_offset),
                          buffer, to_read, &bytes_read);
        // TODO: skip chunk if fails

        // if our signature_length was 5 and we read 4 bytes thats bad.
        if (bytes_read >= signature_length) {
          // defines all starting positions. so for the example above it would
          // be 0 and 1. 2 and above is bad as it would overflow to 6
          for (SIZE_T i = 0; i <= bytes_read - signature_length; ++i) {
            if (memCmpWildcard(buffer + i, signature, mask)) {
              free(buffer);
              return regionBase + region_offset + i;
            }
          }
        }

        // if to_read is too small, the movement is too small to be useful (or
        // could become negative)
        if (to_read <= signature_length) {
          break;
        }

        // since regions can split the signature, we overlap the signatures by
        // (signature_length - 1)
        region_offset += to_read - (signature_length - 1);
      }
    }

    // goes to the next region (for VirtualQueryEx())
    address = (uintptr_t)mbi.BaseAddress + mbi.RegionSize;
  }

  free(buffer);
  // did not get the address so return 0
  return 0;
}

/*
uintptr_t get_osu_game_desktop_ptr(void) {
  uintptr_t update_after_children_addr = find_pattern_in_process(
      osu_process.process_handle, update_after_children_signature,
      update_after_children_mask);

  BYTE original_byte = 0;

  ReadProcessMemory(osu_process.process_handle,
                    (LPCVOID)update_after_children_addr, &original_byte, 1,
                    NULL);

  DebugActiveProcess(osu_process.process_id);

  // TODO: Check if this fails. It silently fails if another debugger
  // is already attached to the process.
  DebugSetProcessKillOnExit(FALSE);

  // Removes the initial attach breakpoint (0xCC / int3).
  wait_for_initial_attach_breakpoint();

  writeOneByte(osu_process.process_handle, update_after_children_addr, 0xCC);

  // RCX contains OsuGameDesktop* at UpdateAfterChildren.
  uintptr_t osu_game_desktop_ptr = capture_breakpoint_rcx(
      osu_process.process_handle, update_after_children_addr, original_byte);

  DebugActiveProcessStop(osu_process.process_id);

  return osu_game_desktop_ptr;
}
*/
