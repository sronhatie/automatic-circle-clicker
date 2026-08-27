#include "offsets.h"

osu_offsets_t osu_offsets = {
    .osu_game = {
        .screen_stack = 0x610
    },

    .screen_stack = {
        .screen_list = 0x320
    },

    .list = {
        .array = 0x8,
        .count = 0x10,
        .first_element = 0x10,
        .element_size = 0x8
    },

    .player = {
        .drawable_ruleset = 0x458,
        .playing_state = 0x3D0
    },

    .drawable_ruleset = {
        .playfield_lazy = 0x360
    },

    .lazy = {
        .lazy_value = 0x18
    },

    .playfield = {
        .clock = 0x80,
        .hit_object_container_lazy = 0x320
    },

    .clock = {
        .frame_stability_container = 0x358
    },

    .frame_stability_container = {
        .current_time = 0x30
    },

    .hit_object_container = {
        .alive_drawable_map = 0x310
    },

    .dictionary_wrapper = {
        .dict = 0x8
    },

    .dictionary = {
        .entries = 0x10,
        .count = 0x38,
        .free_count = 0x44
    },

    .managed_array = {
        .first_element = 0x10
    },

    .dictionary_entry = {
        .size = 0x18,
        .key = 0x0,
        .value = 0x8,
        .hash_code = 0x10,
        .next = 0x14
    },

    .drawable_osu_hit_object = {
        .entry = 0x320,
        .hit_area = 0x408
    },

    .drawable_slider = {
        .slider_input_manager = 0x428
    },

    .slider_input_manager = {
        .slider = 0x208
    },

    .hit_object_lifetime_entry = {
        .hit_object = 0x38,
        .result = 0x48,
        .lifetime_end = 0x20
    },

    .judgement_result = {
        .type = 0x20
    },

    .hit_object = {
        .start_time_bindable = 0x10,
        .hit_windows = 0x20
    },

    .slider = {
        .head_circle = 0x100,
        .tail_circle = 0x108
    },

    .bindable = {
        .value = 0x40
    },

    .hit_windows = {
        .great = 0x8,
        .ok = 0x10,
        .meh = 0x18
    },

    .hit_area = {
        .is_hovered = 0x144
    },

    .playing_state = {
        .value = 0x40
    }
};