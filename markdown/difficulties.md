### The Start 2025-11
JUST SETTING IT ALL UP IS A HASSTLE.  
Had to get ML64 then add it to my Environment Variables.  
THEN It still did not work because CL makes it to 32x and ML64 makes it to 64x.  
Sure I could've just compiled everything to 32x, but that's too easy. OH I just had to run the x64 native tools version.  
But then it would take too much time to compile everything, SO MAKEFILE it is!  
makefile took some time :(  
oh my who knew that int 21h is not a thing in modern ASM. so i need to use windows APIs like SendInput. im doomed. everything i knew is wrong.  
like there are rax(64bit) eax(32bit) R8-R15  
Okay so i could just call windows API like a normal human by doing include in asm BUT wheres the fun in that. i decided to torture myself so ill dynamically locate the functions!!!!  
basically i have to load the dll(dynamic link library), get the address of SendInput API and call the function pointer. pain all i see is pain and suffering.  
Just finished adding my first learnt.md entry and gosh. brain fried like an egg.  
WHY IS CALLING AN API SO DIFFICULT it just feels like magic numbers are everywhere.  
MAKEFILE is so annoying.  
OKAY so i realized that im too dependent on AI and that from this point onwards im not going to use any AI code whatsoever. Like i want to learn as much as I can and with AI in the way i feel like id just be doing what it does and not what i think of doing if that makes sense. no hand holding from ai!!!  
So because of that im reverting everything and starting from the beginning!!!  
makefile is still annoying. anyhow ill try dynamically calling the API using C first to understand how it works, ill also make the whole clicking thingy and then just try to make it in asm  
AAAA I JUST MADE THE THINGY TO CLICK RIGHT CLICK ON LAUNCH IN C wowe. WHILE also dynamically linking it. so its not just calling the SendInput its actually using mySendInput oh wowe. proud of myself for that.  
SOOOO remade the whole thing but with right click from sratch so i think i got this down now. anyhow. MY BRAIN FROM MAKEFILE is dying. i hate makefile. time is flying by too fast. its already 4pm.  
idonno i decided to try and make it without #include <windows.h> how will that go i dont know  
OH MY GOSH U CAN CHECK EVERYTHING JUST BY HOLDING CTRL AND GOING TO THE thingie. this will be so much easier now.  
gosh making ur own windows.h is just that easy, didnt think that it was so easy to dynamically load modules. all u need is documentation.  
  
ill now try to write it all in asm by staring at my C code.  
okay this is harder than it looks. since shadows space, stack 16 byte alignment AND function padding. gosh. i understand how the function padding works but i have no idea how to explain it.  
this website is great though it doesnt talk about the last point https://retroscience.net/x64-assembly.html  
dam only now do i get VS instead of VScode pain and suffering. i need it cause my code isnt working and not sure why so straight to registers i go!!!  
ILL GO INSANE. nothings working, tried VS didnt work, i donno how it works. tried debuging in VS doesnt work. my code doesnt work. this is very frustrating since i cant even debug it, i need to find something that im able to see the inside of the code and how it works :((  
woooo x64dbg exists where reverse engineers use it cool. it works. now i know why my program doesnt work. wrong alignment or something i donno i dont know anything i lied.  
AAAAAAAAAAAAA MY MIND IS BROKEN. WHY WHY WHY WHY. pushing one nonvolatile fixes the alignment, pushing 2 nonvolatiles break the alignment???? this hurts. im not sure why its even misaligned to begind with :(  
WOOOO I UNDERSTAND IT NOW. its cause i called my function in C and then the compiler just adds shadow space and then takes away 8 bytes for the return value, thats why THATS WHY it was misaligned by 8bytes at the start sobsobsob.  
AAAAAAAAAAAAAAAAA WHY DOES MY VOID FUNCTION HAVE TO HAVE A RET. IVE BEEN HAVING PROBLEMS BECAUSE I DIDNT HAVE A RET AT THE END THIS IS PAIN. IVE BEEN DEBUGGING FOR HOURS AND HOURS AND ITS ALL BECAUSE I DIDNT HAVE A RET...  

### Parsing .osu file
idonno ill currently just download and find the .osu map manually, i might make this automatic someday.  
gosh making .inc files work is a pain i just made it have it in the same directory as .asm file otherwise it doesnt work:(  
oh my ive gotten so much done and havent ranted in here what an acomplishment. im currently at the part where i read the file. truly getting the hang of winapi calling and ABI yay  
was stuck on CALLING MY OWN FUNCTION. gosh i tried to do MASM naming PROC but yes too much work so i just do the normal way of moving to registers RCX, RDX, R8, R9  
Current parser is very slow and whatnot since it compares it byte by byte but ill improve it in the future. what matters is that it work ;-;  
doing maths with pointers is painful gosh getting the current left read bytes took ages. thank god for programmer calc in windows  
ive decided to move over to no caps. got lazy holding the SHIFT key all the time so yes.  
dam im in a rabbit hole of learning stuff. got PE-bear got ghidra, im currently trying to understand how PE(preinstallation environment) works and all that. 
im going to die trying to make this parser work, i swear to god why is it so difficult to just ADD A NUMBER TO A STRUCTURE COME ON.  
im confused. I MADE THE PARSER WORK SOMEHOW. BUT NOW MY CLICKMOUSE.ASM IS NOT WORKING??? it just crashes on loadlibraryA what is this i didnt even change anything in it sobbing.  
sigh sigh sigh so the clickmouse.asm is working. but for some reason my printf isnt. the stack is aligned so not sure whats going on this is painful.  
AHABHSABAHA I DID IT I DID IT. it was painful and the code is spaghetti and its not good and not clean and not aaaaaa. it works. thats all that matters. IT WORKS. IT ACTUALLY WORKS. I PARSED AN .OSU FILE IN MASM AND PUT IT IN A STRUCT ARRAY THATS INSaNE.  
the bugs were so dum and argh! like ah yes i didnt allocate memory to my struct. like WHERE ARE U WRITING THE DATA u buffoon. everything works. im happy.  
omg i understand the difference between statically linking and dynamically linking libraries. its a good thing i did both in my asm program. like i can see the difference between it using PE-bear and x64dbg ITS INSANE. i love this. cant wait to get to manually mapping and stuff. gosh so programs lie to us its insane.  

### Making a start/stop feature
no idea where to even start. but yes fun  
oh i think im halfway there... made keyWasPressed.c runtime dynamically load so i wouldnt have to type something in makefile to make user32 work. too lazy for that.  
so yes, a lot quicker to just runtime load it than messing with my makefile.  
now all that's left is to make a toggle. since it can return 0 or 1. it return 1 if its pressed. althought it would always return 1111111 if u just hold it, but yes thats a problem for the future i guess.  
its kind of cool not seeing functions you use from WinAPI not appearing on pe-bear. like it doesnt even know that im logging keys with GetAsyncKeyState or that im pressing stuff using SendInput  
well well well i love "static". anyhow just finished making keyWasPressed function. it actually works. doesnt look pretty but WORKS. next step starting the program. since i have everything. like timing, location, and a way to start it yay.  
NOOOOOO LMAO I FORGOT THAT MY MOUSE HAS TO MOVVEEE i only maed it be able to click. sigh sigh. time to add a way to move the mouse in MASM cause yes!!!!!,,,,,  
yay i finished doing the move mouse thingy!!!! getting closer to the end.  

### Timing
been like a month since ive last done anything, so quickly added a mouseUp() and now timing will be a pain i can already see it.  
dam i derailed. ill probably try getting the time when the map loads so its synced. like prefectly synced, no more pressing q + this should help out in the future getting its mapname and yes  
CreateToolhelp32Snapshot - takes a snapshot of the specified processes.
LoadState has to be 5
ReadProcessMemory - reads the value of resolved address.
jeebus cristus i went on a detour using cheatengine is tough. but i managed to find something. opcodes i guess. i have no ieda. my brain is fried. 
aaaaaaaaa to find the value of LoadState i need to find the base pointer and then do + 10h since thats prolly where the struct holds LoadState. my gosh. this is painful.
it seems i was looking for a ghost... anyhow looked through osus github code thingy and it seems that gamestate is LocalUserPlayingState and that its an enum of 0 1 2 (NotPlaying, Break, Playing)  
ILSpy for reading  
dnSpyEx for interacting (attaching processes)  
im going to go insane. ive been doing this for like 10hours+ now and i still have no idea how to make it work. aiya aiya  
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA okay. i think ill try finding a method and then using RCX (WINDOWS ABI STUFF WOOOOO) to figure out "this" of OsuGameDesktop and after that its just offsets ;-;-;-;-;-;  
OH MY GOD. I ACTUALLY GOT A WAY TO ALWAYS GET THE TOP OF THE THINGY BASICALLY JUST hook into UpdateAfterChildren() (to do that u have to find the signature bytes that mostly dont change even after restarting. ofc u can also have wildcards. the longer the signature the better chance to find the exact byte sequence) in OsuGame and take RCX value. SINCE THAT IS THE POINTER TO OSUGAME CAUSE WINDOWS ABI YEGIAEYBAIBALK aiya aiya so proud of myself. finally some progress after like 20hours+   
next step will be to act as a debugger and get the RCX value. after that just add the offsets (THE EASIEST AND BEST PART OF ALL OF THIS AYUAHAOIHAO)  
FINALLY its all done. i now have gamestate.value BUT LIKE i realized that i dont even need it... i thought and thought and thunk and i realized that osu has a relax mod... soooooo the better option is to just find that function(which i have) and get the value that tells it when its on top of a hitcircle. to be honest even if relax mod wasnt a thing there would still be a way to find where it checks if ur cursor is on top of a hit circle. hence why ill just use this method and not invent something new. I believe that this method is way easier than calculating stuff. ARGh and like all of my previous stuff dont even matter.  I dont even need to parse the .osu file. i dont need to find the beatmap. i dont need anything. like it would just check, if its on top of the hitcircle it presses. as simpel as that... sigh sigh its sad but like i dont see a reason to do any of the difficult thingies when i have access to view its memory... gosh this method is insane. 
WILD i can now actually navigate objects and see who owns what. like go from value to the parent object just aaaa such a cool skill to have. this skill will make finding the Value i need way faster, i dont feel like im looking aimlessly.
sigh sigh just finally managed to get CurrentTime. one thingy done ;-;-;-;-;-;-; 5more to go (this is taking way too long) but i think itll be easier now cause WINDBG is a beast. shouldve used it before, wouldve made my life a lot easier.