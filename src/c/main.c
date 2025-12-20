//#include <stdio.h>
//#include <string.h>
#include <windows.h>

#include "asmFunctions.h"
#include "cFunctions.h"

#define KEY 'Q'

int main(){

  //HitObject *PtrHitObject;
  //PtrHitObject = ParseOsuFile();
  
  //ClickMouse();
  printf("aaaa\n");
  while(1){
    printf("%d ", keyWasPressed());
    Sleep(100);
  }

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