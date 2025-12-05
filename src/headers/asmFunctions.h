#ifndef ASMFUNCTIONS_H
#define ASMFUNCTIONS_H

typedef struct{
    int x;
    int y;
    int objectTime;
    int objectType;
} HitObject;

extern HitObject *ParseOsuFile();
extern void ClickMouse();
extern void MoveCursor(int x, int y);
extern void Wait(int ms);

#endif