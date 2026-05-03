#include <windows.h>
#include <stdint.h>
#include <stdio.h>

#include "relaxLogic.h"
#include "osuChain.h"
#include "asmFunctions.h"
#include "hitResult.h"

void runRelax(HANDLE hProcess, uintptr_t osuGamePtr){
    uintptr_t playerPtr = getPlayerPtr(hProcess, osuGamePtr);
    int playingStateValue = getPlayingStateValue(hProcess, playerPtr);

    if(playingStateValue == 2){
        uintptr_t playfieldPtr = getPlayfieldPtr(hProcess, playerPtr);
        double currentTime = getCurrentTime(hProcess, playfieldPtr);

        uintptr_t hitObjectContainer = getHitObjectContainerPtr(hProcess, playfieldPtr);
        uintptr_t dict = getAliveDrawableMapPtr(hProcess, hitObjectContainer);
        uintptr_t entries = getDictionaryEntriesPtr(hProcess, dict);
        int count = getDictionaryCount(hProcess, dict);

        uintptr_t bestDrawable = 0;
        double bestStartTime = 999999999.0;

        for(int i = 0; i < count; ++i){
            uintptr_t entry = getDictionaryEntryPtr(entries, i);
            uintptr_t drawable = getDictionaryEntryValuePtr(hProcess, entry);
            if(!drawable){
                continue;
            }

            int resultType = getDrawableResultType(hProcess, drawable);
            if(hitResultIsHit(resultType)){
                continue;
            }

            uintptr_t hitArea = getDrawableHitAreaPtr(hProcess, drawable);
            if(!hitArea){
                continue;
            }

            int isHovered = getHitAreaIsHovered(hProcess, hitArea);
            if(!isHovered){
                continue;
            }
    
            uintptr_t hitObject = getDrawableHitObjectPtr(hProcess, drawable);
            double startTime = getHitObjectStartTime(hProcess, hitObject);
            uintptr_t hitWindows = getHitObjectHitWindowsPtr(hProcess, hitObject);
            double mehWindow = getHitWindowsMeh(hProcess, hitWindows);

            double timeOffset = currentTime - startTime;

            if(currentTime < startTime - 12.0){
                continue;
            }

            if(timeOffset > mehWindow){
                continue;
            }

            if(startTime < bestStartTime){
                bestStartTime = startTime;
                bestDrawable = drawable;
            }
        }

        if(bestDrawable){
            mouseDown();
            Sleep(20);
            mouseUp();
        }
    }
}