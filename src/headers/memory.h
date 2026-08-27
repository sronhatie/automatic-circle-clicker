#pragma once

#include <windows.h>
#include <stdint.h>

uintptr_t read_ptr(HANDLE process_handle, uintptr_t address);
BYTE read_byte(HANDLE process_handle, uintptr_t address);
int read_int(HANDLE process_handle, uintptr_t address);
double read_double(HANDLE process_handle, uintptr_t address);
