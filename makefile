BUILD_DIR = build

FIND = C:/msys64/usr/bin/find.exe

C_FILES = $(shell $(FIND) src -type f -name "*.c")
ASM_FILES = $(shell $(FIND) src -type f -name "*.asm")
H_FILES = $(shell $(FIND) src -type f -name "*.h")
INC_FILES = $(shell $(FIND) src -type f -name "*.inc")

C_OBJS = $(patsubst src/%.c,$(BUILD_DIR)/%.obj,$(C_FILES))
ASM_OBJS = $(patsubst src/%.asm,$(BUILD_DIR)/%.obj,$(ASM_FILES))

OBJS = $(C_OBJS) $(ASM_OBJS)

INCLUDE_DIRS = $(sort $(dir $(H_FILES) $(INC_FILES)))
INCLUDES = $(addprefix /I,$(INCLUDE_DIRS))

# MAKE THE EXE FILE

main.exe: $(OBJS)
	link /OUT:main.exe $(OBJS)
	
# GET ASM OBJECT FILES

$(BUILD_DIR)/%.obj: src/%.asm
	@mkdir -p "$(dir $(BUILD_DIR)/%.obj)"
	ML64 /c $(INCLUDES) /Fo$(BUILD_DIR)/%.obj src/%.asm

# GET C OBJECT FILES

$(BUILD_DIR)/%.obj: src/%.c
	@mkdir -p "$(dir $(BUILD_DIR)/%.obj)"
	cl /c $(INCLUDES) /Fo$(BUILD_DIR)/%.obj src/%.c

clean:
	rm -f main.exe
	rm -rf $(BUILD_DIR)
