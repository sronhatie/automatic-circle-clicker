### The Start 2025-11
MASM very different from TASM. more registers. RAX(64bits) EAX(32bits) and RSP ESP RDI EDI and other stuff  
Also db(define byte 8bits) dw(define word 16bits) dd(define
dword 32bits) dq(define qword 64bits) exist now.  
Stack grows downwards. So to allocate space u do SUB register, (size u want to allocate)
Arguments in ASM: RCX, RDX, R8, R9 in that order a b c d. the rest in stack, got to add it from rsp + 20h because shadow space exists  
Return value: RAX  
Callee must preserve not-volatile (callee-saved) registers: RBX, RBP, RDI, RSI, R12-R15  
Stack Alignment: the stack pointer must be 16-byte aligned at the point of a CALL  
LEA(Load Effective Address) is used to calculate and load the address of a memory operand into a register, without accessing the memory itself. LEA only computes the address, making it useful for address calculations and optimizing arithmetics.  
Caller allocates 32bytes of "shadow space" before calling.  
REL(relative addressing) basically tells the computerto use RIP-relative addressing like normal x64 code does usage ```lea rcx, [rel name]```
RIP-relative addressing is a memory addressing mode in the x86-64 architecture where the effective address is calculated by adding a signed 32-bit displacement to the address of the next instruction, which is stored in the RIP (Instruction Pointer) register.  
The primary advantage of RIP-relative addressing is that it enables the creation of position-independent code, which is a security feature that makes it more difficult for attackers to predict the memory layout of a program. This is particularly useful for modern software modules like DLLs or EXEs that contain both code and data  
In every normal Windows process some DLLs are always loaded like: kernel32.dll ntdll.dll kernelbase.dll ucrtbase.dll apisetschema.dll AND your exe!!!  
ML64 - for asm   
CL - for C  
add /c so u only get .obj files  
add /I<directory> if the header is at a different location (no space, very important)  
add /Fo<directory> to make obj files go to a certain directory (again no space)  
link - to link obj files  
use LoadLibraryA instead of LoadLibrary or LoadLibraryW because LoadLibrary is a Macro and A - ASCIIchar W - UTF16wchar  
HMODULE in C is a handle to a loaded DLL  
UINT unsigned int. windows uses unsigned ints in APIs  
WINAPI is a calling convention macro. use it when calling windows APIs or declaring them.  
LPINPUT = Long Pointer(LP) to INPUT. INPUT is a struct defined in windows.h that represents a single input event.  
FUNCTION POINTERS: int(*fptr)(int, int) initialize it by pointerName = &functionName  
UNION is a really cool thing, basically different data types can share the same memory location. although only one member can use up the spot, others just dont exist. useful for saving memory by reusinig the same memory space!!!  
DO typedef before it so u dont have to keep initializing it  
INPUT structure used by SendInput to store information for synthesizing input events such as keystrokes, mouse movement, and mouse clicks.  
in C its easy to load it all. just do HMODULE hName = LoadLibraryA("name.dll") then make a structure pointer. then strucPTR name = GetProcAddress(hName, procName)  
wildcard *.c in makefile gets every .smth thingy  
hold ctrl and u can press on any variable or header or whatever in VSC and itll show u where it is in the header file.  
__declspec(dllimport) to import dlls, there are more than dllimport functions, got to check the documentation.  
  
EXTERN name : PROC to tell it that its an executable proccess somehwere.  
EXTERN name : qword to tell that its data somewhere idonno  
Padding exists and theres no doc of it and u have to figure it out yourself where it is. Its called Field Alignments Inside a Struct.  
if C calls ur function the stack is already aligned if not you have to align it yourself by doing AND RSP, -16  
**x64dbg** use it. /Zi to generate a PDB file, helps with debugging (i wont use it cause yes).  
save ur RAX value if youll need it again for example SendInputPtr.  
because i called my ASM function from C, the compiler already allocates 32bytes and then also takes 8bytes for the return value. thats why my stack was misaligned by 8 at the start of my ASM program.  
ASM doesnt include padding for STRUCTs so u have to add padding urself :(  
u can either make the struct in .data or dynamically in stack. just give it the amount it needs by doing SUB RSP, sizeof STRUCT and then u can use it like this [RSP].STRUCT.name.otherThing Dont forget to restore the RSP by doing ADD  
always have a RET at the end please.  

### Parsing .osu files
malloc is portable. HeapAlloc is windows only.  
when you write a C program, the compiler drags in the C Runtime Library(CRT), basically includes a lot of stuff.  
for HeapAlloc you dont need the CRT so in MASM its better to use it. instead of malloc.  
if you allocate with malloc, you have to free with free. if you do HeapAlloc you have to use HeapFree  
CreateFileA - name is a lie, does a lot more than you think. opens a file, creates a file. basically its a file handle machine. returns a handle  
ReadFile - you give it the handle from CreateFileA and read it. simple.  
CloseHandle - closes everything that calls itself a handle.  
MASM has header files (.inc) where you can have structs, constants and even EXTERN declarations.  
to use it in MASM do INCLUDE MyStuff.inc
Pointers must be in .data, dword thingies can be in .inc  
Do not continue with a bad handle, always zero it out if its bad.  
Instead of chunk reading tiny files (DONT DO THIS FOR BIG FILES), its better to load it all into memory using GetFileSize, VirtualAlloc then read it using ReadFile. VirtualAlloc is simpler to use than HeapAlloc  
lpBuffer is what u allocated using VirtualAlloc, nNumberOfBytesToRead will be file size for this call. outputs lpNumberOfBytesRead, so u need to give it a dword pointer

