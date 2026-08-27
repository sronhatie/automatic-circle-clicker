#pragma once

#include <windows.h>
#include <stdint.h>

uintptr_t find_pattern_in_process(HANDLE process_handle, unsigned char *signature, char *mask);
void closeDebugEventHandles(DEBUG_EVENT *debugEvent);
int wait_for_initial_attach_breakpoint();
uintptr_t capture_breakpoint_rcx(HANDLE process_handle, uintptr_t bpAddr, BYTE originalByte);
