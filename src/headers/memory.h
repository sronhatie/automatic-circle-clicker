#ifndef MEMORY_H
#define MEMORY_H

#include <windows.h>

uintptr_t readPtr(HANDLE hProcess, uintptr_t address);
BYTE readByte(HANDLE hProcess, uintptr_t address);
int readInt(HANDLE hProcess, uintptr_t address);
double readDouble(HANDLE hProcess, uintptr_t address);

#endif