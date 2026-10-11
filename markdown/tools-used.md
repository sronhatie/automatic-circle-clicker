# Tools used for the project

[dnSpy](https://github.com/dnspy/dnspy) - helped me figure out the path to whatever value i needed (found OsuGameDesktop using it). later replaced it with WinDbg
[WinDbg](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/) - made my life a lot easier with object dumps. finding the offsets became super easy.
[Process Monitor](https://learn.microsoft.com/en-us/sysinternals/downloads/procmon) - dont really remember, but i think i used it when i was looking into why osu was crashing after a debugger detaches
[Windows Performance Analyzer](https://learn.microsoft.com/en-us/windows-hardware/test/wpt/windows-performance-analyzer) - used it to look into why osu was crashing after a debugger detaches. figured out the exact moment it crashes and it was a manual exit done by AuthNative.dll because it detects when osu code is modified.
[x64dbg](https://github.com/x64dbg/x64dbg) - bread and butter of figuring out why my program would silently crash (mostly used it for assembly code)
[Ghidra](https://github.com/nationalsecurityagency/ghidra) - i tried to reverse engineer AuthNative.dll and figure out the actual code that makes osu go byebye. sadly havent done it. but would be cool to figure out cause then id know how often it checks for the modified code.
