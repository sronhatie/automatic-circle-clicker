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
