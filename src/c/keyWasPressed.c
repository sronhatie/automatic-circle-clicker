/*
Problems: 
 - 
*/

#include <windows.h>

#define KEY 'Q'

typedef SHORT (WINAPI *getAsyncKeyStatePtr)(int);

int keyWasPressed(){
    int wasPressed = 0;
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
        
    if(pGetAsyncKeyState(KEY) & 0x8000){ // & is the bitwise AND operand
        printf("Key was pressed\n");
        wasPressed = 1;
    }

    return wasPressed;
}