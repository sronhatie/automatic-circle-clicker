#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "asm_functions.h"
#include "osu_chain.h"
#include "osu_process.h"

osu_process_t osu_process = {0};

void osu_process_attach(void) {
  char *process_name = "osu!.exe";
  osu_process.process_id = findPID(process_name);
  if (!osu_process.process_id) {
    printf("Osu not open\n");
    exit(1);
  }

  // OPERATION allows to change memory pages, INFORMATION gets info about the
  // process
  osu_process.process_handle =
      OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION |
                      PROCESS_QUERY_INFORMATION,
                  FALSE, osu_process.process_id);

  osu_process.osu_game_desktop_ptr = get_osu_game_desktop_ptr();
}
