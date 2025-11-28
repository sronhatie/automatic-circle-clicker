#include <stdio.h>
#include <Windows.h>

#include "asmFunctions.h"
#include "cFunctions.h"

const char DLLName[] = "user32.dll";
const char APIname[] = "SendInput";
const int MOUSE_INPUT = 0;

/* SendInput documentation
UINT SendInput(
  [in] UINT    cInputs,
  [in] LPINPUT pInputs,
  [in] int     cbSize
);
*/

/* INPUT documentation
typedef struct tagINPUT {
  DWORD type;
  union {
    MOUSEINPUT    mi;
    KEYBDINPUT    ki;
    HARDWAREINPUT hi;
  } DUMMYUNIONNAME;
} INPUT, *PINPUT, *LPINPUT;
*/

/* MOUSE_INPUT documentations
typedef struct tagMOUSEINPUT {
  LONG      dx;
  LONG      dy;
  DWORD     mouseData;
  DWORD     dwFlags;
  DWORD     time;
  ULONG_PTR dwExtraInfo;
} MOUSEINPUT, *PMOUSEINPUT, *LPMOUSEINPUT;
*/

int main(){
    HMODULE h_user32 = LoadLibraryA(DLLName); // gets user32.dll handle
    typedef UINT (WINAPI *SendInputPtr)(UINT, LPINPUT, int); // we use UINT, LPINPUT, int because thats how its declared as in the doc.
    // SendInputPtr is a type, not a function thats why we make mySendInput
    // GetProcAdress returns a FARPROC, we need the same value as mySendInput so we do (SendIputPtr)
    SendInputPtr mySendInput = (SendInputPtr)GetProcAddress(h_user32, APIname);
    INPUT input = {0}; // zero out the structure
    input.type = INPUT_MOUSE; // or you can also set it to 0 same thing
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN; // or 0x0002 

    /*
    1 = number of INPUT structs you’re sending (you can send an array)
    &input = pointer to the struct
    sizeof(INPUT) = size of one INPUT struct
    */
    mySendInput(1, &input, sizeof(INPUT));


    return 0;
}