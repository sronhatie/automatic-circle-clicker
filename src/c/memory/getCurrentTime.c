#include <windows.h>

double getCurrentTime(HANDLE hProcess, uintptr_t playfieldPtr){
    uintptr_t clock = 0;
    uintptr_t framedClock = 0;
    double currentTime = 0.0;

    ReadProcessMemory(hProcess, (LPCVOID)(playfieldPtr + 0x80), &clock, sizeof(clock), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(clock + 0x358), &framedClock, sizeof(framedClock), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(framedClock + 0x30), &currentTime, sizeof(currentTime), NULL);

    return currentTime;
}