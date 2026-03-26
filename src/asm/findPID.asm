include tlhelp32.inc
include dynload.inc

.data
    hSnapshot dq ?
    processName dq ?
    pe PROCESSENTRY32 <>
    dllName db "kernel32.dll", 0
    hModule dq ?
    proc32First db "Process32First", 0
    proc32Next db "Process32Next", 0
    proc32Snapshot db "CreateToolhelp32Snapshot", 0
    Process32FirstPtr dq ?
    Process32NextPtr dq ?
    CreateToolhelp32SnapshotPtr dq ?

.code
PUBLIC findPID

findPID PROC
    push rsi
    sub rsp, 20h

    mov processName, rcx

    mov pe.dwSize, SIZEOF PROCESSENTRY32

    mov rcx, offset dllName
    call LoadLibraryA
    test rax, rax
    jz zeroEAX
    mov hModule, rax 

    mov rcx, hModule
    mov rdx, offset proc32Snapshot
    call GetProcAddress
    mov CreateToolhelp32SnapshotPtr, rax

    mov ecx, TH32CS_SNAPPROCESS
    xor edx, edx
    call CreateToolhelp32SnapshotPtr
    mov hSnapshot, rax

    mov rcx, hModule
    mov rdx, offset proc32First
    call GetProcAddress
    mov Process32FirstPtr, rax

    mov rcx, hSnapshot
    lea rdx, pe
    call Process32FirstPtr
    test eax, eax
    jz zeroEAX

    mov rcx, hModule
    mov rdx, offset proc32Next
    call GetProcAddress
    mov Process32NextPtr, rax

startLoop:
    lea r10, pe.szExeFile
    mov rsi, processName

compareLoop:
    mov al, byte ptr [r10]
    cmp al, byte ptr [rsi]
    jne nextProcess

    test al, al
    je found

    inc r10
    inc rsi
jmp compareLoop

nextProcess:
    mov rcx, hSnapshot
    lea rdx, pe
    call Process32NextPtr
    test rax, rax
    jz zeroEAX
jmp startLoop

found:
    mov eax, pe.th32ProcessID
    jmp finish

zeroEAX:
    xor eax, eax
    
finish:
    add rsp, 20h
    pop rsi
    ret
findPID ENDP
END