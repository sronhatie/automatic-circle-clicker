ASM_DIR = src/asm
C_DIR = src/c
HEADERS_DIR = src/headers
BUILD_DIR = build

ASM_FILES = $(ASM_DIR)/ClickMouse.asm
C_FILES = $(C_DIR)/main.c
HEADERS = $(HEADERS_DIR)/asmFunctions.h
# ====================================================================

ASM_COMPILER = ml64
C_COMPILER = cl
LINKER = link

ASM_OBJS = $(ASM_FILES:$(ASM_DIR)/%.asm=$(BUILD_DIR)/%.obj)
C_OBJS   = $(C_FILES:$(C_DIR)/%.c=$(BUILD_DIR)/%.obj)

# Executable
TARGET = main.exe

# Build rules
all: $(TARGET)

# Link rule
$(TARGET): $(ASM_OBJS) $(C_OBJS)
	$(LINKER) $(C_OBJS) $(ASM_OBJS) /OUT:$(TARGET)

# Compile C files
$(BUILD_DIR)/%.obj: $(C_DIR)/%.c $(HEADERS)
	$(C_COMPILER) /c /I$(HEADERS_DIR) /Fo$@ $<

# Compile ASM files
$(BUILD_DIR)/%.obj: $(ASM_DIR)/%.asm
	$(ASM_COMPILER) /c /Fo$@ $<

# Run the .exe file
run: ${TARGET}
	${TARGET}

# Clean
clean:
	del /Q $(ASM_OBJS) $(C_OBJS) $(TARGET)