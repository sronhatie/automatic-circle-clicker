#include <windows.h>
#include <stdint.h>
#include <stdio.h>

#include "osuChain.h"
#include "offsets.h"
#include "memory.h"
#include "asmFunctions.h"

void testing(){
    char *processName = "osu!.exe";
    DWORD processID = findPID(processName);
    if(!processID){
        printf("osu not found\n");
        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processID);
    if(!hProcess){
        printf("OpenProcess failed\n");
        return;
    }

    uintptr_t osuGamePtr = getOsuGamePtr(hProcess, processID);
    printf("osuGamePtr: %p\n", (void*)osuGamePtr);

    uintptr_t screenStack = readPtr(hProcess, osuGamePtr + osuOffsets.osuGame.screenStack);
    printf("screenStack: %p\n", (void*)screenStack);

    uintptr_t screenList = readPtr(hProcess, screenStack + osuOffsets.screenStack.screenList);
    printf("screenList: %p\n", (void*)screenList);

    int screenCount = readInt(hProcess, screenList + osuOffsets.list.count);
    printf("screenCount: %d\n", screenCount);

    uintptr_t screenArray = readPtr(hProcess, screenList + osuOffsets.list.array);
    printf("screenArray: %p\n", (void*)screenArray);

    uintptr_t currentScreenEntryAddress = screenArray + osuOffsets.list.firstElement + (uintptr_t)(screenCount - 1) * osuOffsets.list.elementSize;
    printf("currentScreenEntryAddress: %p\n", (void*)currentScreenEntryAddress);

    uintptr_t playerPtr = readPtr(hProcess, currentScreenEntryAddress);
    printf("playerPtr: %p\n", (void*)playerPtr);

    uintptr_t playingState = readPtr(hProcess, playerPtr + osuOffsets.player.playingState);
    printf("playingState ptr: %p\n", (void*)playingState);

    int playingStateValue = readInt(hProcess, playingState + osuOffsets.playingState.value);
    printf("playingState value: %d\n", playingStateValue);

    uintptr_t drawableRuleset = readPtr(hProcess, playerPtr + osuOffsets.player.drawableRuleset);
    printf("drawableRuleset: %p\n", (void*)drawableRuleset);

    uintptr_t lazyPlayfield = readPtr(hProcess, drawableRuleset + osuOffsets.drawableRuleset.playfieldLazy);
    printf("lazyPlayfield: %p\n", (void*)lazyPlayfield);

    uintptr_t playfieldPtr = readPtr(hProcess, lazyPlayfield + osuOffsets.lazy.lazyValue);
    printf("playfieldPtr: %p\n", (void*)playfieldPtr);

    uintptr_t clock = readPtr(hProcess, playfieldPtr + osuOffsets.playfield.clock);
    printf("clock: %p\n", (void*)clock);

    uintptr_t framedClock = readPtr(hProcess, clock + osuOffsets.clock.frameStabilityContainer);
    printf("framedClock: %p\n", (void*)framedClock);

    double currentTime = readDouble(hProcess, framedClock + osuOffsets.frameStabilityContainer.currentTime);
    printf("currentTime: %.3f\n", currentTime);

    uintptr_t lazyHitObjectContainer = readPtr(hProcess, playfieldPtr + osuOffsets.playfield.hitObjectContainerLazy);
    printf("lazyHitObjectContainer: %p\n", (void*)lazyHitObjectContainer);

    uintptr_t hitObjectContainer = readPtr(hProcess, lazyHitObjectContainer + osuOffsets.lazy.lazyValue);
    printf("hitObjectContainer: %p\n", (void*)hitObjectContainer);

    uintptr_t dict = readPtr(hProcess, hitObjectContainer + osuOffsets.hitObjectContainer.aliveDrawableMap);
    printf("aliveDrawableMap/dict: %p\n", (void*)dict);

    uintptr_t entries = readPtr(hProcess, dict + osuOffsets.dictionary.entries);
    printf("entries: %p\n", (void*)entries);

    int count = readInt(hProcess, dict + osuOffsets.dictionary.count);
    printf("count: %d\n", count);
}