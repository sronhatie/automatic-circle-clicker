#include <windows.h>
#include <stdint.h>
#include <stdio.h>

#include "relaxLogic.h"
#include "osuChain.h"
#include "asmFunctions.h"
#include "hitResult.h"

int isSlider(HANDLE hProcess, uintptr_t drawablePtr){
    uintptr_t sliderInputManager = getDrawableSliderInputManagerPtr(hProcess, drawablePtr);
    if(!sliderInputManager){
        return 0;
    }

    uintptr_t slider = getSliderInputManagerSliderPtr(hProcess, sliderInputManager);

    return slider == drawablePtr;
}

int handleCircle(HANDLE hProcess, uintptr_t drawablePtr, double currentTime, double *outStartTime){
    int resultType = getDrawableResultType(hProcess, drawablePtr);
    if(hitResultIsHit(resultType)){
        return 0;
    }

    uintptr_t hitArea = getDrawableHitAreaPtr(hProcess, drawablePtr);
    if(!hitArea){
        return 0;
    }

    int isHovered = getHitAreaIsHovered(hProcess, hitArea);
    if(!isHovered){
        return 0;
    }

    uintptr_t hitObject = getDrawableHitObjectPtr(hProcess, drawablePtr);
    double startTime = getHitObjectStartTime(hProcess, hitObject);
    uintptr_t hitWindows = getHitObjectHitWindowsPtr(hProcess, hitObject);
    double mehWindow = getHitWindowsMeh(hProcess, hitWindows);

    double timeOffset = currentTime - startTime;

    if(currentTime < startTime - 12.0){
        return 0;
    }

    if(timeOffset > mehWindow){
        return 0;
    }

    *outStartTime = startTime;
    return 1;
}

int handleSlider(HANDLE hProcess, uintptr_t drawablePtr, double currentTime, double *outStartTime){
    int resultType = getDrawableResultType(hProcess, drawablePtr);
    if(hitResultIsHit(resultType)){
        return 0;
    }

    uintptr_t hitObject = getDrawableHitObjectPtr(hProcess, drawablePtr);
    if(!hitObject){
        return 0;
    }

    double startTime = getHitObjectStartTime(hProcess, hitObject);
    double endTime = getSliderEndTime(hProcess, hitObject);

    if(currentTime < startTime - 12.0){
        return 0;
    }

    if(currentTime > endTime){
        return 0;
    }

    *outStartTime = startTime;
    return 1;
}

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
        int bestAction = 0;

        for(int i = 0; i < count; ++i){
            uintptr_t entry = getDictionaryEntryPtr(entries, i);
            uintptr_t drawable = getDictionaryEntryValuePtr(hProcess, entry);
            if(!drawable){
                continue;
            }

            uintptr_t hitObject = getDrawableHitObjectPtr(hProcess, drawable);
            if(!hitObject){
                continue;
            }
            
            double startTime = 0.0;
            int action = 0;

            if(isSlider(hProcess, drawable)){
                if(!handleSlider(hProcess, drawable, currentTime, &startTime)){
                    continue;
                }
                action = 1;
            } else{
                if(!handleCircle(hProcess, drawable, currentTime, &startTime)){
                    continue;
                }
                action = 2;
            }

            if(startTime < bestStartTime){
                bestStartTime = startTime;
                bestDrawable = drawable;
                bestAction = action;
            }
        }

        static int mouseIsDown = 0;

        if(bestDrawable){
            if(bestAction == 1){ // HOLD
                if(!mouseIsDown){
                    mouseDown();
                    mouseIsDown = 1;
                }
            } else if(bestAction == 2){ // CLICK
                if(mouseIsDown){
                    mouseUp();
                    mouseIsDown = 0;
                }

                mouseDown();
                Sleep(20);
                mouseUp();
            }
        } else{
            if(mouseIsDown){
                mouseUp();
                mouseIsDown = 0;
            }
        }
    }
}