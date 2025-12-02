INPUT_MOUSE EQU 0
MOUSEEVENTF_LEFTDOWN EQU 02h

EXTERN LoadLibraryA:PROC
EXTERN GetProcAddress:PROC

.data
    dllName db "User32.dll", 0
    procName db "SendInput", 0
    hModule dq ?
    SendInputPtr dq ?


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

.code
PUBLIC ClickMouse

ClickMouse PROC
    ; since we'll call a WINAPI function, we need to reserve 32bytes shadow space
    ; we also have to align the stack by 8 bytes because the C CALL pushes the 8byte return address (RAX)
    SUB RSP, 28h ; 32(shadow space) + 8(misalignment)

    ; RCX RDX R8 R9 return value RAX
    MOV RCX, offset dllName
    CALL LoadLibraryA
    MOV hModule, RAX

    MOV RCX, hModule
    MOV RDX, offset procName
    CALL GetProcAddress
    MOV SendInputPtr, RAX

    
    ADD RSP, 28h ; remove shadowspace and alignment
    RET
ClickMouse ENDP
END