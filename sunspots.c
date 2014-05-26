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
    printf("Please make sure the the only argument is a valid data folder\n\n");
    return 1;
  }

  //print start up menu
  for (int i = 0; i < 50; i++) printf("\n");
  for (int i = 0; i < 70; i++) printf("~");
  printf("\nHello! Welcome to Pat's Sunspot and Solar Sunspot Cycle program. Please\n");
  printf("use the help menu if this is your first time using the program. Enjoy!\n");
  printf("\nContact the creator at xu.17@dartmouth.edu.\n");
  printf("View the GitHub project at github.com/patxu/sunspots\n");
  for (int i = 0; i < 70; i++) printf("~");
  for (int i = 0; i < 10; i++) printf("\n");

  enterToContinue();
  
  //main loop that allows the user to use the program
  while (1){

    //print menu and process user choice
    printMenu();

    for (int i = 0; i < 10; i++) printf("\n");
    printf("Enter your choice here: ");
    char choice = getchar();
    while (getchar() != '\n');

    if (choice == '1'){ //search for sunspots from a particular date
      printf("\n");
      searchForSpots(argv[1]);
    }
    else if (choice == '2'){ //information about the sunspot cycle 
      printf("\n");
    }
    else if (choice == 'h'){
      printf("\n");
      printHelp();
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

void enterToContinue(){
  printf("\nPress [enter] to continue ");
  char c = getchar(); //ask for user input
  if (c!= '\n')
    while (getchar() != '\n'); //eat up the rest of their input
}

void printMenu(){
  for (int i = 0; i < 40; i++) printf("\n");
  printf("\n\t\tMenu\n");
  for (int i = 0; i < 43; i++) printf("~");
  printf("\n[1] Search for Sunspots by Date\n");
  printf("[2] Learn about the Solar Sunspot Cycle\n");
  printf("\n[h] Print Help\n");
  printf("[x] Exit\n");
  for (int i = 0; i < 43; i++) printf("~");
}

void printHelp(){

  for (int i = 0; i < 40; i++) printf("\n");
  for (int i = 0; i < 72; i++) printf("~");
  printf("\nThis is a program created for ASTR1. It focuses on sunspots and the\n");
  printf("solar sunspot cycle. The program is able to several different things:\n");

  printf("\n[1] Search for Sunspots by Date\n");
  printf("\tThis function allows the user to input a date between 05/01/1875 \n");
  printf("\tand 12/31/2013. It will return to the user all the sunspots\n");
  printf("\tobserved on that date\n");
  
  printf("\n[2] Learn about the Solar Sunspot Cycle\n");
  printf("\tnot complete\n");
  for (int i = 0; i < 72; i++) printf("~");
  for (int i = 0; i < 10; i++) printf("\n");
}
