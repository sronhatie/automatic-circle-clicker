include memory.inc

.code
PUBLIC isExecutablePage

isExecutablePage PROC
    test ecx, PAGE_GUARD
    jnz notExecutable
    test ecx, PAGE_NOACCESS
    jnz notExecutable

    and ecx, 0FFh

    cmp ecx, PAGE_EXECUTE
    je isExecutable
    cmp ecx, PAGE_EXECUTE_READ
    je isExecutable
    cmp ecx, PAGE_EXECUTE_READWRITE
    je isExecutable
    cmp ecx, PAGE_EXECUTE_WRITECOPY
    je isExecutable

notExecutable:
    xor eax, eax
    ret

isExecutable:
    mov eax, 1
    ret

isExecutablePage ENDP
END