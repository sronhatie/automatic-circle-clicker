INCLUDE ParseOsuFile.inc

.data
    lpFileName db "Kry.exe - Rift Walker (Ryuusei Aika) [Easy].osu", 0
    hCreateFile dq ?

PUBLIC ParseOsuFile
.code

ParseOsuFile PROC
    SUB RSP, 28h ; shadow space + reserved space = 40(dec)

    MOV RCX, offset lpFileName
    MOV RDX, GENERIC_READ
    MOV R8, FILE_SHARE_READ
    MOV R9, NULL
    SUB RSP, 20h ; 3 more args + 8 bytes to align it
    MOV QWORD PTR [RSP + 20h], OPEN_EXISTING
    MOV QWORD PTR [RSP + 28h], FILE_ATTRIBUTE_NORMAL
    MOV QWORD PTR [RSP + 30h], NULL
    CALL CreateFileA
    ADD RSP, 20h ; fix 3 args
    CMP RAX, INVALID_HANDLE_VALUE
    JE ifBadHandle

    MOV hCreateFile, RAX
    JMP ifGoodHandle


ifBadHandle:
    MOV RAX, 0
    ADD RSP, 28h ; fix shadow space and reserved
    RET

ifGoodHandle:
    
    


    ADD RSP, 28h ; fix shadow space and reserved
    RET
ParseOsuFile ENDP
END