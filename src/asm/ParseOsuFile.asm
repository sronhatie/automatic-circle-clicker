INCLUDE ParseOsuFile.inc

.data
    lpFileName db "Kry.exe - Rift Walker (Ryuusei Aika) [Easy].osu", 0
    fileHandle dq ?
    fileSize dd ?
    fileBuffer dq ?
    bytesRead dd ?

PUBLIC ParseOsuFile
.code

ParseOsuFile PROC
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
    ; RAX holds true or false, our read bytes are in bytesRead

    MOV RCX, fileBuffer
    MOV EDX, bytesRead
    CALL FindHitObjects

    MOV RCX, RAX
    CALL ParseFile




    ; CloseHandle ======================================
    MOV RCX, fileHandle
    CALL CloseHandle

    ; VirtualFree ======================================
    MOV RCX, fileBuffer
    MOV RDX, NULL
    MOV R8D, MEM_RELEASE ; its a DWORD
    CALL VirtualFree

    ADD RSP, 38h ; fix shadow space and reserved
    RET
ParseOsuFile ENDP

FindHitObjects PROC ptrFileBuffer:QWORD, readLength:DWORD
    PUSH RSI
    MOV RSI, ptrFileBuffer
    MOV ECX, readLength

startLoop:
    CMP ECX, 0
    JE notFound
    CMP ECX, 11
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
    CMP BYTE PTR [RSI + 8], 't'
    JNE wrong
    CMP BYTE PTR [RSI + 9], 's'
    JNE wrong
    CMP BYTE PTR [RSI + 10], ']'
    JNE wrong

    JMP finish

notFound:
    MOV RAX, 0
    POP RSI
    RET

wrong:
    INC RSI
    DEC ECX
    JNZ startLoop


finish:
    LEA RAX, [RSI + 14] ; since [HitObjects]CR + LF is 14 symbols
    POP RSI
    RET
FindHitObjects ENDP

ParseFile PROC ptrFirstByte:QWORD 

    RET
ParseFile ENDP
END