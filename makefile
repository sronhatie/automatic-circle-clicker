C_DIR = src/c/
ASM_DIR = src/asm/

# MAKE THE EXE FILE
OBJS = build/main.obj build/clickMouse.obj build/parseOsuFile.obj build/keyWasPressed.obj
main.exe: $(OBJS)
	link $(OBJS)
# GET ASM OBJECT FILES
build/clickMouse.obj: $(ASM_DIR)clickMouse.asm | build/
	ML64 /c /Fobuild/ src/asm/clickMouse.asm
build/parseOsuFile.obj: $(ASM_DIR)parseOsuFile.asm | build/
	ML64 /c /Fobuild/ src/asm/parseOsuFile.asm

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