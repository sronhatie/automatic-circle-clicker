#include <windows.h>

#include "asmFunctions.h"
#include "debugging.h"
#include "signatures.h"

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

uintptr_t findPatternInProcess(HANDLE hProcess, unsigned char *signature, char *mask){
    MEMORY_BASIC_INFORMATION mbi;
    uintptr_t address = 0;
    size_t signatureLength = strlen(mask);

    const SIZE_T chunkSize = 1024 * 1024;
    unsigned char *buffer = malloc(chunkSize);

    while((VirtualQueryEx(hProcess, (LPCVOID)address, &mbi, sizeof(mbi))) == sizeof(mbi)){
        if(mbi.State == MEM_COMMIT && isExecutablePage(mbi.Protect)){
            uintptr_t regionBase = (uintptr_t)mbi.BaseAddress;
            SIZE_T regionSize = mbi.RegionSize;
            SIZE_T regionOffset = 0;

            while(regionOffset < regionSize){
                SIZE_T toRead = chunkSize;
                if(regionOffset + toRead > regionSize){
                    toRead = regionSize - regionOffset;
                }

                SIZE_T bytesRead = 0;
                ReadProcessMemory(hProcess, (LPCVOID)(regionBase + regionOffset), buffer, toRead, &bytesRead);

                if(bytesRead >= signatureLength){
                    for(SIZE_T i = 0; i <= bytesRead - signatureLength; ++i){
                        if(memCmpWildcard(buffer + i, signature, mask)){
                            free(buffer);
                            return regionBase + regionOffset + i;
                        }
                    }
                }

                if(toRead <= signatureLength){
                    break;
                }

                regionOffset += toRead - (signatureLength - 1);
            }
        }

        address = (uintptr_t)mbi.BaseAddress + mbi.RegionSize;
    }

    free(buffer);
    return 0;
}

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

uintptr_t getOsuGamePtr(HANDLE hProcess, DWORD processID){
    uintptr_t updateAfterChildrenAddr = findPatternInProcess(hProcess, updateAfterChildrenSignature, updateAfterChildrenMask);

    BYTE originalByte = 0;
    ReadProcessMemory(hProcess, (LPCVOID)updateAfterChildrenAddr, &originalByte, 1, NULL);

    DebugActiveProcess(processID);
    DebugSetProcessKillOnExit(FALSE);

    waitForInitialAttachBreakpoint();
    writeOneByte(hProcess, updateAfterChildrenAddr, 0xCC);

    uintptr_t osuGamePtr = captureBreakpointRCX(hProcess, updateAfterChildrenAddr, originalByte);
    DebugActiveProcessStop(processID);

    return osuGamePtr;
}