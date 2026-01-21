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
extern void moveMouse(int x, int y);

#endif