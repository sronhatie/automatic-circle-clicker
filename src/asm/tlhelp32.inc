TH32CS_SNAPPROCESS equ 02h

PROCESSENTRY32 STRUCT
    dwSize DWORD ?
    cntUsage DWORD ?
    th32ProcessID DWORD ?
    padding1 DWORD ?
    th32DefaultHeapID QWORD ?
    th32ModuleID DWORD ?
    cntThreads DWORD ?
    th32ParentProcessID DWORD ?
    pcPriClassBase DWORD ?
    dwFlags DWORD ?
    szExeFile BYTE 260 DUP(?) ; char MAX_PATH
PROCESSENTRY32 ENDS