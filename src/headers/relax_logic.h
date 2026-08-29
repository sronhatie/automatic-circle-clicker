#pragma once

#include <stdint.h>
#include <windows.h>

void run_relax(void);
int is_slider(uintptr_t drawable_ptr);
int handle_circle(uintptr_t drawable_ptr, double current_time,
                  double *out_start_time);
int handle_slider(uintptr_t drawable_ptr, double current_time,
                  double *out_start_time);
