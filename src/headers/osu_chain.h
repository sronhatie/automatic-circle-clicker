#pragma once

#include <windows.h>
#include <stdint.h>

uintptr_t get_osu_game_desktop_ptr(HANDLE process_handle, DWORD process_id);
uintptr_t get_player_ptr(HANDLE process_handle, uintptr_t osu_game_desktop_ptr);
uintptr_t get_playfield_ptr(HANDLE process_handle, uintptr_t player_ptr);
int get_playing_state_value(HANDLE process_handle, uintptr_t player_ptr);
double get_current_time(HANDLE process_handle, uintptr_t playfield_ptr);
uintptr_t get_hit_object_container_ptr(HANDLE process_handle,
                                       uintptr_t playfield_ptr);
uintptr_t get_alive_drawable_map_ptr(HANDLE process_handle,
                                     uintptr_t hit_object_container_ptr);
uintptr_t get_dictionary_entries_ptr(HANDLE process_handle, uintptr_t dict_ptr);
int get_dictionary_count(HANDLE process_handle, uintptr_t dict_ptr);
uintptr_t get_dictionary_entry_ptr(uintptr_t entries_ptr, int index);
uintptr_t get_dictionary_entry_value_ptr(HANDLE process_handle, uintptr_t entry_ptr);
uintptr_t get_drawable_entry_ptr(HANDLE process_handle, uintptr_t drawable_ptr);
uintptr_t get_drawable_hit_object_ptr(HANDLE process_handle, uintptr_t drawable_ptr);
uintptr_t get_drawable_slider_input_manager_ptr(HANDLE process_handle,
                                                uintptr_t drawable_ptr);
uintptr_t
get_slider_input_manager_slider_ptr(HANDLE process_handle,
                                    uintptr_t slider_input_manager_ptr);
uintptr_t get_slider_head_circle_ptr(HANDLE process_handle,
                                     uintptr_t hit_object_ptr);
uintptr_t get_slider_tail_circle_ptr(HANDLE process_handle,
                                     uintptr_t hit_object_ptr);
double get_hit_object_start_time(HANDLE process_handle, uintptr_t hit_object_ptr);
double get_drawable_start_time(HANDLE process_handle, uintptr_t drawable_ptr);
double get_entry_lifetime_end(HANDLE process_handle, uintptr_t entry_ptr);
double get_drawable_lifetime_end(HANDLE process_handle, uintptr_t drawable_ptr);
double get_slider_end_time(HANDLE process_handle, uintptr_t hit_object_ptr);
uintptr_t get_hit_object_hit_windows_ptr(HANDLE process_handle,
                                         uintptr_t hit_object_ptr);
double get_hit_windows_meh(HANDLE process_handle, uintptr_t hit_windows_ptr);
uintptr_t get_drawable_result_ptr(HANDLE process_handle, uintptr_t drawable_ptr);
int get_drawable_result_type(HANDLE process_handle, uintptr_t drawable_ptr);
uintptr_t get_drawable_hit_area_ptr(HANDLE process_handle, uintptr_t drawable_ptr);
int get_hit_area_is_hovered(HANDLE process_handle, uintptr_t hit_area_ptr);
