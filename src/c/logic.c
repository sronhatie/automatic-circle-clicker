#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#include <logic.h>
#include "asm_functions.h"
#include "osu_chain.h"
#include "relax_logic.h"

void start() {
  char *process_name = "osu!.exe";
  DWORD process_id = findPID(process_name);
  if (!process_id) {
    printf("Osu not open\n");
    return;
  }

  // OPERATION allows to change memory pages, INFORMATION gets info about the
  // process
  HANDLE process_handle =
      OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION |
                      PROCESS_QUERY_INFORMATION,
                  FALSE, process_id);
  uintptr_t osu_game_desktop_ptr = get_osu_game_desktop_ptr(process_handle, process_id);

  // currently this just prints out the OsuGame pointer so i know if the program
  // is running (otherwise it silently crashes)
  printf("OsuGame ptr = %p\n", (void *)osu_game_desktop_ptr);

  while (1) {
    run_relax(process_handle, osu_game_desktop_ptr);

    Sleep(10);
  }
}
