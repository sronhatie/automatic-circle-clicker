#include <stdio.h>
#include <string.h>

#include "asmFunctions.h"
#include "cFunctions.h"

int main(){
  FILE *osuFile;
  osuFile = fopen("Kry.exe - Rift Walker (Ryuusei Aika) [Easy].osu", "r");
  if(!osuFile){
    return 1;
  }


  return 0;
}