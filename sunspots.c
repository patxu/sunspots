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
#include "average.h"


int main(int argc, char *argv[]){

  //check that arguments are valid
  if (argCheck(argc, argv) != TRUE){
    printf("Argument Error!\n");
    printf("Please make sure the the two arguments are valid directories\n\n");
    return 1;
  }

  //print start up message
  print(WELCOME);
  enterToContinue();
  
  //main loop that allows the user to use the program
  while (1){
    //print menu and process user choice
    print(MENU);

    printf("Enter your choice here: ");
    char choice = getchar();
    while (getchar() != '\n');

    if (choice == '1'){ //search for sunspots from a particular date
      for (int i = 0; i < 70; i++) printf("\n");
      searchForSpots(argv[1]);
    }
    else if (choice == '2'){ // average sunspot number by month
      monthAverage(argv[2]);
    }
    else if (choice == '3'){
      quiz();
    }
    else if (choice == 'h'){
      print(HELP);
    }
    else if (choice == 'x'){ //exit
      printf("\nExiting!\n\n");
      break; //exit the program
    }
    else{
      printf("\nInvalid choice. Please try again.\n");
    }

    enterToContinue();
  }
}

int argCheck(int argc, char *argv[]){

  if (argc != 3){
    return FALSE;
  } 

  struct stat mydir1;
  if (stat(argv[1], &mydir1) == 0){
    if(!S_ISDIR(mydir1.st_mode)){ //file exists but isn't a directory
      return FALSE;
    }
  }
  else //file doesn't exist
    return FALSE;

  struct stat mydir2;
  if (stat(argv[2], &mydir2) == 0){
    if(!S_ISDIR(mydir2.st_mode)){ //file exists but isn't a directory
      return FALSE;
    }
  }
  else //file doesn't exist
    return FALSE;

  return TRUE;
}

void enterToContinue(){
  printf("\nPress [enter] to continue ");
  char c = getchar(); //ask for user input
  if (c!= '\n')
    while (getchar() != '\n'); //eat up the rest of their input
}

void print(int option){
  for (int i = 0; i < 40; i++) printf("\n");

  FILE* file;
  if (option == WELCOME){
   file = fopen("config/welcome.txt", "r");
    if (file == NULL){
      printf("ERROR: welcome file not found\n");
      return;
    }
  }
  else if (option == MENU){
    file = fopen("config/menu.txt", "r");
    if (file == NULL){
      printf("ERROR: menu file not found\n");
      return;
    }
  }
  else if (option == HELP){
    file = fopen("config/help.txt", "r");
    if (file == NULL){
      printf("ERROR: help file not found\n");
      return;
    }
  }

  char c;
  while ((c = fgetc(file)) != EOF)
    printf("%c", c);

  fclose(file);
  for (int i = 0; i < 10; i++) printf("\n");
}

