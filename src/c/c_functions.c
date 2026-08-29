#include <stdio.h>
#include <windows.h>


#include "c_functions.h"

#define KEY 'Q'
#define KEY_DOWN_MASK 0x8000

// function pointer type for dynamically loaded GetAsyncKeyState
typedef SHORT(WINAPI *get_async_key_state_ptr)(int);

int key_was_pressed(void) {
  int was_pressed = 0;
  static int previous_was_pressed = 0;
  // cashed so theyre resolved only once
  static get_async_key_state_ptr p_get_async_key_state = NULL;
  static HMODULE user32_handle;

  if (p_get_async_key_state == NULL) {
    user32_handle = LoadLibrary("user32.dll");
    if (user32_handle == NULL) {
      printf("Failed to load user32.dll\n");
      return 0;
    }

    p_get_async_key_state = (get_async_key_state_ptr)GetProcAddress(
        user32_handle, "GetAsyncKeyState");
    if (p_get_async_key_state == NULL) {
      printf("Failed to make pointer to getAsyncKeyState\n");
      return 0;
    }
  }

  if (p_get_async_key_state(KEY) &
      KEY_DOWN_MASK) { // & is the bitwise AND operand
    was_pressed = 1;
  }

  // only returns 1 for a press (doesnt return 1 if you hold it)
  if (!previous_was_pressed && was_pressed) {
    previous_was_pressed = 1;
  } else if (previous_was_pressed && was_pressed) {
    was_pressed = 0;
  } else {
    previous_was_pressed = 0;
  }

  return was_pressed;
}