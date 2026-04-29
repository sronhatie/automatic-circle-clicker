#include <windows.h>

uintptr_t getPlayerPtr(HANDLE hProcess, uintptr_t osuGamePtr){
    uintptr_t screenStack = 0;
    uintptr_t screenList = 0;
    int screenCount = 0;
    uintptr_t screenArray = 0;
    uintptr_t currentScreen = 0; // Player

    ReadProcessMemory(hProcess, (LPCVOID)(osuGamePtr + 0x5F8), &screenStack, sizeof(screenStack), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(screenStack + 0x320), &screenList, sizeof(screenList), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(screenList + 0x10), &screenCount, sizeof(screenCount), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(screenList + 0x8), &screenArray, sizeof(screenArray), NULL);
    uintptr_t currentScreenEntryAddress = screenArray + 0x10 + (uintptr_t)(screenCount - 1) * 8;
    ReadProcessMemory(hProcess, (LPCVOID)currentScreenEntryAddress, &currentScreen, sizeof(currentScreen), NULL);

    return currentScreen;
}