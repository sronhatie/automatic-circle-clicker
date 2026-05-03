#ifndef RELAXLOGIC_H
#define RELAXLOGIC_H

int isSlider(HANDLE hProcess, uintptr_t hitObjectPtr);
int handleCircle(HANDLE hProcess, uintptr_t drawablePtr, double currentTime, double *outStartTime);
int handleSlider(HANDLE hProcess, uintptr_t drawablePtr, double currentTime, double *outStartTime);

void runRelax(HANDLE hProcess, uintptr_t osuGamePtr);

#endif