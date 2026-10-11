#include <windows.h>

#include "memory.h"
#include "offsets.h"
#include "osu_chain.h"
#include "osu_process.h"
#include "hook.h"

uintptr_t get_player_ptr(void) {
  uintptr_t screen_stack = read_ptr(osu_process.osu_game_desktop_ptr +
                                    osu_offsets.osu_game.screen_stack);

  uintptr_t screen_list =
      read_ptr(screen_stack + osu_offsets.screen_stack.screen_list);

  int screen_count = read_int(screen_list + osu_offsets.list.count);

  uintptr_t screen_array = read_ptr(screen_list + osu_offsets.list.array);

  uintptr_t current_screen_entry_address =
      screen_array + osu_offsets.list.first_element +
      (uintptr_t)(screen_count - 1) * osu_offsets.list.element_size;

  return read_ptr(current_screen_entry_address);
}

uintptr_t get_playfield_ptr(uintptr_t player_ptr) {
  uintptr_t drawable_ruleset =
      read_ptr(player_ptr + osu_offsets.player.drawable_ruleset);

  uintptr_t lazy_playfield =
      read_ptr(drawable_ruleset + osu_offsets.drawable_ruleset.playfield_lazy);

  return read_ptr(lazy_playfield + osu_offsets.lazy.lazy_value);
}

int get_playing_state_value(uintptr_t player_ptr) {
  uintptr_t playing_state =
      read_ptr(player_ptr + osu_offsets.player.playing_state);

  return read_int(playing_state + osu_offsets.playing_state.value);
}

double get_current_time(uintptr_t playfield_ptr) {
  uintptr_t clock = read_ptr(playfield_ptr + osu_offsets.playfield.clock);

  uintptr_t frame_stability_container =
      read_ptr(clock + osu_offsets.clock.frame_stability_container);

  return read_double(frame_stability_container +
                     osu_offsets.frame_stability_container.current_time);
}

uintptr_t get_hit_object_container_ptr(uintptr_t playfield_ptr) {
  uintptr_t lazy_hit_object_container =
      read_ptr(playfield_ptr + osu_offsets.playfield.hit_object_container_lazy);

  return read_ptr(lazy_hit_object_container + osu_offsets.lazy.lazy_value);
}

uintptr_t get_alive_drawable_map_ptr(uintptr_t hit_object_container_ptr) {
  return read_ptr(hit_object_container_ptr +
                  osu_offsets.hit_object_container.alive_drawable_map);
}

uintptr_t get_dictionary_entries_ptr(uintptr_t dict_ptr) {
  return read_ptr(dict_ptr + osu_offsets.dictionary.entries);
}

int get_dictionary_count(uintptr_t dict_ptr) {
  return read_int(dict_ptr + osu_offsets.dictionary.count);
}

uintptr_t get_dictionary_entry_ptr(uintptr_t entries_ptr, int index) {
  return entries_ptr + osu_offsets.managed_array.first_element +
         (uintptr_t)index * osu_offsets.dictionary_entry.size;
}

uintptr_t get_dictionary_entry_value_ptr(uintptr_t entry_ptr) {
  return read_ptr(entry_ptr + osu_offsets.dictionary_entry.value);
}

uintptr_t get_drawable_entry_ptr(uintptr_t drawable_ptr) {
  return read_ptr(drawable_ptr + osu_offsets.drawable_osu_hit_object.entry);
}

uintptr_t get_drawable_hit_object_ptr(uintptr_t drawable_ptr) {
  uintptr_t entry = get_drawable_entry_ptr(drawable_ptr);

  return read_ptr(entry + osu_offsets.hit_object_lifetime_entry.hit_object);
}

uintptr_t get_drawable_slider_input_manager_ptr(uintptr_t drawable_ptr) {
  return read_ptr(drawable_ptr +
                  osu_offsets.drawable_slider.slider_input_manager);
}

uintptr_t
get_slider_input_manager_slider_ptr(uintptr_t slider_input_manager_ptr) {
  return read_ptr(slider_input_manager_ptr +
                  osu_offsets.slider_input_manager.slider);
}

uintptr_t get_slider_head_circle_ptr(uintptr_t hit_object_ptr) {
  return read_ptr(hit_object_ptr + osu_offsets.slider.head_circle);
}

uintptr_t get_slider_tail_circle_ptr(uintptr_t hit_object_ptr) {
  return read_ptr(hit_object_ptr + osu_offsets.slider.tail_circle);
}

double get_hit_object_start_time(uintptr_t hit_object_ptr) {
  uintptr_t start_time_bindable =
      read_ptr(hit_object_ptr + osu_offsets.hit_object.start_time_bindable);

  return read_double(start_time_bindable + osu_offsets.bindable.value);
}

double get_drawable_start_time(uintptr_t drawable_ptr) {
  uintptr_t hit_object = get_drawable_hit_object_ptr(drawable_ptr);

  return get_hit_object_start_time(hit_object);
}

double get_entry_lifetime_end(uintptr_t entry_ptr) {
  return read_double(entry_ptr +
                     osu_offsets.hit_object_lifetime_entry.lifetime_end);
}

double get_drawable_lifetime_end(uintptr_t drawable_ptr) {
  uintptr_t entry = get_drawable_entry_ptr(drawable_ptr);

  return get_entry_lifetime_end(entry);
}

double get_slider_end_time(uintptr_t hit_object_ptr) {
  uintptr_t tail_circle = get_slider_tail_circle_ptr(hit_object_ptr);

  return get_hit_object_start_time(tail_circle);
}

uintptr_t get_hit_object_hit_windows_ptr(uintptr_t hit_object_ptr) {
  return read_ptr(hit_object_ptr + osu_offsets.hit_object.hit_windows);
}

double get_hit_windows_meh(uintptr_t hit_windows_ptr) {
  return read_double(hit_windows_ptr + osu_offsets.hit_windows.meh);
}

uintptr_t get_drawable_result_ptr(uintptr_t drawable_ptr) {
  uintptr_t entry = get_drawable_entry_ptr(drawable_ptr);

  return read_ptr(entry + osu_offsets.hit_object_lifetime_entry.result);
}

int get_drawable_result_type(uintptr_t drawable_ptr) {
  uintptr_t result = get_drawable_result_ptr(drawable_ptr);

  if (!result) {
    return 0; // HitResult.None
  }

  return read_int(result + osu_offsets.judgement_result.type);
}

uintptr_t get_drawable_hit_area_ptr(uintptr_t drawable_ptr) {
  return read_ptr(drawable_ptr + osu_offsets.drawable_osu_hit_object.hit_area);
}

int get_hit_area_is_hovered(uintptr_t hit_area_ptr) {
  return read_byte(hit_area_ptr + osu_offsets.hit_area.is_hovered);
}
