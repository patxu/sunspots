#ifndef _SUNSPOTS_H_
#define _SUNDPOTS_H_

#define FALSE 0
#define TRUE 1

/*
 * checks the arguments, ensuring that we took in a valid data directory
 */
int argCheck(int argc, char *argv[]);

/*
 * given a SPOT, it will print out all the information about the spot
 */
void printSpot(SPOT* spot);

/*
 * given a directory, it will set up an array with all the filenames of that directory
 * and return the number of files, or -1 if failure
 */
int getFiles(const char *dir, struct dirent ***namelist,
   int(*select)(const struct dirent *),
   int(*compar)(const struct dirent **, const struct dirent **));

/*
 * given a string, it will open a file and parse the file, and return a spot
 */
int parseFile(char *filename, char* dirname);

#endif
