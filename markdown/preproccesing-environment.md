idonno i started learing this now so im stuck i guess.  
```
Ldr* - PE loader
Ldrp* - loader private internals. undocumented, unstable, constantly changing
Rtl* - runtime library (strings, memory, lists, heaps)
Nt* / Zw* - syscalls
Ki* - kernel internals (you usually won’t see these)
```
execution starts at kernel then it reaches ntdll!LdrInitializeThunk not entry point.  
a thread is an execution stream with its own registers, its own stack, its own TEB(Thread Environment Block) but shared address space with the process.  

```
ntdll!LdrInitializeThunk - this is the start of user-mode execution. it runs on each new thread.
ntdll!LdrpInitializeProcess - loader brain
ntdll!LdrLoadDll - maps DLLs into memory also called whenever any DLL is requested
ntdll!LdrpCallInitRoutine - calls DllMain and TLS callbacks
```
API-MS-WIN DLLs are names, not files.  
memory map is a live view of the process' virtual address space. shows what dlls are really loaded.  
TYPES:  
IMG - memory mapped PE image (EXE or DLL)  
MPA - file mapping (NLS, locale data, etc.)  
PRV - private memory (heap, stack, allocations)  
Manual mapping shows up as PRV, executable, no file path, large region  

