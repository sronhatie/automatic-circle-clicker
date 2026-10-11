.code
PUBLIC hook_stub
PUBLIC hook_stub_end

hook_stub PROC

    ; get our current runtime address.
    ; CALL is 5 bytes, so R11 becomes stub_address + 5.
    call get_rip

get_rip:
    pop r11

    ; 5 bytes for CALL + 33 bytes of data before the stub.
    ; R11 = remote_memory
    sub r11, 38

    ; get UpdateAfterChildren address.
    mov r10, [r11 + 25]

    ; restore the original 17 bytes.
    mov rax, [r11 + 8]
    mov [r10], rax

    mov rax, [r11 + 16]
    mov [r10 + 8], rax

    mov al, [r11 + 24]
    mov [r10 + 16], al

    ; signal that we've finished restoring
    mov [r11], rcx

    ; restart UpdateAfterChildren normally.
    jmp r10

hook_stub ENDP
; we need to know the end address to calculate stub_size
hook_stub_end LABEL BYTE

END