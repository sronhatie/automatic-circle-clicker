#include <stdint.h>
#include <stdio.h>

#include "memory.h"
#include "offsets.h"
#include "osu_process.h"

void testing(void) {
  osu_process_attach();

  if (!osu_process.process_handle || !osu_process.osu_game_desktop_ptr) {
    printf("Failed to attach to osu\n");
    return;
  }

  printf("osu_game_desktop_ptr: %p\n",
         (void *)osu_process.osu_game_desktop_ptr);

  uintptr_t screen_stack = read_ptr(osu_process.osu_game_desktop_ptr +
                                    osu_offsets.osu_game.screen_stack);
  printf("screen_stack: %p\n", (void *)screen_stack);

  uintptr_t screen_list =
      read_ptr(screen_stack + osu_offsets.screen_stack.screen_list);
  printf("screen_list: %p\n", (void *)screen_list);

  int screen_count = read_int(screen_list + osu_offsets.list.count);
  printf("screen_count: %d\n", screen_count);

  uintptr_t screen_array = read_ptr(screen_list + osu_offsets.list.array);
  printf("screen_array: %p\n", (void *)screen_array);

  uintptr_t current_screen_entry_address =
      screen_array + osu_offsets.list.first_element +
      (uintptr_t)(screen_count - 1) * osu_offsets.list.element_size;
  printf("current_screen_entry_address: %p\n",
         (void *)current_screen_entry_address);

  uintptr_t player_ptr = read_ptr(current_screen_entry_address);
  printf("player_ptr: %p\n", (void *)player_ptr);

  uintptr_t playing_state =
      read_ptr(player_ptr + osu_offsets.player.playing_state);
  printf("playing_state ptr: %p\n", (void *)playing_state);

  int playing_state_value =
      read_int(playing_state + osu_offsets.playing_state.value);
  printf("playing_state value: %d\n", playing_state_value);

  uintptr_t drawable_ruleset =
      read_ptr(player_ptr + osu_offsets.player.drawable_ruleset);
  printf("drawable_ruleset: %p\n", (void *)drawable_ruleset);

  uintptr_t lazy_playfield =
      read_ptr(drawable_ruleset + osu_offsets.drawable_ruleset.playfield_lazy);
  printf("lazy_playfield: %p\n", (void *)lazy_playfield);

  uintptr_t playfield_ptr =
      read_ptr(lazy_playfield + osu_offsets.lazy.lazy_value);
  printf("playfield_ptr: %p\n", (void *)playfield_ptr);

  uintptr_t clock = read_ptr(playfield_ptr + osu_offsets.playfield.clock);
  printf("clock: %p\n", (void *)clock);

  uintptr_t framed_clock =
      read_ptr(clock + osu_offsets.clock.frame_stability_container);
  printf("framed_clock: %p\n", (void *)framed_clock);

  double current_time = read_double(
      framed_clock + osu_offsets.frame_stability_container.current_time);
  printf("current_time: %.3f\n", current_time);

  uintptr_t lazy_hit_object_container =
      read_ptr(playfield_ptr + osu_offsets.playfield.hit_object_container_lazy);
  printf("lazy_hit_object_container: %p\n", (void *)lazy_hit_object_container);

  uintptr_t hit_object_container =
      read_ptr(lazy_hit_object_container + osu_offsets.lazy.lazy_value);
  printf("hit_object_container: %p\n", (void *)hit_object_container);

  uintptr_t dictionary_ptr =
      read_ptr(hit_object_container +
               osu_offsets.hit_object_container.alive_drawable_map);
  printf("alive_drawable_map/dictionary: %p\n", (void *)dictionary_ptr);

  uintptr_t entries = read_ptr(dictionary_ptr + osu_offsets.dictionary.entries);
  printf("entries: %p\n", (void *)entries);

  int count = read_int(dictionary_ptr + osu_offsets.dictionary.count);
  printf("count: %d\n", count);
}
