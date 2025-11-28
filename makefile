C_DIR = src/c/
ASM_DIR = src/asm/

# MAKE THE EXE FILE
OBJS = build/main.obj build/RightClickMouse.obj build/ClickMouse.obj
main.exe: $(OBJS)
	link $(OBJS)
# GET ASM OBJECT FILES
build/ClickMouse.obj: $(ASM_DIR)ClickMouse.asm | build/
	ML64 /c /Fobuild/ src/asm/ClickMouse.asm
# GET C OBJECT FILES
build/main.obj: $(C_DIR)main.c | build/
	cl /c /Isrc/headers /Fobuild/ src/c/main.c

build/RightClickMouse.obj: $(C_DIR)RightClickMouse.c | build/
	cl /c /Fobuild/ $(C_DIR)RightClickMouse.c

# MAKE BUILD FOLDER IF IT DOESNT EXIST
build/:
	mkdir build