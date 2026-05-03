#include "offsets.h"

OsuOffsets osuOffsets = {
    .osuGame = {
        .screenStack = 0x5F8
    },

    .screenStack = {
        .screenList = 0x320
    },

    .list = {
        .array = 0x8,
        .count = 0x10,
        .firstElement = 0x10,
        .elementSize = 0x8
    },

    .player = {
        .drawableRuleset = 0x458,
        .playingState = 0x3D0
    },

    .drawableRuleset = {
        .playfieldLazy = 0x360
    },

    .lazy = {
        .lazyValue = 0x18
    },

    .playfield = {
        .clock = 0x80,
        .hitObjectContainerLazy = 0x320
    },

    .clock = {
        .frameStabilityContainer = 0x358
    },

    .frameStabilityContainer = {
        .currentTime = 0x30
    },

    .hitObjectContainer = {
        .aliveDrawableMap = 0x310
    },

    .dictionaryWrapper = {
        .dict = 0x8
    },

    .dictionary = {
        .entries = 0x10,
        .count = 0x38,
        .freeCount = 0x44
    },

    .managedArray = {
        .firstElement = 0x10
    },

    .dictionaryEntry = {
        .size = 0x18,
        .key = 0x0,
        .value = 0x8,
        .hashCode = 0x10,
        .next = 0x14
    },

    .drawableOsuHitObject = {
        .entry = 0x320,
        .hitArea = 0x408
    },

    .drawableSlider = {
        .sliderInputManager = 0x428
    },

    .sliderInputManager = {
        .slider = 0x208
    },

    .hitObjectLifetimeEntry = {
        .hitObject = 0x38,
        .result = 0x48,
        .lifetimeEnd = 0x20
    },

    .judgementResult = {
        .type = 0x20
    },

    .hitObject = {
        .startTimeBindable = 0x10,
        .hitWindows = 0x20
    },

    .slider = {
        .headCircle = 0x100,
        .tailCircle = 0x108
    },

    .bindable = {
        .value = 0x40
    },

    .hitWindows = {
        .great = 0x8,
        .ok = 0x10,
        .meh = 0x18
    },

    .hitArea = {
        .isHovered = 0x144
    },

    .playingState = {
        .value = 0x40
    }
};