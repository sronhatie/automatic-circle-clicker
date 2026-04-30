#include <windows.h>

uintptr_t getPlayfieldPtr(HANDLE hProcess, uintptr_t playerPtr){
    uintptr_t drawableRuleset = 0;
    uintptr_t lazyPlayfield = 0;
    uintptr_t playfield = 0;

    ReadProcessMemory(hProcess, (LPCVOID)(playerPtr + 0x458), &drawableRuleset, sizeof(drawableRuleset), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(drawableRuleset + 0x360), &lazyPlayfield, sizeof(lazyPlayfield), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(lazyPlayfield + 0x18), &playfield, sizeof(playfield), NULL);

    return playfield;
}