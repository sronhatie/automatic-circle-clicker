PUBLIC ClickMouse

; the random hex numbers are actual BIT flags that Windows checks. so like dont change them
INPUT_MOUSE EQU 0
MOUSEEVENTF_LEFTDOWN EQU 0x02
MOUSEEVENTF_LEFTUP EQU 0x04
INPUT_SIZE EQU 40 ; sizeof(INPUT) on x64

; from kernel32.dll (because its always loaded)
EXTERN LoadLibraryA:QWORD ; loads a DLL at runtime manually
EXTERN GetProcAddress:QWORD ; gets the address of a function inside that DLL
; QWORD because it tells MASM that its 64bits

.data
    dllName db "user32.dll", 0 ; handles input devices, windows, UI events
    procName db "SendInput", 0 ; API for simulating mouse buttons

.code

PROC ClickMouse
    PUSH RBX ; got to preserve nonvolatile

    ; load user32.dll
    LEA RCX, [REL dllName] ; RCX pointer to dllName (user32.dll)
    CALL LoadLibraryA ; returns module handle (hModule) in RAX
    MOV RBX, RAX ; store hModule in RBX

    POP RBX
    RET
ClickMouse ENDP

END