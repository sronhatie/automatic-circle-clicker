
# MAKE THE EXE FILE
main.exe: build/main.obj build/ClickMouse.obj
	link build/main.obj build/ClickMouse.obj
# GET ASM OBJECT FILES
build/ClickMouse.obj: src/asm/ClickMouse.asm | build/
	ML64 /c /Fobuild\ src/asm/ClickMouse.asm
# GET C OBJECT FILES
build/main.obj: src/c/main.c | build/
	cl /c /Isrc/headers /Fobuild/ src/c/main.c
# MAKE BUILD FOLDER IF IT DOESNT EXIST
build/:
	mkdir build