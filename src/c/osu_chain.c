#include <windows.h>

#include "asm_functions.h"
#include "debugging.h"
#include "memory.h"
#include "offsets.h"
#include "osu_chain.h"
#include "signatures.h"

uintptr_t get_osu_game_desktop_ptr(HANDLE process_handle, DWORD process_id) {
  uintptr_t update_after_children_addr = find_pattern_in_process(
      process_handle, update_after_children_signature, update_after_children_mask);

  BYTE original_byte = 0;

  ReadProcessMemory(process_handle, (LPCVOID)update_after_children_addr,
                    &original_byte, 1, NULL);

  DebugActiveProcess(process_id);

  // TODO: Check if this fails. It silently fails if another debugger
  // is already attached to the process.
  DebugSetProcessKillOnExit(FALSE);

  // Removes the initial attach breakpoint (0xCC / int3).
  wait_for_initial_attach_breakpoint();

  writeOneByte(process_handle, update_after_children_addr, 0xCC);

  // RCX contains OsuGameDesktop* at UpdateAfterChildren.
  uintptr_t osu_game_desktop_ptr = capture_breakpoint_rcx(
      process_handle, update_after_children_addr, original_byte);

  DebugActiveProcessStop(process_id);

  return osu_game_desktop_ptr;
}

uintptr_t get_player_ptr(HANDLE process_handle, uintptr_t osu_game_desktop_ptr) {
  uintptr_t screen_stack = read_ptr(
      process_handle, osu_game_desktop_ptr + osu_offsets.osu_game.screen_stack);

  uintptr_t screen_list =
      read_ptr(process_handle, screen_stack + osu_offsets.screen_stack.screen_list);

  int screen_count = read_int(process_handle, screen_list + osu_offsets.list.count);

  uintptr_t screen_array =
      read_ptr(process_handle, screen_list + osu_offsets.list.array);

  uintptr_t current_screen_entry_address =
      screen_array + osu_offsets.list.first_element +
      (uintptr_t)(screen_count - 1) * osu_offsets.list.element_size;

  return read_ptr(process_handle, current_screen_entry_address);
}

uintptr_t get_playfield_ptr(HANDLE process_handle, uintptr_t player_ptr) {
  uintptr_t drawable_ruleset =
      read_ptr(process_handle, player_ptr + osu_offsets.player.drawable_ruleset);

  uintptr_t lazy_playfield =
      read_ptr(process_handle,
               drawable_ruleset + osu_offsets.drawable_ruleset.playfield_lazy);

  return read_ptr(process_handle, lazy_playfield + osu_offsets.lazy.lazy_value);
}

int get_playing_state_value(HANDLE process_handle, uintptr_t player_ptr) {
  uintptr_t playing_state =
      read_ptr(process_handle, player_ptr + osu_offsets.player.playing_state);

  return read_int(process_handle, playing_state + osu_offsets.playing_state.value);
}

double get_current_time(HANDLE process_handle, uintptr_t playfield_ptr) {
  uintptr_t clock =
      read_ptr(process_handle, playfield_ptr + osu_offsets.playfield.clock);

  uintptr_t frame_stability_container =
      read_ptr(process_handle, clock + osu_offsets.clock.frame_stability_container);

  return read_double(process_handle,
                     frame_stability_container +
                         osu_offsets.frame_stability_container.current_time);
}

uintptr_t get_hit_object_container_ptr(HANDLE process_handle,
                                       uintptr_t playfield_ptr) {
  uintptr_t lazy_hit_object_container =
      read_ptr(process_handle,
               playfield_ptr + osu_offsets.playfield.hit_object_container_lazy);

  return read_ptr(process_handle,
                  lazy_hit_object_container + osu_offsets.lazy.lazy_value);
}

uintptr_t get_alive_drawable_map_ptr(HANDLE process_handle,
                                     uintptr_t hit_object_container_ptr) {
  return read_ptr(process_handle,
                  hit_object_container_ptr +
                      osu_offsets.hit_object_container.alive_drawable_map);
}

uintptr_t get_dictionary_entries_ptr(HANDLE process_handle, uintptr_t dict_ptr) {
  return read_ptr(process_handle, dict_ptr + osu_offsets.dictionary.entries);
}

int get_dictionary_count(HANDLE process_handle, uintptr_t dict_ptr) {
  return read_int(process_handle, dict_ptr + osu_offsets.dictionary.count);
}

uintptr_t get_dictionary_entry_ptr(uintptr_t entries_ptr, int index) {
  return entries_ptr + osu_offsets.managed_array.first_element +
         (uintptr_t)index * osu_offsets.dictionary_entry.size;
}

