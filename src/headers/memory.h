#pragma once

#include <stdint.h>
#include <windows.h>

uintptr_t read_ptr(uintptr_t address);
BYTE read_byte(uintptr_t address);
int read_int(uintptr_t address);
double read_double(uintptr_t address);
