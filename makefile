C_DIR = src/c/
ASM_DIR = src/asm/

# MAKE THE EXE FILE
OBJS = build/main.obj \
	build/mouseDown.obj \
	build/mouseUp.obj \
	build/parseOsuFile.obj \
	build/keyWasPressed.obj \
	build/moveMouse.obj \
	build/findPID.obj \
	build/isExecutablePage.obj \
	build/memCmpWildcard.obj \
	build/writeOneByte.obj \
	build/findPatternInProcess.obj \
	build/closeDebugEventHandles.obj \
	build/waitForInitialAttachBreakpoint.obj \
	build/captureBreakpointRCX.obj \
	build/getPlayingStateValue.obj \
	build/getPlayerPtr.obj


main.exe: $(OBJS)
	link $(OBJS)
	
# GET ASM OBJECT FILES
build/mouseDown.obj: $(ASM_DIR)mouseDown.asm | build/
	ML64 /c /Fobuild/ src/asm/mouseDown.asm

build/mouseUp.obj: $(ASM_DIR)mouseUp.asm | build/
	ML64 /c /Fobuild/ src/asm/mouseUp.asm

build/parseOsuFile.obj: $(ASM_DIR)parseOsuFile.asm | build/
	ML64 /c /Fobuild/ src/asm/parseOsuFile.asm
	
build/moveMouse.obj: $(ASM_DIR)moveMouse.asm | build/
	ML64 /c /Fobuild/ src/asm/moveMouse.asm

build/findPID.obj: $(ASM_DIR)findPID.asm | build/
	ML64 /c /Fobuild/ src/asm/findPID.asm

build/isExecutablePage.obj: $(ASM_DIR)isExecutablePage.asm | build/
	ML64 /c /Fobuild/ src/asm/isExecutablePage.asm

build/memCmpWildcard.obj: $(ASM_DIR)memCmpWildcard.asm | build/
	ML64 /c /Fobuild/ src/asm/memCmpWildcard.asm

build/writeOneByte.obj: $(ASM_DIR)writeOneByte.asm | build/
	ML64 /c /Fobuild/ src/asm/writeOneByte.asm

# GET C OBJECT FILES
build/main.obj: $(C_DIR)main.c | build/
	cl /c /Isrc/headers /Fobuild/ src/c/main.c

build/keyWasPressed.obj: $(C_DIR)keyWasPressed.c | build/
	cl /c /Fobuild/ $(C_DIR)keyWasPressed.c

build/findPatternInProcess.obj: $(C_DIR)findPatternInProcess.c | build/
	cl /c /Isrc/headers /Fobuild/ $(C_DIR)findPatternInProcess.c

build/closeDebugEventHandles.obj: $(C_DIR)closeDebugEventHandles.c | build/
	cl /c /Isrc/headers /Fobuild/ $(C_DIR)closeDebugEventHandles.c

build/waitForInitialAttachBreakpoint.obj: $(C_DIR)waitForInitialAttachBreakpoint.c | build/
	cl /c /Isrc/headers /Fobuild/ $(C_DIR)waitForInitialAttachBreakpoint.c

build/captureBreakpointRCX.obj: $(C_DIR)captureBreakpointRCX.c | build/
	cl /c /Isrc/headers /Fobuild/ $(C_DIR)captureBreakpointRCX.c

build/getPlayingStateValue.obj: $(C_DIR)getPlayingStateValue.c | build/
	cl /c /Isrc/headers /Fobuild/ $(C_DIR)getPlayingStateValue.c

build/getPlayerPtr.obj: $(C_DIR)getPlayerPtr.c | build/
	cl /c /Isrc/headers /Fobuild/ $(C_DIR)getPlayerPtr.c

# MAKE BUILD FOLDER IF IT DOESNT EXIST
build/:
	mkdir build

clean:
	del main.exe
	rmdir /s /q build