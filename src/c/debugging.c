#include <windows.h>

#include "asmFunctions.h"
#include "debugging.h"
#include "signatures.h"

uintptr_t captureBreakpointRCX(HANDLE hProcess, uintptr_t bpAddr, BYTE originalByte){
    DEBUG_EVENT debugEvent;
    uintptr_t capturedRCX = 0;

    while (1){
        WaitForDebugEvent(&debugEvent, INFINITE);
// TODO: check if it fails

        DWORD continueStatus = DBG_CONTINUE;
        int done = 0;

        if(debugEvent.dwDebugEventCode == EXCEPTION_DEBUG_EVENT){
            DWORD exceptionCode = debugEvent.u.Exception.ExceptionRecord.ExceptionCode;
            uintptr_t exceptionAddress = (uintptr_t)debugEvent.u.Exception.ExceptionRecord.ExceptionAddress;

            if(exceptionCode == EXCEPTION_BREAKPOINT){
                // since registers belong to a thread, we open the thread that hit the breakpoint
                HANDLE hThread = OpenThread(
                    THREAD_GET_CONTEXT | THREAD_SET_CONTEXT | THREAD_QUERY_INFORMATION,
                    FALSE,
                    debugEvent.dwThreadId
                );
// TODO: check if it fails

                CONTEXT ctx; // huge struct containing processor-specific register data.
                ZeroMemory(&ctx, sizeof(ctx));
                ctx.ContextFlags = CONTEXT_INTEGER | CONTEXT_CONTROL;

                // fills ctx with the frozen threads current registers
                GetThreadContext(hThread, &ctx);
// TODO: check if it fails

                uintptr_t rip = (uintptr_t)ctx.Rip;
                uintptr_t int3Addr;
                // if rip was 0 then -1 would wrap around.
                if(rip > 0){
                    // once the cpu executes 0xCC it triggers an exception but RIP points after the breakpoint byte
                    // so we do - 1 to get the actual address of 0xCC(int3)
                    int3Addr = rip - 1;
                } else{
                    int3Addr = 0;
                }

                if(exceptionAddress == bpAddr || int3Addr == bpAddr){
                    capturedRCX = (uintptr_t)ctx.Rcx;
                    // restores the original byte (previously was 0xCC)
                    writeOneByte(hProcess, bpAddr, originalByte);
// TODO: check if it fails

                    ctx.Rip = bpAddr;
                    SetThreadContext(hThread, &ctx);
// TODO: check if it fails

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
// TODO: check if it fails

        if(done){
            return capturedRCX;
        }
    }
}

// TODO: change to int to return if it fails or succeeds 
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
// TODO: check for bad inputs
    MEMORY_BASIC_INFORMATION mbi;
    uintptr_t address = 0;
    size_t signatureLength = strlen(mask);

    // scans the memory in 1MB chunks
    const SIZE_T chunkSize = 1024 * 1024;
    unsigned char *buffer = malloc(chunkSize);
// TODO: check if it fails

    // checks what memory region exists and fills mbi
    // the loop ends once it reaches the end (sizeof(mbi))
    while((VirtualQueryEx(hProcess, (LPCVOID)address, &mbi, sizeof(mbi))) == sizeof(mbi)){
        // only scans memory that is usable and is executable
        if(mbi.State == MEM_COMMIT && isExecutablePage(mbi.Protect)){
            uintptr_t regionBase = (uintptr_t)mbi.BaseAddress;
            SIZE_T regionSize = mbi.RegionSize;
            SIZE_T regionOffset = 0;

            while(regionOffset < regionSize){
                SIZE_T toRead = chunkSize;
                // if theres less than 1MB left it only reads the remaining amount
                if(regionOffset + toRead > regionSize){
                    toRead = regionSize - regionOffset;
                }

                SIZE_T bytesRead = 0;
                ReadProcessMemory(hProcess, (LPCVOID)(regionBase + regionOffset), buffer, toRead, &bytesRead);
// TODO: skip chunk if fails

                // if our signatureLength was 5 and we read 4 bytes thats bad.
                if(bytesRead >= signatureLength){
                    // defines all starting positions. so for the example above it would be 
                    // 0 and 1. 2 and above is bad as it would overflow to 6
                    for(SIZE_T i = 0; i <= bytesRead - signatureLength; ++i){
                        if(memCmpWildcard(buffer + i, signature, mask)){
                            free(buffer);
                            return regionBase + regionOffset + i;
                        }
                    }
                }

                // if toRead is too small, the movement is too small to be useful (or could become negative)
                if(toRead <= signatureLength){
                    break;
                }

                // since regions can split the signature, we overlap the signatures by (signatureLength - 1)
                regionOffset += toRead - (signatureLength - 1);
            }
        }

        // goes to the next region (for VirtualQueryEx())
        address = (uintptr_t)mbi.BaseAddress + mbi.RegionSize;
    }

    free(buffer);
    return 0;
}

int waitForInitialAttachBreakpoint(){ // i should change the name of this.
   // this function is used to remove the breakpoint that windows sends to debuggers

    DEBUG_EVENT debugEvent;

    while(1){
        WaitForDebugEvent(&debugEvent, INFINITE);
// TODO: check if it fails

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
        // resumes the process
        ContinueDebugEvent(debugEvent.dwProcessId, debugEvent.dwThreadId, continueStatus); 
// TODO: check if it fails

        if(done){
            return 1;
        }
    }
}
