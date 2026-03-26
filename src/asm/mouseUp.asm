; AAAAA the other values in the INPUT struct arent zeroed out so uh fix that someday.
; also i only need to resolve the SendInputPtr only once. so yes wasteful 

INCLUDE wininput.inc

.data
    dllName db "User32.dll", 0
    procName db "SendInput", 0
    hModule dq ?
    SendInputPtr dq ?

.code
PUBLIC mouseUp

mouseUp PROC
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

    SUB RSP, SIZEOF INPUT ; allocate space for INPUT struct will be 28h (40) that means its not 16byte aligned
    SUB RSP, 08h ; aligns the stack before CALL
    MOV [RSP].INPUT.myType, INPUT_MOUSE
    MOV [RSP].INPUT.mi.dwFlags, MOUSEEVENTF_LEFTUP

    MOV RCX, 1
    ; using MOV RDX, [RSP].INPUT wont work
    LEA RDX, [RSP].INPUT ; start of INPUT struct 
    MOV R8, SIZEOF INPUT
    CALL SendInputPtr

    ADD RSP, 08h
    ADD RSP, SIZEOF INPUT ; remove space for INPUT struct
    ADD RSP, 28h ; remove shadowspace and alignment
    RET
mouseUp ENDP
END