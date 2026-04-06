.code
PUBLIC memCmpWildcard

memCmpWildcard PROC
    ; rcx *buffer, rdx *signature, r8 *mask
    xor r9, r9

loopStart:
    mov al, byte ptr [r8 + r9] ; al = mask[i]
    test al, al
    je matchFound

    cmp al, 'x'
    jne nextByte

    mov al, byte ptr [rcx + r9] ; buffer[i]
    cmp al, byte ptr [rdx + r9] ; cmp buffer[i], signature[i]
    jne noMatch

nextByte:
    inc r9
jmp loopStart

noMatch:
    xor eax, eax
    ret

matchFound:
    mov eax, 1
    ret
memCmpWildcard ENDP
END