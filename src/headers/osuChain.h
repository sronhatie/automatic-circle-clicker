#ifndef OSUCHAIN_H
#define OSUCHAIN_H

#include <Windows.h>

uintptr_t getOsuGamePtr(HANDLE hProcess, DWORD processID);
uintptr_t getPlayerPtr(HANDLE hProcess, uintptr_t osuGamePtr);
uintptr_t getPlayfieldPtr(HANDLE hProcess, uintptr_t playerPtr);
int getPlayingStateValue(HANDLE hProcess, uintptr_t playerPtr);
double getCurrentTime(HANDLE hProcess, uintptr_t playfieldPtr);

uintptr_t getHitObjectContainerPtr(HANDLE hProcess, uintptr_t playfieldPtr);
uintptr_t getAliveDrawableMapPtr(HANDLE hProcess, uintptr_t hitObjectContainerPtr);
uintptr_t getDictionaryEntriesPtr(HANDLE hProcess, uintptr_t dictPtr);
int getDictionaryCount(HANDLE hProcess, uintptr_t dictPtr);

uintptr_t getDictionaryEntryPtr(uintptr_t entriesPtr, int index);
uintptr_t getDictionaryEntryValuePtr(HANDLE hProcess, uintptr_t entryPtr);

uintptr_t getDrawableEntryPtr(HANDLE hProcess, uintptr_t drawablePtr);
uintptr_t getDrawableHitObjectPtr(HANDLE hProcess, uintptr_t drawablePtr);
uintptr_t getDrawableSliderInputManagerPtr(HANDLE hProcess, uintptr_t drawablePtr);
uintptr_t getSliderInputManagerSliderPtr(HANDLE hProcess, uintptr_t sliderInputManagerPtr);
uintptr_t getSliderHeadCirclePtr(HANDLE hProcess, uintptr_t hitObjectPtr);
uintptr_t getSliderTailCirclePtr(HANDLE hProcess, uintptr_t hitObjectPtr);

double getHitObjectStartTime(HANDLE hProcess, uintptr_t hitObjectPtr);
double getDrawableStartTime(HANDLE hProcess, uintptr_t drawablePtr);
double getEntryLifetimeEnd(HANDLE hProcess, uintptr_t entryPtr);
double getDrawableLifetimeEnd(HANDLE hProcess, uintptr_t drawablePtr);
double getSliderEndTime(HANDLE hProcess, uintptr_t hitObjectPtr);

uintptr_t getHitObjectHitWindowsPtr(HANDLE hProcess, uintptr_t hitObjectPtr);
double getHitWindowsMeh(HANDLE hProcess, uintptr_t hitWindowsPtr);

uintptr_t getDrawableResultPtr(HANDLE hProcess, uintptr_t drawablePtr);
int getDrawableResultType(HANDLE hProcess, uintptr_t drawablePtr);

uintptr_t getDrawableHitAreaPtr(HANDLE hProcess, uintptr_t drawablePtr);
int getHitAreaIsHovered(HANDLE hProcess, uintptr_t hitAreaPtr);

#endif