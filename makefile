C_DIR = src/c/
ASM_DIR = src/asm/

# MAKE THE EXE FILE
OBJS = build/main.obj build/mouseDown.obj build/parseOsuFile.obj build/keyWasPressed.obj build/moveMouse.obj
main.exe: $(OBJS)
	link $(OBJS)
# GET ASM OBJECT FILES
build/mouseDown.obj: $(ASM_DIR)mouseDown.asm | build/
	ML64 /c /Fobuild/ src/asm/mouseDown.asm
build/parseOsuFile.obj: $(ASM_DIR)parseOsuFile.asm | build/
	ML64 /c /Fobuild/ src/asm/parseOsuFile.asm
build/moveMouse.obj: $(ASM_DIR)moveMouse.asm | build/
	ML64 /c /Fobuild/ src/asm/moveMouse.asm

# GET C OBJECT FILES
build/main.obj: $(C_DIR)main.c | build/
	cl /c /Isrc/headers /Fobuild/ src/c/main.c

build/keyWasPressed.obj: $(C_DIR)keyWasPressed.c | build/
	cl /c /Fobuild/ $(C_DIR)keyWasPressed.c

# MAKE BUILD FOLDER IF IT DOESNT EXIST
build/:
	mkdir build

clean:
	del main.exe
	rmdir /s /q build