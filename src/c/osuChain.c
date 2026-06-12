#include <windows.h>

#include "asmFunctions.h"
#include "debugging.h"
#include "osuChain.h"
#include "offsets.h"
#include "memory.h"
#include "signatures.h"

uintptr_t getOsuGamePtr(HANDLE hProcess, DWORD processID){
    uintptr_t updateAfterChildrenAddr = findPatternInProcess(hProcess, updateAfterChildrenSignature, updateAfterChildrenMask);

    BYTE originalByte = 0;
    ReadProcessMemory(hProcess, (LPCVOID)updateAfterChildrenAddr, &originalByte, 1, NULL);

    DebugActiveProcess(processID); // attaches as a debugger
// TODO: check if it fails or not (the program just silently fails if another debugger is already attached to it.)
    DebugSetProcessKillOnExit(FALSE);

    waitForInitialAttachBreakpoint(); // removes the first breakpoint (0xCC aka int3)
    writeOneByte(hProcess, updateAfterChildrenAddr, 0xCC); 

    // gets rcx, since that holds the address of OsuGame
    uintptr_t osuGamePtr = captureBreakpointRCX(hProcess, updateAfterChildrenAddr, originalByte);
    DebugActiveProcessStop(processID);

    return osuGamePtr;
}

uintptr_t getPlayerPtr(HANDLE hProcess, uintptr_t osuGamePtr){
    uintptr_t screenStack = readPtr(hProcess, osuGamePtr + osuOffsets.osuGame.screenStack);
    uintptr_t screenList = readPtr(hProcess, screenStack + osuOffsets.screenStack.screenList);
    int screenCount = readInt(hProcess, screenList + osuOffsets.list.count);
    uintptr_t screenArray = readPtr(hProcess, screenList + osuOffsets.list.array);
    uintptr_t currentScreenEntryAddress = screenArray + osuOffsets.list.firstElement + (uintptr_t)(screenCount - 1) * osuOffsets.list.elementSize;

    return readPtr(hProcess, currentScreenEntryAddress);
}

uintptr_t getPlayfieldPtr(HANDLE hProcess, uintptr_t playerPtr){
    uintptr_t drawableRuleset = readPtr(hProcess, playerPtr + osuOffsets.player.drawableRuleset);
    uintptr_t lazyPlayfield = readPtr(hProcess, drawableRuleset + osuOffsets.drawableRuleset.playfieldLazy);

    return readPtr(hProcess, lazyPlayfield + osuOffsets.lazy.lazyValue);
}

int getPlayingStateValue(HANDLE hProcess, uintptr_t playerPtr){
    uintptr_t playingState = readPtr(hProcess, playerPtr + osuOffsets.player.playingState);

    return readInt(hProcess, playingState + osuOffsets.playingState.value);
}

double getCurrentTime(HANDLE hProcess, uintptr_t playfieldPtr){
    uintptr_t clock = readPtr(hProcess, playfieldPtr + osuOffsets.playfield.clock);
    uintptr_t framedClock = readPtr(hProcess, clock + osuOffsets.clock.frameStabilityContainer);

    return readDouble(hProcess, framedClock + osuOffsets.frameStabilityContainer.currentTime);
}

uintptr_t getHitObjectContainerPtr(HANDLE hProcess, uintptr_t playfieldPtr){
    uintptr_t lazyHitObjectContainer = readPtr(hProcess, playfieldPtr + osuOffsets.playfield.hitObjectContainerLazy);

    return readPtr(hProcess, lazyHitObjectContainer + osuOffsets.lazy.lazyValue);
}

uintptr_t getAliveDrawableMapPtr(HANDLE hProcess, uintptr_t hitObjectContainerPtr){
    return readPtr(hProcess, hitObjectContainerPtr + osuOffsets.hitObjectContainer.aliveDrawableMap);
}

uintptr_t getDictionaryEntriesPtr(HANDLE hProcess, uintptr_t dictPtr){
    return readPtr(hProcess, dictPtr + osuOffsets.dictionary.entries);
}

int getDictionaryCount(HANDLE hProcess, uintptr_t dictPtr){
    return readInt(hProcess, dictPtr + osuOffsets.dictionary.count);
}

uintptr_t getDictionaryEntryPtr(uintptr_t entriesPtr, int index){
    return entriesPtr + osuOffsets.managedArray.firstElement + (uintptr_t)index * osuOffsets.dictionaryEntry.size;
}

