INPUT_MOUSE EQU 0
MOUSEEVENTF_LEFTDOWN EQU 02h

EXTERN LoadLibraryA:PROC
EXTERN GetProcAddress:PROC

.data
    dllName db "User32.dll", 0
    procName db "SendInput", 0
    hModule dq ?


MOUSEINPUT STRUCT 
    myDx DWORD ?
    dy DWORD ?
    mouseData DWORD ?
    dwFlags DWORD ?
    time DWORD ?
    dwExtraInfo QWORD ?
MOUSEINPUT ENDS

INPUT STRUCT
    myType DWORD ?
    mi MOUSEINPUT <> ; zero outs the structure
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

.code
PUBLIC ClickMouse

ClickMouse PROC
    ; since we'll call a WINAPI function, we need to reserve 32bytes shadow space
    ; we also have to align the stack by 8 bytes because the C CALL pushes the 8byte return address (RAX)
    SUB RSP, 28h ; 32(shadow space) + 8(misalignment)


    ADD RSP, 28h ; remove shadowspace and alignment
ClickMouse ENDP
END