#include <windows.h>
#include <stdint.h>
#include <stdio.h>

#include "relaxLogic.h"
#include "osuChain.h"
#include "asmFunctions.h"
#include "hitResult.h"

#define EARLY_ACTION_MS 12.0
#define PLAYING_STATE_PLAYING 2
#define ACTION_NONE  0
#define ACTION_HOLD  1
#define ACTION_CLICK 2
#define CLICK_HOLD_MS 20

int isSlider(HANDLE hProcess, uintptr_t drawablePtr){
    // only sliders have this so it checks if the object has this, if it does its a slider
    // SliderInputManager points back to the owning drawable slider
    uintptr_t sliderInputManager = getDrawableSliderInputManagerPtr(hProcess, drawablePtr);
    if(!sliderInputManager){
        return 0;
    }

    uintptr_t slider = getSliderInputManagerSliderPtr(hProcess, sliderInputManager);

    return slider == drawablePtr;
}

int handleCircle(HANDLE hProcess, uintptr_t drawablePtr, double currentTime, double *outStartTime){
    int resultType = getDrawableResultType(hProcess, drawablePtr);
    // if its already hit ignore it (prevents clicking more than once)
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

    // negative = too early
    // 0        = exactly on time
    // positive = late
    double timeOffset = currentTime - startTime;

    // clicks earlier to compensate for delay
    if(currentTime < startTime - EARLY_ACTION_MS){
        return 0;
    }
    
    // if too late, ignore it
    if(timeOffset > mehWindow){
        return 0;
    }

    *outStartTime = startTime;
    // circle is valid only if it is unhit, hovered, and inside its hit window
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

    // clicks earlier to compensate for delay
    if(currentTime < startTime - EARLY_ACTION_MS){
        return 0;
    }

    // slider already ended
    if(currentTime > endTime){
        return 0;
    }

    *outStartTime = startTime;
    return 1;
}

void runRelax(HANDLE hProcess, uintptr_t osuGamePtr){
    uintptr_t playerPtr = getPlayerPtr(hProcess, osuGamePtr);
    int playingStateValue = getPlayingStateValue(hProcess, playerPtr);

    // only runs it if playingState == 2 (Playing)
    if(playingStateValue == PLAYING_STATE_PLAYING){
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
            int action = ACTION_NONE;

            if(isSlider(hProcess, drawable)){
                if(!handleSlider(hProcess, drawable, currentTime, &startTime)){
                    continue;
                }
                action = ACTION_HOLD;
            } else{
                if(!handleCircle(hProcess, drawable, currentTime, &startTime)){
                    continue;
                }
                action = ACTION_CLICK;
            }

            // pick earliest object because multiple objects can be alive at the same time
            if(startTime < bestStartTime){
                bestStartTime = startTime;
                bestDrawable = drawable;
                bestAction = action;
            }
        }

        static int mouseIsDown = 0;

        if(bestDrawable){
            if(bestAction == ACTION_HOLD){
                if(!mouseIsDown){
                    mouseDown();
                    mouseIsDown = 1;
                }
            } else if(bestAction == ACTION_CLICK){
                if(mouseIsDown){
                    mouseUp();
                    mouseIsDown = 0;
                }

                mouseDown();
                Sleep(CLICK_HOLD_MS);
// TODO: make it not use Sleep() since it blocks the whole program
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