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

    ; requires to be set before calling Process32First
    mov pe.dwSize, SIZEOF PROCESSENTRY32

    mov rcx, offset dllName
    call LoadLibraryA
    test rax, rax
    jz zeroEAX
    mov hModule, rax 

    mov rcx, hModule
    mov rdx, offset proc32Snapshot
    call GetProcAddress
; TODO: check if failed or not
    mov CreateToolhelp32SnapshotPtr, rax

    mov ecx, TH32CS_SNAPPROCESS
    xor edx, edx ; 0 means show all processes 
    call CreateToolhelp32SnapshotPtr
; TODO: check if it failed or not
; it returns INVALID_HANDLE_VALUE if it fails
    mov hSnapshot, rax ; hSnapshot now holds a snapshot of all processes

    mov rcx, hModule
    mov rdx, offset proc32First
    call GetProcAddress
; TODO: check if failed or not
    mov Process32FirstPtr, rax

    mov rcx, hSnapshot
    lea rdx, pe
    call Process32FirstPtr ; gets the first process on the list and fills it in pe
    test eax, eax
    jz zeroEAX

    mov rcx, hModule
    mov rdx, offset proc32Next
    call GetProcAddress
; TODO: check if failed or not
    mov Process32NextPtr, rax

startLoop:
    lea r10, pe.szExeFile ; holds the current process name
    mov rsi, processName ; holds the process name we need

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
; TODO: CLOSE THE HANDLE OF hSnapshot
    add rsp, 20h
    pop rsi
    ret
findPID ENDP
END