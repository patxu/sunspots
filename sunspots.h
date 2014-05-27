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
 * prints out a text file depending on the option selected. the options include a 
 * help, welcome, and main file. view them direction in the config/ directory.
 * view the options in common.h
 */
void print(int option);

/*
 * only called in this fuction- implementation in search.c
 * takes in an array of filenames, the number of files in the data directory, and the
 * name of the data directory, and deals with calling functions to get the user input
 * and parse the files
 */
void searchForSpots(char* dir);

#endif
