//#include <stdio.h>
//#include <string.h>
#include <windows.h>

#include "asmFunctions.h"
#include "cFunctions.h"

int main(){

  HitObject *PtrHitObject;
  PtrHitObject = parseOsuFile();
  
  //mouseDown();
  moveMouse(50, 50);
  printf("aaaa\n");
/*
  while(1){
    if(keyWasPressed()){
      int i = 0;
      while(PtrHitObject[i].x != 0){

        ++i;
      }
    }
    Sleep(100);
  }
*/
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