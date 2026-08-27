#include <windows.h>

#include <memory.h>

uintptr_t read_ptr(HANDLE process_handle, uintptr_t address) {
  uintptr_t value = 0;
  ReadProcessMemory(process_handle, (LPCVOID)address, &value, sizeof(value), NULL);
  return value;
}

BYTE read_byte(HANDLE process_handle, uintptr_t address) {
  BYTE value = 0;
  ReadProcessMemory(process_handle, (LPCVOID)address, &value, sizeof(value), NULL);
  return value;
}

int read_int(HANDLE process_handle, uintptr_t address) {
  int value = 0;
  ReadProcessMemory(process_handle, (LPCVOID)address, &value, sizeof(value), NULL);
  return value;
}

double read_double(HANDLE process_handle, uintptr_t address) {
  double value = 0;
  ReadProcessMemory(process_handle, (LPCVOID)address, &value, sizeof(value), NULL);
  return value;
}
