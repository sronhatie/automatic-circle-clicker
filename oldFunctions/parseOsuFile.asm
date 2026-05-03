INCLUDE parseOsuFile.inc

.data
    lpFileName db "Kry.exe - Rift Walker (Ryuusei Aika) [Easy].osu", 0
    fileHandle dq ?
    fileSize dd ?
    fileBuffer dq ?
    bytesRead dd ?
    startOfHitObject dq ?
    ptrHitObject dq ?

PUBLIC parseOsuFile
.code

parseOsuFile PROC
    SUB RSP, 38h ; shadows space, fix alignment, will need 3 args in stack for call

    ; CreateFileA ======================================
    MOV RCX, offset lpFileName
    MOV RDX, GENERIC_READ
    MOV R8, FILE_SHARE_READ
    MOV R9, NULL
    MOV DWORD PTR [RSP + 20h], OPEN_EXISTING
    MOV DWORD PTR [RSP + 28h], FILE_ATTRIBUTE_NORMAL
    MOV QWORD PTR [RSP + 30h], NULL
    CALL CreateFileA
    CMP RAX, INVALID_HANDLE_VALUE
    JE ifBadHandle

    MOV fileHandle, RAX
    JMP ifGoodHandle

ifBadHandle:
    MOV RAX, 0
    ADD RSP, 38h ; fix stack
    RET

ifGoodHandle:
    ; GetFileSize ======================================
    MOV RCX, fileHandle
    MOV RDX, NULL
    CALL GetFileSize
    MOV fileSize, EAX ; since fileSize is DWORD

    ; VirtualAlloc ======================================
    MOV RCX, NULL
    MOV EDX, fileSize ; since fileSize is DWORD
    MOV R8, MEM_COMMIT
    MOV R9, PAGE_READWRITE
    CALL VirtualAlloc
    MOV fileBuffer, RAX

    ; ReadFile ======================================
    MOV RCX, fileHandle
    MOV RDX, fileBuffer
    MOV R8D, fileSize ; r8d since its a dword not a qword
    MOV R9, offset bytesRead
    MOV QWORD PTR [RSP + 20h], NULL
    CALL ReadFile
    ; RAX holds true or false, our byte size is in bytesRead

    ; FindHitObjects ======================================
    MOV RCX, fileBuffer
    MOV EDX, bytesRead
    CALL findHitObjects
    mov startOfHitObject, rax

    ; FindHitCount ======================================
    MOV RCX, startOfHitObject ; start of after [HitObjects]
    MOV RDX, fileBuffer
    MOV R8D, bytesRead
    CALL findHitCount

    imul rax, rax, 10h

    ; VirtualAlloc ======================================
    MOV RCX, NULL
    MOV rdx, rax ; rax holds hitcount * 16
    MOV R8, MEM_COMMIT
    MOV R9, PAGE_READWRITE
    CALL VirtualAlloc
    mov ptrHitObject, rax ; ptrHitObject now points to that memory space thingy how fun

    ; ParseFile ======================================
    MOV RCX, startOfHitObject ; start of after [HitObjects]
    MOV RDX, fileBuffer
    MOV R8D, bytesRead
    mov R9, ptrHitObject
    CALL parseFile

    ; CloseHandle ======================================
    MOV RCX, fileHandle
    CALL CloseHandle

    ; VirtualFree ======================================
    MOV RCX, fileBuffer
    MOV RDX, NULL
    MOV R8D, MEM_RELEASE ; its a DWORD
    CALL VirtualFree

    mov rax, ptrHitObject ; returns pointer to HitObject
    ADD RSP, 38h ; fix shadow space and reserved
    RET
parseOsuFile ENDP
; =======================================================================================================
findHitObjects PROC
    PUSH RSI
    MOV RSI, RCX ; fileBuffer
    MOV ECX, EDX ; bytesRead

