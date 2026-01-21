INPUT_MOUSE EQU 0
MOUSEEVENTF_MOVE equ 01h
MOUSEEVENTF_LEFTDOWN EQU 02h
MOUSEEVENTF_ABSOLUTE equ 8000h

EXTERN LoadLibraryA:PROC
EXTERN GetProcAddress:PROC

MOUSEINPUT STRUCT 
    myDx DWORD ? ; 0-4
    dy DWORD ? ; 4-8
    mouseData DWORD ? ; 8-12
    dwFlags DWORD ? ; 12-16
    time DWORD ? ; 16-20
    padding DWORD ?; padding 20-24
    dwExtraInfo QWORD ? ; 24-32
MOUSEINPUT ENDS

INPUT STRUCT
    myType DWORD ? ; 0-4
    padding DWORD ?; padding 4-8
    mi MOUSEINPUT <> ; zero outs the structure 8-40
INPUT ENDS

; this is the full struc but we'll only use mouseinput so no need to overcomplicate it.
;typedef struct tagINPUT {
;  DWORD type;
;  union {
;    MOUSEINPUT    mi;
;    KEYBDINPUT    ki;
;    HARDWAREINPUT hi;
;  } DUMMYUNIONNAME;
;} INPUT, *PINPUT, *LPINPUT;