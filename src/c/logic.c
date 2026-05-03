#include <windows.h>
#include <stdint.h>
#include <stdio.h>

#include "asmFunctions.h"
#include "osuChain.h"

#include "relaxLogic.h"

void start(){
    char *processName = "osu!.exe";
    DWORD processID = findPID(processName);
    if(!processID){
        printf("Osu not open\n");
        return;
    }
    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION | PROCESS_QUERY_INFORMATION, FALSE, processID);
    uintptr_t osuGamePtr = getOsuGamePtr(hProcess, processID);

    printf("OsuGame ptr = %p\n", (void *)osuGamePtr);

    while(1){
        runRelax(hProcess, osuGamePtr);

        Sleep(10);
    }
}