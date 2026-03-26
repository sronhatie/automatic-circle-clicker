//#include <stdio.h>
//#include <string.h>
#include <windows.h>

#include "asmFunctions.h"
#include "cFunctions.h"

int main(){
  char *processName = "osu!.exe";

  HitObject *PtrHitObject;
  PtrHitObject = parseOsuFile();
  
  DWORD processID = findPID(processName);
  printf("%d", processID);

  moveMouse(50, 50);
  printf("aaaa\n");
  // mouseDown();
  // mouseUp();

  // while(1){
  //   if(keyWasPressed()){
  //     printf("Started clicking\n");
  //     int i = 0;
  //     int previousTime = 0;

  //     while(PtrHitObject[i].x != 0){
  //       if(keyWasPressed()){
  //         printf("Stopped clicking\n");
  //         break;
  //       }

  //       int delay = PtrHitObject[i].objectTime - previousTime;
  //       previousTime = PtrHitObject[i].objectTime;
  //       printf("%d : %d | ", delay, previousTime);


  //       mouseDown();
  //       mouseUp();
  //       printf("clicked\n");
  //       Sleep(delay);
  //       //moveMouse(PtrHitObject[i].x, PtrHitObject[i].y);
  //       i++;
  //     }
  //   }

  //   Sleep(100);
  // }

  return 0;
}



/* for(int i = 0; i < 150; ++i){
  printf(
    "%d: x=%d y=%d time=%d type=%d\n",
      i,
      PtrHitObject[i].x,
      PtrHitObject[i].y,
      PtrHitObject[i].objectTime,
      PtrHitObject[i].objectType
  );
} */