/*
 * author: Patrick Xu
 *
 * average.c
 *
 * finds the average number of sunspots of a particular month and compares this to the
 * average number of sunspots across all months. also informs the user how this number
 * compares in the context of the sunspot cycle
 * 
 */

#define _SVID_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#include "common.h"
#include "average.h"
#include "search.h" //for getFiles

void monthAverage(char* dir){
  int month = -1, year = -1; 

  getMonthandYear(&month, &year);

  //get data folder file into an array
  struct dirent **files;
  int num;
  if ((num = getFiles(dir, &files, NULL, alphasort)) == -1){
    printf("Error when reading data files\n");
    return;
  }
  
  char fullpath[strlen(files[2]->d_name) + strlen(dir) + 1]; 
  if (dir[strlen(dir)-1] != '/')
    sprintf(fullpath, "%s%c%s", dir, '/', files[2]->d_name);
  else
    sprintf(fullpath, "%s%s", dir, files[2]->d_name);

  FILE* file = fopen(fullpath, "r");
  if (file == NULL)
    printf("Could not open file: %s\n", files[2]->d_name);

  char c = getc(file);
  int ssn = -1, mTemp, yTemp;

  do{
    //skip YEAR data
    char y[YEAR_LEN];
    for (int i = 0; i < YEAR_LEN; i++){
      y[i] = c;
      c = getc(file);
    }
    sscanf(y, "%d", &yTemp);

    //skip MONTH data
    char m[MONTH_LEN];
    for (int i = 0; i < MONTH_LEN; i++){
      m[i] = c;
      c = getc(file);
    }
    sscanf(m, "%d", &mTemp);

    if (month != mTemp || year != yTemp) {
      while((c = getc(file)) != '\n'); //get to the next line/sunspot
      c = getc(file);
      continue;
    }

    //get SSN data
    char s[SSN_LEN];
    for (int i = 0; i < SSN_LEN; i++){
      s[i] = c;
      c = getc(file);
    }
    sscanf(s, "%d", &ssn);
    break;//found our month, so we can exit

  }while(c != EOF); 
  
  int avg = getOverallAverage(fullpath);

  if (ssn == -1)
    printf("\nCould not find month average for the requested year and month\n");
  else{
    printf("\nMonthly average for %d/%d is %d\n", month, year, ssn);
    printf("Average between all months is %d\n\n", avg);
    if (ssn <= avg*.4)
      printf("This year is likley near a minimum in the sunspot cycle\n");
    else if (ssn >= avg*1.5)
      printf("This year is likely near a maximum in the sunspot cycle\n");
    else
      printf("This was year somehwere in the middle of a sunspot cycle\n");
  }

  fclose(file); 
}

void getMonthandYear(int* month, int* year){

  while (1) {
    printf("\nEnter a year (1749-2014): ");
    scanf("%d", year);
    if (!(*year > 1748 && *year < 2015))
      printf("Invalid year\n");
    else
      break;
  }
  char c = getchar(); //clean up user input
  if (c!= '\n')
    while (getchar() != '\n');
  
  if (*year == 2014){
    while (1){
      printf("\nEnter a month (1-4): ");
      scanf("%d", month);
      if (!(*month > 0 && *month < 4))
	printf("Invalid month\n");
      else
	break;
    }
  }

  else{
    while (1){
      printf("\nEnter a month (1-12): ");
      scanf("%d", month);
      if (!(*month > 0 && *month < 13))
	printf("Invalid month\n");
      else
	break;
    }
  }

  c = getchar(); //clean up user input
  if (c!= '\n')
    while (getchar() != '\n'); 

}

int getOverallAverage(char fullpath[]){

  FILE* file = fopen(fullpath, "r");
  int ssnTotal = 0, temp, monthTotal = 0;
  char c = getc(file);

  do{
    //skip YEAR data
    for (int i = 0; i < YEAR_LEN; i++){
      c = getc(file);
    }

    //skip MONTH data
    for (int i = 0; i < MONTH_LEN; i++){
      c = getc(file);
    }
    monthTotal++;

    //get SSN data
    char ssn[SSN_LEN];
    for (int i = 0; i < SSN_LEN; i++){
      ssn[i] = c;
      c = getc(file);
    }
    sscanf(ssn, "%d", &temp);
    ssnTotal += temp;
      
    while((c = getc(file)) != '\n'); //get to the next line
    c = getc(file);

  }while(c != EOF); 

  fclose(file);
  return ssnTotal/monthTotal;
}
