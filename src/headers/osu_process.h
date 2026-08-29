#pragma once

#include <stdint.h>
#include <windows.h>

typedef struct {
  DWORD process_id;
  HANDLE process_handle;
  uintptr_t osu_game_desktop_ptr;
} osu_process_t;

extern osu_process_t osu_process;

void osu_process_attach(void);
