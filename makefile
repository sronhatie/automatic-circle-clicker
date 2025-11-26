
ASM_FILES = ClickMouse.asm
C_FILES = main.c
HEADERS = asmFunctions.h
# ====================================================================

ASM_COMPILER = ml64
C_COMPILER = cl
LINKER = link

ASM_OBJS = $(ASM_FILES:.asm=.obj)
C_OBJS   = $(C_FILES:.c=.obj)

# Executable
TARGET = main.exe

# Build rules
all: $(TARGET)

# Link rule
$(TARGET): $(ASM_OBJS) $(C_OBJS)
	$(LINKER) $(C_OBJS) $(ASM_OBJS) /OUT:$(TARGET)

# Compile C files
%.obj: %.c $(HEADERS)
	$(C_COMPILER) /c /Fo$@ $<

# Compile ASM files
%.obj: %.asm
	$(ASM_COMPILER) /c /Fo$@ $<

# Run the .exe file
run: ${TARGET}
	${TARGET}

# Clean
clean:
	del /Q $(ASM_OBJS) $(C_OBJS) $(TARGET)