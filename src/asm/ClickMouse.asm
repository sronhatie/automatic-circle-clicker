INPUT_MOUSE EQU 0
MOUSEEVENTF_LEFTDOWN EQU 02h

EXTERN LoadLibraryA:PROC
EXTERN GetProcAddress:PROC

.data
    dllName db "User32.dll", 0
    procName db "SendInput", 0
    hModule dq ?

.code
PUBLIC ClickMouse

ClickMouse PROC
    ; since we'll call a WINAPI function, we need to reserve 32bytes shadow space
    ; we also have to align the stack by 8 bytes because the compiler takes away 8 bytes for the return RAX register :( 
    SUB RSP, 28h ; 32(shadow space) + 8(misalignment)


    ADD RSP, 28h ; remove shadowspace and alignment
ClickMouse ENDP
END