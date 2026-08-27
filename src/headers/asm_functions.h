#pragma once

#include <windows.h>
#include <stdint.h>

extern void mouseDown();
extern void mouseUp();
extern void moveMouse(int x, int y);
extern DWORD findPID(char *process_name);
extern int isExecutablePage(DWORD protect);
extern int memCmpWildcard(unsigned char *buffer, unsigned char *signature,
                          char *mask);
extern int writeOneByte(HANDLE process_handle, uintptr_t address, BYTE value);
