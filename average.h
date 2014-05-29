#ifndef _AVERAGE_H_
#define _AVERAGE_H_

/*
 * finds the average number of sunspots of a particular month and compares this to the
 * average number of sunspots across all months. also informs the user how this number
 * compares in the context of the sunspot cycle
 */
void monthAverage(char* dir);

/*
 * gets user input for the month and year
 */
void getMonthandYear(int* month, int* year);

/*
 * gets the overall average number of sunspots per month across all months
 */
int getOverallAverage(char fullpath[]);

#endif
