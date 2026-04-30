C_DIR = src/c
ASM_DIR = src/asm
BUILD_DIR = build

C_FILES = $(wildcard $(C_DIR)/*.c) $(wildcard $(C_DIR)/memory/*.c)
ASM_FILES = $(wildcard $(ASM_DIR)/*.asm)

C_OBJ = $(patsubst $(C_DIR)/%.c,$(BUILD_DIR)/%.obj,$(C_FILES))
ASM_OBJS = $(patsubst $(ASM_DIR)/%.asm,$(BUILD_DIR)/%.obj,$(ASM_FILES))

OBJS = $(C_OBJ) $(ASM_OBJS)

# MAKE THE EXE FILE

main.exe: $(OBJS)
	link /OUT:main.exe $(OBJS)
	
# GET ASM OBJECT FILES

$(BUILD_DIR)/%.obj: $(ASM_DIR)/%.asm | $(BUILD_DIR)
	ML64 /c /Fo$@ $<

# GET C OBJECT FILES

$(BUILD_DIR)/%.obj: $(C_DIR)/%.c | $(BUILD_DIR) $(BUILD_DIR)/memory
	cl /c /Isrc/headers /Fo$@ $<

# MAKE BUILD FOLDER IF IT DOESNT EXIST

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/memory:
	mkdir $(BUILD_DIR)\memory

clean:
	del main.exe
	rmdir /s /q $(BUILD_DIR)