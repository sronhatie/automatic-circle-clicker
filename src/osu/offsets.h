#pragma once

#include <stdint.h>

typedef struct {
  uintptr_t screen_stack;
} osu_game_offsets_t;

typedef struct {
  uintptr_t screen_list;
} screen_stack_offsets_t;

typedef struct {
  uintptr_t array;
  uintptr_t count;
  uintptr_t first_element;
  uintptr_t element_size;
} list_offsets_t;

typedef struct {
  uintptr_t drawable_ruleset;
  uintptr_t playing_state;
} player_offsets_t;

typedef struct {
  uintptr_t playfield_lazy;
} drawable_osu_ruleset_offsets_t;

typedef struct {
  uintptr_t lazy_value;
} lazy_offsets_t;

typedef struct {
  uintptr_t clock;
  uintptr_t hit_object_container_lazy;
} playfield_offsets_t;

typedef struct {
  uintptr_t frame_stability_container;
} clock_offsets_t;

typedef struct {
  uintptr_t current_time;
} frame_stability_container_offsets_t;

typedef struct {
  uintptr_t alive_drawable_map;
} hit_object_container_offsets_t;

typedef struct {
  uintptr_t dict;
} slim_read_only_dictionary_wrapper_offsets_t;

typedef struct {
  uintptr_t entries;
  uintptr_t count;
  uintptr_t free_count;
} dictionary_offsets_t;

typedef struct {
  uintptr_t first_element;
} managed_array_offsets_t;

typedef struct {
  uintptr_t size;
  uintptr_t key;
  uintptr_t value;
  uintptr_t hash_code;
  uintptr_t next;
} dictionary_entry_offsets_t;

typedef struct {
  uintptr_t entry;
  uintptr_t hit_area;
} drawable_osu_hit_object_offsets_t;

typedef struct {
  uintptr_t slider_input_manager;
} drawable_slider_offsets_t;

typedef struct {
  uintptr_t slider;
} slider_input_manager_offsets_t;

typedef struct {
  uintptr_t hit_object;
  uintptr_t result;
  uintptr_t lifetime_end;
} hit_object_lifetime_entry_offsets_t;

typedef struct {
  uintptr_t type;
} judgement_result_offsets_t;

typedef struct {
  uintptr_t start_time_bindable;
  uintptr_t hit_windows;
} hit_object_offsets_t;

typedef struct {
  uintptr_t head_circle;
  uintptr_t tail_circle;
} slider_offsets_t;

typedef struct {
  uintptr_t value;
} bindable_offsets_t;

typedef struct {
  uintptr_t great;
  uintptr_t ok;
  uintptr_t meh;
} hit_windows_offsets_t;

typedef struct {
  uintptr_t is_hovered;
} hit_area_offsets_t;

typedef struct {
  uintptr_t value;
} playing_state_offsets_t;

typedef struct {
  osu_game_offsets_t osu_game;
  screen_stack_offsets_t screen_stack;
  list_offsets_t list;
  player_offsets_t player;
  drawable_osu_ruleset_offsets_t drawable_ruleset;
  lazy_offsets_t lazy;
  playfield_offsets_t playfield;
  clock_offsets_t clock;
  frame_stability_container_offsets_t frame_stability_container;
  hit_object_container_offsets_t hit_object_container;
  slim_read_only_dictionary_wrapper_offsets_t dictionary_wrapper;
  dictionary_offsets_t dictionary;
  managed_array_offsets_t managed_array;
  dictionary_entry_offsets_t dictionary_entry;
  drawable_osu_hit_object_offsets_t drawable_osu_hit_object;
  drawable_slider_offsets_t drawable_slider;
  slider_input_manager_offsets_t slider_input_manager;
  hit_object_lifetime_entry_offsets_t hit_object_lifetime_entry;
  judgement_result_offsets_t judgement_result;
  hit_object_offsets_t hit_object;
  slider_offsets_t slider;
  bindable_offsets_t bindable;
  hit_windows_offsets_t hit_windows;
  hit_area_offsets_t hit_area;
  playing_state_offsets_t playing_state;
} osu_offsets_t;

extern osu_offsets_t osu_offsets;