uintptr_t get_dictionary_entry_value_ptr(HANDLE process_handle,
                                         uintptr_t entry_ptr) {
  return read_ptr(process_handle, entry_ptr + osu_offsets.dictionary_entry.value);
}

uintptr_t get_drawable_entry_ptr(HANDLE process_handle, uintptr_t drawable_ptr) {
  return read_ptr(process_handle,
                  drawable_ptr + osu_offsets.drawable_osu_hit_object.entry);
}

uintptr_t get_drawable_hit_object_ptr(HANDLE process_handle,
                                      uintptr_t drawable_ptr) {
  uintptr_t entry = get_drawable_entry_ptr(process_handle, drawable_ptr);

  return read_ptr(process_handle,
                  entry + osu_offsets.hit_object_lifetime_entry.hit_object);
}

uintptr_t get_drawable_slider_input_manager_ptr(HANDLE process_handle,
                                                uintptr_t drawable_ptr) {
  return read_ptr(process_handle,
                  drawable_ptr +
                      osu_offsets.drawable_slider.slider_input_manager);
}

uintptr_t
get_slider_input_manager_slider_ptr(HANDLE process_handle,
                                    uintptr_t slider_input_manager_ptr) {
  return read_ptr(process_handle, slider_input_manager_ptr +
                                 osu_offsets.slider_input_manager.slider);
}

uintptr_t get_slider_head_circle_ptr(HANDLE process_handle,
                                     uintptr_t hit_object_ptr) {
  return read_ptr(process_handle, hit_object_ptr + osu_offsets.slider.head_circle);
}

uintptr_t get_slider_tail_circle_ptr(HANDLE process_handle,
                                     uintptr_t hit_object_ptr) {
  return read_ptr(process_handle, hit_object_ptr + osu_offsets.slider.tail_circle);
}

double get_hit_object_start_time(HANDLE process_handle, uintptr_t hit_object_ptr) {
  uintptr_t start_time_bindable = read_ptr(
      process_handle, hit_object_ptr + osu_offsets.hit_object.start_time_bindable);

  return read_double(process_handle,
                     start_time_bindable + osu_offsets.bindable.value);
}

double get_drawable_start_time(HANDLE process_handle, uintptr_t drawable_ptr) {
  uintptr_t hit_object = get_drawable_hit_object_ptr(process_handle, drawable_ptr);

  return get_hit_object_start_time(process_handle, hit_object);
}

double get_entry_lifetime_end(HANDLE process_handle, uintptr_t entry_ptr) {
  return read_double(process_handle,
                     entry_ptr +
                         osu_offsets.hit_object_lifetime_entry.lifetime_end);
}

double get_drawable_lifetime_end(HANDLE process_handle, uintptr_t drawable_ptr) {
  uintptr_t entry = get_drawable_entry_ptr(process_handle, drawable_ptr);

  return get_entry_lifetime_end(process_handle, entry);
}

double get_slider_end_time(HANDLE process_handle, uintptr_t hit_object_ptr) {
  uintptr_t tail_circle = get_slider_tail_circle_ptr(process_handle, hit_object_ptr);

  return get_hit_object_start_time(process_handle, tail_circle);
}

uintptr_t get_hit_object_hit_windows_ptr(HANDLE process_handle,
                                         uintptr_t hit_object_ptr) {
  return read_ptr(process_handle,
                  hit_object_ptr + osu_offsets.hit_object.hit_windows);
}

double get_hit_windows_meh(HANDLE process_handle, uintptr_t hit_windows_ptr) {
  return read_double(process_handle, hit_windows_ptr + osu_offsets.hit_windows.meh);
}

uintptr_t get_drawable_result_ptr(HANDLE process_handle, uintptr_t drawable_ptr) {
  uintptr_t entry = get_drawable_entry_ptr(process_handle, drawable_ptr);

  return read_ptr(process_handle,
                  entry + osu_offsets.hit_object_lifetime_entry.result);
}

int get_drawable_result_type(HANDLE process_handle, uintptr_t drawable_ptr) {
  uintptr_t result = get_drawable_result_ptr(process_handle, drawable_ptr);

  if (!result) {
    return 0; // HitResult.None
  }

  return read_int(process_handle, result + osu_offsets.judgement_result.type);
}

uintptr_t get_drawable_hit_area_ptr(HANDLE process_handle, uintptr_t drawable_ptr) {
  return read_ptr(process_handle,
                  drawable_ptr + osu_offsets.drawable_osu_hit_object.hit_area);
}

int get_hit_area_is_hovered(HANDLE process_handle, uintptr_t hit_area_ptr) {
  return read_byte(process_handle, hit_area_ptr + osu_offsets.hit_area.is_hovered);
}