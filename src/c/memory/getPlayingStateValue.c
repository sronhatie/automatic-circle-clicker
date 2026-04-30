#include <windows.h>

int getPlayingStateValue(HANDLE hProcess, uintptr_t playerPtr){
    uintptr_t playingState = 0;
    int playingStateValue = 0;

    ReadProcessMemory(hProcess, (LPCVOID)(playerPtr + 0x3D0), &playingState, sizeof(playerPtr), NULL);
    ReadProcessMemory(hProcess, (LPCVOID)(playingState + 0x40), &playingStateValue, sizeof(playingStateValue), NULL);

    return playingStateValue;
}