#ifndef _SUNSPOTS_H_
#define _SUNDPOTS_H_

/*
 * checks the arguments, ensuring that we took in a valid data directory
 */
int argCheck(int argc, char *argv[]);

/*
 * short function that simply waits for the user to press enter before continuing
 */
void enterToContinue();

/*
 * prints out the menu from which users choose what they want to do in the program
 */
void printMenu();

/*
 * prints out the help menu
 */
void printHelp();

/*
 * only called in this fuction- implementation in search.c
 * takes in an array of filenames, the number of files in the data directory, and the
 * name of the data directory, and deals with calling functions to get the user input
 * and parse the files
 */
void searchForSpots(char* dir);

#endif
