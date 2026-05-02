#include <windows.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "asmFunctions.h"
#include "cFunctions.h"
#include "signatures.h"
#include "debugging.h"
#include "signatures.h"
#include "memory.h"
#include "osuChain.h"
#include "offsets.h"

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
        uintptr_t playerPtr = getPlayerPtr(hProcess, osuGamePtr);
        int playingStateValue = getPlayingStateValue(hProcess, playerPtr);

        if(playingStateValue == 2){
            uintptr_t playfieldPtr = getPlayfieldPtr(hProcess, playerPtr);
            uintptr_t hitObjectContainer = getHitObjectContainerPtr(hProcess, playfieldPtr);
            uintptr_t dict = getAliveDrawableMapPtr(hProcess, hitObjectContainer);
            uintptr_t entries = getDictionaryEntriesPtr(hProcess, dict);
            int count = getDictionaryCount(hProcess, dict);

            for(int i = 0; i < count; ++i){
                uintptr_t entry = getDictionaryEntryPtr(entries, i);
                uintptr_t drawable = getDictionaryEntryValuePtr(hProcess, entry);

                if(!drawable){
                    continue;
                }

                uintptr_t hitArea = getDrawableHitAreaPtr(hProcess, drawable);

                if(!hitArea){
                    continue;
                }

                int isHovered = getHitAreaIsHovered(hProcess, hitArea);
                printf("hovered: %d\n",isHovered);
            }
        }

        Sleep(500);
    }

    printf("aaaa\n");
}