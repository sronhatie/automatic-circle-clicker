#include <windows.h>

#include "asmFunctions.h"

uintptr_t captureBreakpointRCX(HANDLE hProcess, uintptr_t bpAddr, BYTE originalByte){
    DEBUG_EVENT debugEvent;
    uintptr_t capturedRCX = 0;

    while (1){
        WaitForDebugEvent(&debugEvent, INFINITE);

        DWORD continueStatus = DBG_CONTINUE;
        int done = 0;

        if(debugEvent.dwDebugEventCode == EXCEPTION_DEBUG_EVENT){
            DWORD code = debugEvent.u.Exception.ExceptionRecord.ExceptionCode;
            uintptr_t exceptionAddress = (uintptr_t)debugEvent.u.Exception.ExceptionRecord.ExceptionAddress;

            if(code == EXCEPTION_BREAKPOINT){
                HANDLE hThread = OpenThread(
                    THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_QUERY_INFORMATION,
                    FALSE,
                    debugEvent.dwThreadId
                );

                CONTEXT ctx;
                ZeroMemory(&ctx, sizeof(ctx));
                ctx.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;

                GetThreadContext(hThread, &ctx);

                uintptr_t rip = (uintptr_t)ctx.Rip;
                uintptr_t int3Addr;
                if(rip > 0){
                    int3Addr = rip - 1;
                } else{
                    int3Addr = 0;
                }

                if(exceptionAddress == bpAddr || int3Addr == bpAddr){
                    capturedRCX = (uintptr_t)ctx.Rcx;
                    writeOneByte(hProcess, bpAddr, originalByte);

                    ctx.Rip = bpAddr;
                    SetThreadContext(hThread, &ctx);

                    done = 1;
                    continueStatus = DBG_CONTINUE;
                } else{
                    continueStatus = DBG_CONTINUE;
                }

                CloseHandle(hThread);
            } else{
                continueStatus = DBG_EXCEPTION_NOT_HANDLED;
            }
        }

        closeDebugEventHandles(&debugEvent);
        ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, continueStatus);

        if(done){
            return capturedRCX;
        }
    }
}