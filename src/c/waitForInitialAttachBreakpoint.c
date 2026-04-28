#include <windows.h>

#include "asmFunctions.h"

int waitForInitialAttachBreakpoint(){
    DEBUG_EVENT debugEvent;

    while(1){
        WaitForDebugEvent(&debugEvent, INFINITE);

        DWORD continueStatus = DBG_CONTINUE;
        int done = 0;

        if(debugEvent.dwDebugEventCode == EXCEPTION_DEBUG_EVENT){
            DWORD exceptionCode = debugEvent.u.Exception.ExceptionRecord.ExceptionCode;

            if(exceptionCode == EXCEPTION_BREAKPOINT){
                done = 1;
                continueStatus = DBG_CONTINUE;
            } else{
                continueStatus = DBG_EXCEPTION_NOT_HANDLED;
            }
        }

        closeDebugEventHandles(&debugEvent);
        ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, continueStatus);

        if(done){
            return 1;
        }
    }
}