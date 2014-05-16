/*
 * author: Patrick Xu
 *
 * sunspots.c
 *
 * Description: will parse sunspot data given with the format specified 
 * in ./format.txt and allow user to learn about sunspots in a certain day.
 *
 * Input: folder containing the data
 *
 */

#include <stdio.h>
#include <sys/stat.h>

#include "sunspots.h"


int main(int argc, char *argv[]){

  if (argcheck(argc, argv) != TRUE){
    printf("Argument Error!\n");
    return FALSE;
  }

}

int argcheck(int argc, char *argv[]){

  if (argc != 2){
    return FALSE;
  } 

  struct stat mydir;
  if (stat(argv[1], &mydir) == 0){
    if(!S_ISDIR(mydir.st_mode)){ //file exists but isn't a directory
      return FALSE;
    }
  }
  else //file doesn't exist
    return FALSE;

  return TRUE;
}

void printspot(SPOT* spot){

  printf("%s\n", spot->year);

}
