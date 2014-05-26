#ifndef _SEARCH_H_
#define _SEARCH_H_


/*
 * takes in an array of filenames, the number of files in the data directory, and the
 * name of the data directory, and deals with calling functions to get the user input
 * and parse the files
 */
void searchForSpots(char* dir);

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
 * gets the search string from the user, returning TRUE if successful and FALSE
 * if failed. will return failure if the string is in the incorrect format
 */
int getSearchTerm(char** searchTerm, int* year, int* month, int* day);

/*
 * given a string, it will open a file and parse the file, and return a spot
 */
int parseFile(char *filename, char* dirname, int year, int month, int day);

#endif
