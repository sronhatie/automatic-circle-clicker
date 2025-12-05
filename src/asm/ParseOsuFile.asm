INCLUDE ParseOsuFile.inc

.data
    lpFileName dq "Kry.exe - Rift Walker (Ryuusei Aika) [Easy].osu", 0
    hCreateFile dq ?

PUBLIC ParseOsuFile
.code

ParseOsuFile PROC
    SUB RSP, 28h ; shadow space + reserved space = 40(dec)

    MOV RCX, offset lpFileName
    MOV RDX, GENERIC_READ
    MOV R8, FILE_SHARE_READ
    MOV R9, NULL
    SUB RSP, 18h ; 3 more args
    MOV QWORD PTR [RSP], NULL
    MOV QWORD PTR [RSP + 8], FILE_ATTRIBUTE_NORMAL
    MOV QWORD PTR [RSP + 16], OPEN_EXISTING
    CALL CreateFileA
    ADD RSP, 18h ; fix 3 args
    CMP RAX, INVALID_HANDLE_VALUE
    JE ifBadHandle

    MOV hCreateFile, RAX
    JMP ifGoodHandle:


ifBadHandle:
    MOV RAX, 0
    RET

ifGoodHandle:
    
    


    ADD RSP, 28h ; fix shadow space and reserved
    RET
ParseOsuFile ENDP
END