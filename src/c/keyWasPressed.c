#include <windows.h>

#define KEY 'Q'

int keyWasPressed(){
    typedef SHORT (WINAPI *getAsyncKeyStatePtr)(int);
    int wasPressed = 0;

    HMODULE hUser32 = LoadLibrary("user32.dll");
    if(hUser32 == NULL){
        printf("Failed to load user32.dll\n");
        return 0;
    }

    getAsyncKeyStatePtr pGetAsyncKeyState = (getAsyncKeyStatePtr)GetProcAddress(hUser32, "GetAsyncKeyState");
    if(pGetAsyncKeyState == NULL){
        printf("Failed to make pointer to getAsyncKeyState\n");
        return 0;
    }

    if(pGetAsyncKeyState(KEY) && 0x8000){
        printf("Key was pressed\n");
        wasPressed = 1;
    }

    FreeLibrary(hUser32);
    return wasPressed;
}