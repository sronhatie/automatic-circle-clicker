#include <windows.h>

uintptr_t readPtr(HANDLE hProcess, uintptr_t address){
    uintptr_t value = 0;
    ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(value), NULL);
    return value;
}

BYTE readByte(HANDLE hProcess, uintptr_t address){
    uintptr_t value = 0;
    ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(value), NULL);
    return value;
}

int readInt(HANDLE hProcess, uintptr_t address){
    uintptr_t value = 0;
    ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(value), NULL);
    return value;
}

double readDouble(HANDLE hProcess, uintptr_t address){
    uintptr_t value = 0;
    ReadProcessMemory(hProcess, (LPCVOID)address, &value, sizeof(value), NULL);
    return value;
}


