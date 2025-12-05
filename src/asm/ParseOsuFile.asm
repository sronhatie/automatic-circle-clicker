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
    MOV QWORD PTR [RSP + 20h], OPEN_EXISTING
    MOV QWORD PTR [RSP + 28h], FILE_ATTRIBUTE_NORMAL
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

    
    
    ADD RSP, 38h ; fix shadow space and reserved
    RET
ParseOsuFile ENDP
END