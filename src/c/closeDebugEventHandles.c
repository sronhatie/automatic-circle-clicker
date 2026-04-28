#include <windows.h>

#include "asmFunctions.h"

void closeDebugEventHandles(DEBUG_EVENT *debugEvent){
    if(debugEvent->dwDebugEventCode == CREATE_PROCESS_DEBUG_EVENT){
        if(debugEvent->u.CreateProcessInfo.hFile){
            CloseHandle(debugEvent->u.CreateProcessInfo.hFile);
        }
    } else if(debugEvent->dwDebugEventCode == LOAD_DLL_DEBUG_EVENT){
        if(debugEvent->u.LoadDll.hFile){
            CloseHandle(debugEvent->u.LoadDll.hFile);
        }
    }
}