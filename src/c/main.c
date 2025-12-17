#include <stdio.h>
#include <string.h>

#include "asmFunctions.h"
#include "cFunctions.h"

int main(){

  HitObject *PtrHitObject;
  PtrHitObject = ParseOsuFile();
  
  ClickMouse();
  printf("aaaa\n");
  
  for (int i = 0; i < 150; i++) {
    printf(
      "%d: x=%d y=%d time=%d type=%d\n",
        i,
        PtrHitObject[i].x,
        PtrHitObject[i].y,
        PtrHitObject[i].objectTime,
        PtrHitObject[i].objectType
    );
  }


  return 0;
}