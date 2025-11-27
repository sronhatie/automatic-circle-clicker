
# MAKE THE EXE FILE
main.exe: main.obj ClickMouse.obj
	link build/main.obj build/ClickMouse.obj
# GET ASM OBJECT FILES
ClickMouse.obj: ./src/asm/ClickMouse.asm
	ML64 /c /Fobuild\ src\asm\ClickMouse.asm
# GET C OBJECT FILES
main.obj: ./src/c/main.c
	cl /c /Isrc/headers /Fobuild/ src/c/main.c
