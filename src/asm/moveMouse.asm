; i only need to resolve the SendInputPtr only once. so yes wasteful '

include wininput.inc
include dynload.inc

.data
    dllName db "User32.dll", 0
    procName db "SendInput", 0
    hModule dq ?
    SendInputPtr dq ?

.code
PUBLIC moveMouse

moveMouse PROC
    push r12
    push r13

    sub rsp, 28h
    
    mov r12d, ecx ; rcx = x
    mov r13d, edx ; rdx = y
    
    mov rcx, offset dllName
    call LoadLibraryA
    mov hModule, rax

    mov rcx, hModule
    mov rdx, offset procName
    call GetProcAddress
    mov SendInputPtr, rax

    sub rsp, sizeof INPUT
    sub rsp, 08h

    mov [rsp].INPUT.myType, 0
    mov [rsp].INPUT.mi.mouseData, 0
    mov [rsp].INPUT.mi.time, 0
    mov [rsp].INPUT.mi.padding, 0
    mov qword ptr [rsp].INPUT.mi.dwExtraInfo, 0

    mov [rsp].INPUT.myType, INPUT_MOUSE
    mov [rsp].INPUT.mi.myDx, r12d
    mov [rsp].INPUT.mi.dy, r13d
    mov eax, MOUSEEVENTF_MOVE
    or eax, MOUSEEVENTF_ABSOLUTE
    mov [rsp].INPUT.mi.dwFlags, eax

    mov rcx, 1
    lea rdx, [rsp].INPUT
    mov r8, sizeof INPUT
    call SendInputPtr

    add rsp, sizeof INPUT
    add rsp, 08h
    add rsp, 28h
    pop r13
    pop r12
moveMouse ENDP
END