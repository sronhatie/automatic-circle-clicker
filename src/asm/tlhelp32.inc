TH32CS_SNAPPROCESS equ 02h

PROCESSENTRY32 STRUCT
    dwSize DWORD ?              ; size of the structure, must be set before calling Process32First
    cntUsage DWORD ?            ; no longer used always 0
    th32ProcessID DWORD ?       ; process identifier
    padding1 DWORD ?            ; no longer used always 0
    th32DefaultHeapID QWORD ?   ; no longer used always 0
    th32ModuleID DWORD ?        ; no longer used always 0
    cntThreads DWORD ?          ; number of execution threads started by the process
    th32ParentProcessID DWORD ? ; its parent process (the process that created it)
    pcPriClassBase DWORD ?      ; base priority of any thread created by this process
    dwFlags DWORD ?             ; no longer used always 0
    szExeFile BYTE 260 DUP(?)   ; char MAX_PATH
PROCESSENTRY32 ENDS