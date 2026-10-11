#include <stdint.h>
#include <stdio.h>
#include <windows.h>

#include "logic.h"
#include "osu_process.h"
#include "relax_logic.h"

void start(void) {
  osu_process_attach();
  // currently this just prints out the OsuGame pointer so i know if the program
  // is running (otherwise it silently crashes)
  printf("OsuGame ptr = %p\n", (void *)osu_process.osu_game_desktop_ptr);

  while (1) {
    run_relax();

    Sleep(10);
  }
}
