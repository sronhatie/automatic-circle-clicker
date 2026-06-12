/*
Problems: 
 - 
*/

#include <windows.h>

#define KEY 'Q'
#define KEY_DOWN_MASK 0x8000

// function pointer type for dynamically loaded GetAsyncKeyState
typedef SHORT (WINAPI *getAsyncKeyStatePtr)(int);

int keyWasPressed(){
    int wasPressed = 0;
    static int previousWasPressed = 0;
    // cashed so theyre resolved only once
    static getAsyncKeyStatePtr pGetAsyncKeyState = NULL;
    static HMODULE hUser32;

    if(pGetAsyncKeyState == NULL){
        hUser32 = LoadLibrary("user32.dll");
        if(hUser32 == NULL){
            printf("Failed to load user32.dll\n");
            return 0;
        }
    
        pGetAsyncKeyState = (getAsyncKeyStatePtr)GetProcAddress(hUser32, "GetAsyncKeyState");
        if(pGetAsyncKeyState == NULL){
            printf("Failed to make pointer to getAsyncKeyState\n");
            return 0;
        }
    }

    if(pGetAsyncKeyState(KEY) & KEY_DOWN_MASK){ // & is the bitwise AND operand
        wasPressed = 1;
    }

    // only returns 1 for a press (doesnt return 1 if you hold it)
    if(!previousWasPressed && wasPressed){
        previousWasPressed = 1;
    } else if(previousWasPressed && wasPressed){
        wasPressed = 0;
    } else{
        previousWasPressed = 0;
    }

    return wasPressed;
}