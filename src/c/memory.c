#include <windows.h>

#include "memory.h"
#include "osu_process.h"

uintptr_t read_ptr(uintptr_t address) {
  uintptr_t value = 0;
  ReadProcessMemory(osu_process.process_handle, (LPCVOID)address, &value, sizeof(value), NULL);
  return value;
}

BYTE read_byte(uintptr_t address) {
  BYTE value = 0;
  ReadProcessMemory(osu_process.process_handle, (LPCVOID)address, &value, sizeof(value), NULL);
  return value;
}

int read_int(uintptr_t address) {
  int value = 0;
  ReadProcessMemory(osu_process.process_handle, (LPCVOID)address, &value, sizeof(value), NULL);
  return value;
}

double read_double(uintptr_t address) {
  double value = 0;
  ReadProcessMemory(osu_process.process_handle, (LPCVOID)address, &value, sizeof(value), NULL);
  return value;
}
