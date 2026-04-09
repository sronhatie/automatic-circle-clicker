#ifndef ASMFUNCTIONS_H
#define ASMFUNCTIONS_H

typedef struct{
    int x;
    int y;
    int objectTime;
    int objectType;
} HitObject;

extern HitObject *parseOsuFile();
extern void mouseDown();
extern void mouseUp();
extern void moveMouse(int x, int y);
extern DWORD findPID(char *processName);
extern int isExecutablePage(DWORD protect);
extern int memCmpWildcard(unsigned char *buffer, unsigned char *signature, char *mask);
extern int writeOneByte(HANDLE hProcess, uintptr_t address, BYTE value);

#endif