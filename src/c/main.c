#include <windows.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "asmFunctions.h"
#include "cFunctions.h"
#include "signatures.h"

int main(){
    char *processName = "osu!.exe";
    DWORD processID = findPID(processName);
    if(!processID){
        printf("Osu!lazer not running");
        return 1;
    }

    // HitObject *PtrHitObject;
    // PtrHitObject = parseOsuFile();

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION, FALSE, processID);

    uintptr_t updateAfterChildrenAddr = findPatternInProcess(hProcess, updateAfterChildrenSignature, updateAfterChildrenMask);

    BYTE originalByte = 0;
    ReadProcessMemory(hProcess, (LPCVOID)updateAfterChildrenAddr, &originalByte, 1, NULL);

    DebugActiveProcess(processID);
    DebugSetProcessKillOnExit(FALSE);

    waitForInitialAttachBreakpoint();
    writeOneByte(hProcess, updateAfterChildrenAddr, 0xCC);

    uintptr_t osuGamePtr = captureBreakpointRCX(hProcess, updateAfterChildrenAddr, originalByte);
    DebugActiveProcessStop(processID);

    printf("OsuGame ptr = %p\n", (void *)osuGamePtr);

    int previousPlayingStateValue = -1;
    while(1){
        uintptr_t playerPtr = getPlayerPtr(hProcess, osuGamePtr);
        int playingStateValue = getPlayingStateValue(hProcess, playerPtr);
            if (playingStateValue != previousPlayingStateValue) {
                printf("playingStateValue = %d\n", playingStateValue);
                previousPlayingStateValue = playingStateValue;
            }
        Sleep(50);
    }

    CloseHandle(hProcess);

    printf("aaaa\n");

    // while(1){
    //   if(keyWasPressed()){

    //     printf("Started clicking\n");
    //     int i = 0;
    //     int previousTime = 0;

    //     while(PtrHitObject[i].x != 0){
    //       if(keyWasPressed()){
    //         printf("Stopped clicking\n");
    //         break;
    //       }

    //       int delay = PtrHitObject[i].objectTime - previousTime;
    //       previousTime = PtrHitObject[i].objectTime;
    //       printf("%d : %d | ", delay, previousTime);

    //       mouseDown();
    //       mouseUp();
    //       printf("clicked\n");
    //       Sleep(delay);
    //       //moveMouse(PtrHitObject[i].x, PtrHitObject[i].y);
    //       i++;
    //     }
    //   }

    //   Sleep(100);
    // }

    return 0;
}