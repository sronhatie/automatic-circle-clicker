// #include <Windows.h>
// just defining the thingies ill use (did it by holding ctrl and yes shows it how its defined, im not going to learn this by memory...)
typedef long LONG;
typedef const char *LPCSTR;
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef unsigned long DWORD;
typedef unsigned __int64 ULONG_PTR, *PULONG_PTR;
typedef void *LPVOID;
typedef void *HMODULE;

#define WINAPI __stdcall

typedef int (WINAPI *FARPROC)(void);

/* LoadLibraryA and GetProcAddress doc
HMODULE LoadLibraryA(
  [in] LPCSTR lpLibFileName
);

FARPROC GetProcAddress(
  [in] HMODULE hModule,
  [in] LPCSTR  lpProcName
);
*/

__declspec(dllimport) HMODULE WINAPI LoadLibraryA(LPCSTR lpLibFileName); 
__declspec(dllimport) FARPROC WINAPI GetProcAddress(HMODULE hModule, LPCSTR lpProcName);

typedef struct tagMOUSEINPUT {
    LONG    dx;
    LONG    dy;
    DWORD   mouseData;
    DWORD   dwFlags;
    DWORD   time;
    ULONG_PTR dwExtraInfo;
} MOUSEINPUT;

typedef struct tagINPUT {
    DWORD   type;

    union // unions 
    {
        MOUSEINPUT      mi;
        /* we only use the mouseinput so these dont matter
        KEYBDINPUT    ki;
        HARDWAREINPUT hi;
        */
    }; 
} INPUT;


/*
INPUT_MOUSE 0 The event is a mouse event. Use the mi structure of the union.
MOUSEEVENTF_RIGHTDOWN 0x0008 The right button was pressed.
*/
#define INPUT_MOUSE 0
#define MOUSEEVENTF_RIGHTDOWN 0x0008

void RightClickMouse(){
    HMODULE hUser32 = LoadLibraryA("user32.dll"); // gets user32.dll handle
    typedef UINT (WINAPI *SendInputPtr)(UINT, INPUT*, int); // we use UINT, LPINPUT, int because thats how its declared as in the doc.
    // SendInputPtr is a type, not a function thats why we make mySendInput
    // GetProcAddress returns a FARPROC, we need the same value as mySendInput so we do (SendIputPtr)
    SendInputPtr mySendInput = (SendInputPtr)GetProcAddress(hUser32, "SendInput");

    INPUT input = {0};
    input.type = INPUT_MOUSE; // or you can also set it to 0 same thing
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN; // or 0x0008

    /*
    1 = number of INPUT structs you’re sending (you can send an array)
    &input = pointer to the struct
    sizeof(INPUT) = size of one INPUT struct
    */
    mySendInput(1, &input, sizeof(INPUT));
}

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