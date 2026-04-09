include dynload.inc
include memory.inc

.data
    dllName db "Kernel32.dll", 0
    hModule dq ?

    vpName db "VirtualProtectEx", 0
    wpmName db "WriteProcessMemory", 0
    ficName db "FlushInstructionCache", 0
    VirtualProtectExPtr dq ?
    WriteProcessMemoryPtr dq ?
    FlushInstructionCachePtr dq ?

.code
PUBLIC writeOneByte

writeOneByte PROC
    ; rcx hProcess, rdx breakpointAddress, r8 value
    push r12
    push r13
    push r14

    mov r12, rcx
    mov r13, rdx
    mov r14b, r8b
    
    sub rsp, 40h ; shadow + misalignment + 5th arg to rsp + locals

    mov rcx, offset dllName
    call LoadLibraryA
    mov hModule, rax

    mov rcx, hModule
    mov rdx, offset vpName
    call GetProcAddress
    mov VirtualProtectExPtr, rax

    mov rcx, hModule
    mov rdx, offset wpmName
    call GetProcAddress
    mov WriteProcessMemoryPtr, rax

    mov rcx, hModule
    mov rdx, offset ficName
    call GetProcAddress
    mov FlushInstructionCachePtr, rax

    ; [rsp + 20h] 5th arg
    ; [rsp + 28h] oldProtect DWORD
    ; [rsp + 30h] tempProtect DWORD
    ; [rsp + 34h] &value

    mov byte ptr [rsp + 34h], r14b

    ; VirtualProtectEx(hProcess, addr, 1, PAGE_EXECUTE_READWRITE, &oldProtect)
    mov rcx, r12
    mov rdx, r13
    mov r8d, 1
    mov r9d, PAGE_EXECUTE_READWRITE
    lea rax, [rsp + 28h]
    mov qword ptr [rsp + 20h], rax
    call VirtualProtectExPtr

    ; WriteProcessMemory(hProcess, addr, &value, 1, NULL)
    mov rcx, r12
    mov rdx, r13
    lea r8, [rsp + 34h]
    mov r9d, 1
    mov qword ptr [rsp + 20h], 0
    call WriteProcessMemoryPtr

    ; FlushInstructionCache(hProcess, addr, 1)
    mov rcx, r12
    mov rdx, r13
    mov r8d, 1
    call FlushInstructionCachePtr

    ; VirtualProtectEx(hProcess, addr, 1, oldProtect, &tempProtect)
    mov rcx, r12
    mov rdx, r13
    mov r8d, 1
    mov r9d, dword ptr [rsp + 28h]
    lea rax, [rsp + 30h]
    mov qword ptr [rsp + 20h], rax
    call VirtualProtectExPtr

    mov eax, 1

    add rsp, 40h
    pop r14
    pop r13
    pop r12
    ret
writeOneByte ENDP
END