uintptr_t getDictionaryEntryValuePtr(HANDLE hProcess, uintptr_t entryPtr){
    return readPtr(hProcess, entryPtr + osuOffsets.dictionaryEntry.value);
}

uintptr_t getDrawableEntryPtr(HANDLE hProcess, uintptr_t drawablePtr){
    return readPtr(hProcess, drawablePtr + osuOffsets.drawableOsuHitObject.entry);
}

uintptr_t getDrawableHitObjectPtr(HANDLE hProcess, uintptr_t drawablePtr){
    uintptr_t entry = getDrawableEntryPtr(hProcess, drawablePtr);

    return readPtr(hProcess, entry + osuOffsets.hitObjectLifetimeEntry.hitObject);
}

uintptr_t getDrawableSliderInputManagerPtr(HANDLE hProcess, uintptr_t drawablePtr){
    return readPtr(hProcess, drawablePtr + osuOffsets.drawableSlider.sliderInputManager);
}

uintptr_t getSliderInputManagerSliderPtr(HANDLE hProcess, uintptr_t sliderInputManagerPtr){
    return readPtr(hProcess, sliderInputManagerPtr + osuOffsets.sliderInputManager.slider);
}

uintptr_t getSliderHeadCirclePtr(HANDLE hProcess, uintptr_t hitObjectPtr){
    return readPtr(hProcess, hitObjectPtr + osuOffsets.slider.headCircle);
}

uintptr_t getSliderTailCirclePtr(HANDLE hProcess, uintptr_t hitObjectPtr){
    return readPtr(hProcess, hitObjectPtr + osuOffsets.slider.tailCircle);
}

double getHitObjectStartTime(HANDLE hProcess, uintptr_t hitObjectPtr){
    uintptr_t startTimeBindable = readPtr(hProcess, hitObjectPtr + osuOffsets.hitObject.startTimeBindable);

    return readDouble(hProcess, startTimeBindable + osuOffsets.bindable.value);
}

double getDrawableStartTime(HANDLE hProcess, uintptr_t drawablePtr){
    uintptr_t hitObject = getDrawableHitObjectPtr(hProcess, drawablePtr);

    return getHitObjectStartTime(hProcess, hitObject);
}

double getEntryLifetimeEnd(HANDLE hProcess, uintptr_t entryPtr){
    return readDouble(hProcess, entryPtr + osuOffsets.hitObjectLifetimeEntry.lifetimeEnd);
}

double getDrawableLifetimeEnd(HANDLE hProcess, uintptr_t drawablePtr){
    uintptr_t entry = getDrawableEntryPtr(hProcess, drawablePtr);

    return getEntryLifetimeEnd(hProcess, entry);
}

double getSliderEndTime(HANDLE hProcess, uintptr_t hitObjectPtr){
    uintptr_t tailCircle = getSliderTailCirclePtr(hProcess, hitObjectPtr);

    return getHitObjectStartTime(hProcess, tailCircle);
}

uintptr_t getHitObjectHitWindowsPtr(HANDLE hProcess, uintptr_t hitObjectPtr){
    return readPtr(hProcess, hitObjectPtr + osuOffsets.hitObject.hitWindows);
}

double getHitWindowsMeh(HANDLE hProcess, uintptr_t hitWindowsPtr){
    return readDouble(hProcess, hitWindowsPtr + osuOffsets.hitWindows.meh);
}

uintptr_t getDrawableResultPtr(HANDLE hProcess, uintptr_t drawablePtr){
    uintptr_t entry = getDrawableEntryPtr(hProcess, drawablePtr);

    return readPtr(hProcess, entry + osuOffsets.hitObjectLifetimeEntry.result);
}

int getDrawableResultType(HANDLE hProcess, uintptr_t drawablePtr){
    uintptr_t result = getDrawableResultPtr(hProcess, drawablePtr);

    if(!result){
        return 0; // HitResult.None
    }

    return readInt(hProcess, result + osuOffsets.judgementResult.type);
}

uintptr_t getDrawableHitAreaPtr(HANDLE hProcess, uintptr_t drawablePtr){
    return readPtr(hProcess, drawablePtr + osuOffsets.drawableOsuHitObject.hitArea);
}

int getHitAreaIsHovered(HANDLE hProcess, uintptr_t hitAreaPtr){
    return readByte(hProcess, hitAreaPtr + osuOffsets.hitArea.isHovered);
}
