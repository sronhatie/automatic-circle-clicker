#pragma once

#include <windows.h>
#include <stdint.h>

int is_slider(HANDLE process_handle, uintptr_t drawable_ptr);
int handle_circle(HANDLE process_handle, uintptr_t drawable_ptr, double current_time,
                 double *out_start_time);
int handle_slider(HANDLE process_handle, uintptr_t drawable_ptr, double current_time,
                 double *out_start_time);

void run_relax(HANDLE process_handle, uintptr_t osu_game_desktop_ptr);