startLoop:
    CMP ECX, 12
    JL notFound

    CMP BYTE PTR [RSI], '['
    JNE wrong
    CMP BYTE PTR [RSI + 1], 'H'
    JNE wrong
    CMP BYTE PTR [RSI + 2], 'i'
    JNE wrong
    CMP BYTE PTR [RSI + 3], 't'
    JNE wrong
    CMP BYTE PTR [RSI + 4], 'O'
    JNE wrong
    CMP BYTE PTR [RSI + 5], 'b'
    JNE wrong
    CMP BYTE PTR [RSI + 6], 'j'
    JNE wrong
    CMP BYTE PTR [RSI + 7], 'e'
    JNE wrong
    CMP BYTE PTR [RSI + 8], 'c'
    JNE wrong
    CMP BYTE PTR [RSI + 9], 't'
    JNE wrong
    CMP BYTE PTR [RSI + 10], 's'
    JNE wrong
    CMP BYTE PTR [RSI + 11], ']'
    JNE wrong

    JMP finish

notFound:
    MOV RAX, 0
    POP RSI
    RET

wrong:
    INC RSI
    DEC ECX
    CMP ECX, 0
    JNE startLoop

finish:
    LEA RAX, [RSI + 14] ; since [HitObjects]CR + LF is 14 symbols
    POP RSI
    RET
findHitObjects ENDP
; =======================================================================================================
findHitCount PROC
    PUSH RSI
    push rdi

    MOV RSI, RCX ; start of after [HitObjects]. (currentPtr)
    MOV RDI, RDX ; start of file (startPtr)
    MOV ECX, R8D ; bytesRead (totalLength)

    ; remaining = totalLength - (currentPtr - startPtr)
    MOV RAX, RSI
    SUB RAX, RDX
    SUB RCX, RAX ; RCX holds remaining length 

    mov rax, 00h ; counter

findNewLine:
    cmp rcx, 00h
    je done

    cmp byte ptr [rsi], 0Ah ; (newline)
    jne next

    inc rax

next:
    inc rsi
    dec rcx
jmp findNewLine

done:
    pop rdi
    POP RSI
    RET
findHitCount ENDP
; =======================================================================================================
parseFile PROC
    PUSH RSI
    PUSH RDI
    PUSH RBX
    
    MOV RSI, RCX ; start of after [HitObjects]. (currentPtr)
    MOV RDI, RDX ; start of file (startPtr)
    MOV ECX, R8D ; bytesRead (totalLength)
    MOV RBX, R9 ; pointer to HitObject struct

    ; remaining = totalLength - (currentPtr - startPtr)
    MOV RAX, RSI
    SUB RAX, RDX
    SUB RCX, RAX ; RCX holds remaining length 

    mov r8, 00h ; offset index
    mov r10, 00h ; field index (x, y, time, type)
    ; value = value * 10 + (digit - '0')
startLoop:
    mov rax, 00h

makeNumber:
    cmp byte ptr [rsi], '0'
    jb notNumber
    cmp byte ptr [rsi], '9'
    ja notNumber

    movzx r11d, byte ptr [rsi]
    sub r11, '0'
    imul rax, rax, 10
    add rax, r11

    dec rcx
    inc rsi
    cmp byte ptr [rsi], ','
    jne makeNumber

    mov dword ptr [rbx + r8], eax ; start of HitObject + offset = number
    add r8, 04h
    ; skip ,
    dec rcx
    inc rsi

    inc r10
    cmp r10, 04h
    jne finishLoop

    mov r10, 00h
    mov r8, 00h
    add rbx, sizeof HitObject
skipSlider:
    inc rsi
    dec rcx
    cmp byte ptr [rsi], 0Ah ; (newline)
    jne skipSlider

    ; skips 0Ah (newline)
    inc rsi
    dec rcx

finishLoop:
    cmp rcx, 00h
jne startLoop

jmp finish

notNumber:
    inc rsi
    dec rcx
    jmp finishLoop

finish:
    mov rax, rbx
    POP RBX
    POP RDI
    POP RSI
    RET
parseFile ENDP
END