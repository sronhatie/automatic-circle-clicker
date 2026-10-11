#pragma once

#include <stdint.h>

uintptr_t get_player_ptr(void);
uintptr_t get_playfield_ptr(uintptr_t player_ptr);
int get_playing_state_value(uintptr_t player_ptr);
double get_current_time(uintptr_t playfield_ptr);
uintptr_t get_hit_object_container_ptr(uintptr_t playfield_ptr);
uintptr_t get_alive_drawable_map_ptr(uintptr_t hit_object_container_ptr);
uintptr_t get_dictionary_entries_ptr(uintptr_t dict_ptr);
int get_dictionary_count(uintptr_t dict_ptr);
uintptr_t get_dictionary_entry_ptr(uintptr_t entries_ptr, int index);
uintptr_t get_dictionary_entry_value_ptr(uintptr_t entry_ptr);
uintptr_t get_drawable_entry_ptr(uintptr_t drawable_ptr);
uintptr_t get_drawable_hit_object_ptr(uintptr_t drawable_ptr);
uintptr_t get_drawable_slider_input_manager_ptr(uintptr_t drawable_ptr);
uintptr_t
get_slider_input_manager_slider_ptr(uintptr_t slider_input_manager_ptr);
uintptr_t get_slider_head_circle_ptr(uintptr_t hit_object_ptr);
uintptr_t get_slider_tail_circle_ptr(uintptr_t hit_object_ptr);
double get_hit_object_start_time(uintptr_t hit_object_ptr);
double get_drawable_start_time(uintptr_t drawable_ptr);
double get_entry_lifetime_end(uintptr_t entry_ptr);
double get_drawable_lifetime_end(uintptr_t drawable_ptr);
double get_slider_end_time(uintptr_t hit_object_ptr);
uintptr_t get_hit_object_hit_windows_ptr(uintptr_t hit_object_ptr);
double get_hit_windows_meh(uintptr_t hit_windows_ptr);
uintptr_t get_drawable_result_ptr(uintptr_t drawable_ptr);
int get_drawable_result_type(uintptr_t drawable_ptr);
uintptr_t get_drawable_hit_area_ptr(uintptr_t drawable_ptr);
int get_hit_area_is_hovered(uintptr_t hit_area_ptr);
