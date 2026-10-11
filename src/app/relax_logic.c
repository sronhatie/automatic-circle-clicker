#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#include "hit_result.h"
#include "input.h"
#include "osu_chain.h"
#include "relax_logic.h"


#define EARLY_ACTION_MS 12.0
#define PLAYING_STATE_PLAYING 2
#define ACTION_NONE 0
#define ACTION_HOLD 1
#define ACTION_CLICK 2
#define CLICK_HOLD_MS 20

void run_relax(void) {
  uintptr_t player_ptr = get_player_ptr();
  int playing_state_value = get_playing_state_value(player_ptr);

  // only runs it if playing_state == 2 (Playing)
  if (playing_state_value == PLAYING_STATE_PLAYING) {
    uintptr_t playfield_ptr = get_playfield_ptr(player_ptr);
    double current_time = get_current_time(playfield_ptr);

    uintptr_t hit_object_container =
        get_hit_object_container_ptr(playfield_ptr);
    uintptr_t dict = get_alive_drawable_map_ptr(hit_object_container);
    uintptr_t entries = get_dictionary_entries_ptr(dict);
    int count = get_dictionary_count(dict);

    uintptr_t best_drawable = 0;
    double best_start_time = 999999999.0;
    int best_action = 0;

    for (int i = 0; i < count; ++i) {
      uintptr_t entry = get_dictionary_entry_ptr(entries, i);
      uintptr_t drawable = get_dictionary_entry_value_ptr(entry);
      if (!drawable) {
        continue;
      }

      uintptr_t hit_object = get_drawable_hit_object_ptr(drawable);
      if (!hit_object) {
        continue;
      }

      double start_time = 0.0;
      int action = ACTION_NONE;

      if (is_slider(drawable)) {
        if (!handle_slider(drawable, current_time, &start_time)) {
          continue;
        }
        action = ACTION_HOLD;
      } else {
        if (!handle_circle(drawable, current_time, &start_time)) {
          continue;
        }
        action = ACTION_CLICK;
      }

      // pick earliest object because multiple objects can be alive at the same
      // time
      if (start_time < best_start_time) {
        best_start_time = start_time;
        best_drawable = drawable;
        best_action = action;
      }
    }

    static int mouse_is_down = 0;

    if (best_drawable) {
      if (best_action == ACTION_HOLD) {
        if (!mouse_is_down) {
          mouseDown();
          mouse_is_down = 1;
        }
      } else if (best_action == ACTION_CLICK) {
        if (mouse_is_down) {
          mouseUp();
          mouse_is_down = 0;
        }

        mouseDown();
        Sleep(CLICK_HOLD_MS);
        // TODO: make it not use Sleep() since it blocks the whole program
        mouseUp();
      }
    } else {
      if (mouse_is_down) {
        mouseUp();
        mouse_is_down = 0;
      }
    }
  }
}

int is_slider(uintptr_t drawable_ptr) {
  // only sliders have this so it checks if the object has this, if it does its
  // a slider SliderInputManager points back to the owning drawable slider
  uintptr_t slider_input_manager =
      get_drawable_slider_input_manager_ptr(drawable_ptr);
  if (!slider_input_manager) {
    return 0;
  }

  uintptr_t slider = get_slider_input_manager_slider_ptr(slider_input_manager);

  return slider == drawable_ptr;
}

int handle_circle(uintptr_t drawable_ptr, double current_time,
                  double *out_start_time) {
  int result_type = get_drawable_result_type(drawable_ptr);
  // if its already hit ignore it (prevents clicking more than once)
  if (hit_result_is_hit(result_type)) {
    return 0;
  }

  uintptr_t hit_area = get_drawable_hit_area_ptr(drawable_ptr);
  if (!hit_area) {
    return 0;
  }

  int is_hovered = get_hit_area_is_hovered(hit_area);
  if (!is_hovered) {
    return 0;
  }

  uintptr_t hit_object = get_drawable_hit_object_ptr(drawable_ptr);
  double start_time = get_hit_object_start_time(hit_object);
  uintptr_t hit_windows = get_hit_object_hit_windows_ptr(hit_object);
  double meh_window = get_hit_windows_meh(hit_windows);

  // negative = too early
  // 0        = exactly on time
  // positive = late
  double time_offset = current_time - start_time;

  // clicks earlier to compensate for delay
  if (current_time < start_time - EARLY_ACTION_MS) {
    return 0;
  }

  // if too late, ignore it
  if (time_offset > meh_window) {
    return 0;
  }

  *out_start_time = start_time;
  // circle is valid only if it is unhit, hovered, and inside its hit window
  return 1;
}

int handle_slider(uintptr_t drawable_ptr, double current_time,
                  double *out_start_time) {
  int result_type = get_drawable_result_type(drawable_ptr);
  if (hit_result_is_hit(result_type)) {
    return 0;
  }

  uintptr_t hit_object = get_drawable_hit_object_ptr(drawable_ptr);
  if (!hit_object) {
    return 0;
  }

  double start_time = get_hit_object_start_time(hit_object);
  double end_time = get_slider_end_time(hit_object);

  // clicks earlier to compensate for delay
  if (current_time < start_time - EARLY_ACTION_MS) {
    return 0;
  }

  // slider already ended
  if (current_time > end_time) {
    return 0;
  }

  *out_start_time = start_time;
  return 1;
}
