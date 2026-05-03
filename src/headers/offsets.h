#ifndef OFFSETS_H
#define OFFSETS_H

#include <stdint.h>

typedef struct{
    uintptr_t screenStack;
} OsuGameOffsets;

typedef struct{
    uintptr_t screenList;
} ScreenStackOffsets;

typedef struct{
    uintptr_t array;
    uintptr_t count;
    uintptr_t firstElement;
    uintptr_t elementSize;
} ListOffsets;

typedef struct{
    uintptr_t drawableRuleset;
    uintptr_t playingState;
} PlayerOffsets;

typedef struct{
    uintptr_t playfieldLazy;
} DrawableOsuRulesetOffsets;

typedef struct{
    uintptr_t lazyValue;
} LazyOffsets;

typedef struct{
    uintptr_t clock;
    uintptr_t hitObjectContainerLazy;
} PlayfieldOffsets;

typedef struct{
    uintptr_t frameStabilityContainer;
} ClockOffsets;

typedef struct{
    uintptr_t currentTime;
} FrameStabilityContainerOffsets;

typedef struct{
    uintptr_t aliveDrawableMap;
} HitObjectContainerOffsets;

typedef struct{
    uintptr_t dict;
} SlimReadOnlyDictionaryWrapperOffsets;

typedef struct{
    uintptr_t entries;
    uintptr_t count;
    uintptr_t freeCount;
} DictionaryOffsets;

typedef struct{
    uintptr_t firstElement;
} ManagedArrayOffsets;

typedef struct{
    uintptr_t size;
    uintptr_t key;
    uintptr_t value;
    uintptr_t hashCode;
    uintptr_t next;
} DictionaryEntryOffsets;

typedef struct{
    uintptr_t entry;
    uintptr_t hitArea;
} DrawableOsuHitObjectOffsets;

typedef struct{
    uintptr_t sliderInputManager;
} DrawableSliderOffsets;

typedef struct{
    uintptr_t slider;
} SliderInputManagerOffsets;

typedef struct{
    uintptr_t hitObject;
    uintptr_t result;
    uintptr_t lifetimeEnd;
} HitObjectLifetimeEntryOffsets;

typedef struct{
    uintptr_t type;
} JudgementResultOffsets;

typedef struct{
    uintptr_t startTimeBindable;
    uintptr_t hitWindows;
} HitObjectOffsets;

typedef struct{
    uintptr_t headCircle;
    uintptr_t tailCircle;
} SliderOffsets;

typedef struct{
    uintptr_t value;
} BindableOffsets;

typedef struct{
    uintptr_t great;
    uintptr_t ok;
    uintptr_t meh;
} HitWindowsOffsets;

typedef struct{
    uintptr_t isHovered;
} HitAreaOffsets;

typedef struct{
    uintptr_t value;
} PlayingStateOffsets;

typedef struct{
    OsuGameOffsets osuGame;
    ScreenStackOffsets screenStack;
    ListOffsets list;

    PlayerOffsets player;
    DrawableOsuRulesetOffsets drawableRuleset;
    LazyOffsets lazy;
    PlayfieldOffsets playfield;
    ClockOffsets clock;
    FrameStabilityContainerOffsets frameStabilityContainer;

    HitObjectContainerOffsets hitObjectContainer;
    SlimReadOnlyDictionaryWrapperOffsets dictionaryWrapper;
    DictionaryOffsets dictionary;
    ManagedArrayOffsets managedArray;
    DictionaryEntryOffsets dictionaryEntry;

    DrawableOsuHitObjectOffsets drawableOsuHitObject;
    DrawableSliderOffsets drawableSlider;
    SliderInputManagerOffsets sliderInputManager;
    HitObjectLifetimeEntryOffsets hitObjectLifetimeEntry;
    JudgementResultOffsets judgementResult;
    HitObjectOffsets hitObject;
    SliderOffsets slider;
    BindableOffsets bindable;
    HitWindowsOffsets hitWindows;
    HitAreaOffsets hitArea;
    PlayingStateOffsets playingState;
} OsuOffsets;

extern OsuOffsets osuOffsets;

#endif