#pragma once

#include <stdint.h>

uintptr_t get_osu_game_desktop_ptr(void);
uintptr_t find_pattern(HANDLE process_handle, unsigned char *signature,
                       char *mask);
