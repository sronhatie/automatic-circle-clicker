### The Start 2025-11
MASM very different from TASM. more registers. RAX(64bits) EAX(32bits) and RSP ESP RDI EDI and other stuff  
Also db(define byte 8bits) dw(define word 16bits) dd(define dword 32bits) dq(define qword 64bits) exist now.  
Stack grows downwards. So to allocate space u do SUB register, (size u want to allocate)
Arguments in ASM: RCX, RDX, R8, R9 in that order a b c d  
Return value: RAX  
Callee must preserve not-volatile (callee-saved) registers: RBX, RBP, RDI, RSI, R12-R15  
Stack Alignment: the stack pointer must be 16-byte aligned at the point of a CALL  
LEA(Load Effective Address) is used to calculate and load the address of a memory operand into a register, without accessing the memory itself. LEA only computes the address, making it useful for address calculations and optimizing arithmetics.  
Caller allocates 32bytes of "shadow space" before calling.  
REL(relative addressing) basically tells the computerto use RIP-relative addressing like normal x64 code does usage ```lea rcx, [rel name]```
RIP-relative addressing is a memory addressing mode in the x86-64 architecture where the effective address is calculated by adding a signed 32-bit displacement to the address of the next instruction, which is stored in the RIP (Instruction Pointer) register.  
The primary advantage of RIP-relative addressing is that it enables the creation of position-independent code, which is a security feature that makes it more difficult for attackers to predict the memory layout of a program. This is particularly useful for modern software modules like DLLs or EXEs that contain both code and data  
In every normal Windows process some DLLs are always loaded like: kernel32.dll ntdll.dll kernelbase.dll ucrtbase.dll apisetschema.dll AND your exe!!!  

