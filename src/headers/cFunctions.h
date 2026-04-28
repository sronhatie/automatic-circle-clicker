#ifndef CFUNCTIONS_H
#define CFUNCTIONS_H

int keyWasPressed();
uintptr_t findPatternInProcess(HANDLE hProcess, unsigned char *signature, char *mask);
void closeDebugEventHandles(DEBUG_EVENT *debugEvent);
int waitForInitialAttachBreakpoint();
uintptr_t captureBreakpointRCX(HANDLE hProcess, uintptr_t bpAddr, BYTE originalByte);
int findPlayingStateValue(HANDLE hProcess, uintptr_t osuGamePtr);

#endif