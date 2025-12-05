#include <stdio.h>
#include <string.h>

#include "asmFunctions.h"
#include "cFunctions.h"

int main(){

  HitObject *PtrHitObject;
  PtrHitObject = ParseOsuFile();
  
  ClickMouse();
  printf("aaaa");



  return 0;
}