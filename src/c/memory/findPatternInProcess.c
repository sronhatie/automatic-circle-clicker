#include <windows.h>

#include "asmFunctions.h"

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