EXTERN CreateFileA:PROC
EXTERN GetFileSize:PROC
EXTERN VirtualAlloc:PROC
EXTERN ReadFile:PROC
EXTERN CloseHandle:PROC
EXTERN VirtualFree:PROC

; CreateFileA
GENERIC_READ EQU 80000000h ; dwDesiredAccess
FILE_SHARE_READ EQU 01h ; dwShareMode
OPEN_EXISTING EQU 03h ; dwCreationDisposition
FILE_ATTRIBUTE_NORMAL EQU 80h ; dwFlagsAndAttributes
INVALID_HANDLE_VALUE EQU -1h ; return value from CreateFileA on failure
NULL EQU 0
; VirtualAlloc
MEM_COMMIT EQU 00001000h ; flAllocationType
PAGE_READWRITE EQU 04h ; flProtect
; VirtualFree
MEM_RELEASE EQU 000008000h


HitObject STRUCT
    x DWORD ?
    y DWORD ?
    objectTime DWORD ?
    objectType DWORD ?
HitObject ENDS