#ifndef DEBUGGING_H
#define DEBUGGING_H

uintptr_t findPatternInProcess(HANDLE hProcess, unsigned char *signature, char *mask);
void closeDebugEventHandles(DEBUG_EVENT *debugEvent);
int waitForInitialAttachBreakpoint();
uintptr_t captureBreakpointRCX(HANDLE hProcess, uintptr_t bpAddr, BYTE originalByte);
uintptr_t getOsuGamePtr(HANDLE hProcess, DWORD processID);

#endif