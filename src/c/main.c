#include <stdio.h>
#include <Windows.h>

#include "asmFunctions.h"

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

int main(){
    HMODULE h_user32 = LoadLibraryA(DLLName); // gets user32.dll handle
    


    return 0;
}