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

#define _SVID_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#include "common.h"
#include "sunspots.h"


int main(int argc, char *argv[]){

  //check that arguments are valid
  if (argCheck(argc, argv) != TRUE){
    printf("Argument Error!\n");
    return FALSE;
  }

  //get data folder files into array
  struct dirent **files;
  int num;
  if ((num = getFiles(argv[1], &files, NULL, alphasort)) == -1){
    printf("Error when reading data files\n");
    return FALSE;
  }

  //main loop that allows the user to use the program
  while (1){

    //print menu and process user choice
    printf("\n\tMenu\n----------------------\n");
    printf("[1] Search for sunspots on a particular day\n");
    printf("[2] Learn about the solar sunspot cycle\n");
    printf("\n");
    printf("[x] Exit\n");
    printf("----------------------\n");
    printf("Enter your choice here: ");
    char choice = getc(stdin);

    if (choice == '1'){ //search for sunspots from a particular date
      printf("\n");
      searchForSpots(files, num, argv[1]);
    }
    if (choice == '2'){ //information about the sunspot cycle 
      printf("\n");
    }
    else if (choice == 'x'){ //exit
	printf("\nExiting!\n\n");
	break;
    }

    printf("\nPress [enter] to continue ");

    while ((choice = getc(stdin)) != '\n'); //eat up their input
    getc(stdin); //clear  input

  }

  for (int i = 0; i < num; i++) // free memory
    free(files[i]);
  free(files);
  
}

int argCheck(int argc, char *argv[]){

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
