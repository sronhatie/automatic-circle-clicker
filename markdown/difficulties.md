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

