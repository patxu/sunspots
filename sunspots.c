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
#define PI 3.14159265

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <math.h>

#include "common.h"
#include "sunspots.h"
#include "hash.h"


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
  //while (choice != 'e'){
    //make the search string that we use to store the query
    char* searchTerm = malloc(sizeof(char) * DATE_LEN); //MM/DD/YYYY
    for (int i = 0; i < DATE_LEN; i++)
      searchTerm[i] = '\0';

    int year, month, day;
    char c;
    while (getSearchTerm(&searchTerm, &year, &month, &day) != TRUE){
      printf("\nInvalid search term. Please try again.\n\n");
      while ((c = getc(stdin)) != '\n'); //cleans up the input line
    }


    //parse files- skip first 2 files because those are . and ..
    int found  = FALSE;
    for (int i = 2; i < num; i++) {
      if (parseFile(files[i]->d_name, argv[1], year, month, day) == TRUE)
	found = TRUE;
    }

    if (found == FALSE)
      printf("\nThere were no sunspots that day!\n\n");

//  }

  for (int i = 0; i < num; i++)
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

int getSearchTerm(char** searchTerm, int* year, int* month, int* day){

  printf("Please enter your search date in the format MM/DD/YYYY: ");
  scanf("%10s", *searchTerm);

  for (int i = 0; i < DATE_LEN; i++){
    if (i == MONTH_LEN || i == MONTH_LEN + DAY_LEN + 1){
      if ((*searchTerm+i)[0] != '/')
	return FALSE;
    }
    else if ((*searchTerm+i)[0] < 48 || (*searchTerm+i)[0] > 57)
	return FALSE;
  }

  sscanf(*searchTerm, "%d/%d/%d", month, day, year);

  return TRUE;
}

void printSpot(SPOT* spot){

  printf("The spot was observed on ");
  
  printf("%d/%d/%d", *spot->month, *spot->day, *spot->year);

  printf(" at ");
  int hours, minutes;
  minutes = spot->time * 60; // convert time from hours to minutes
  hours =  minutes / 60;
  minutes = minutes % 60;
  printf("%.2d:%.2d UT", hours, minutes);
  
  if (spot->area == -1) //area unavailable
    printf("\nArea unavailable");
  else{
    printf("\nIt has an area of %.4f%% Solar Hemispheres", spot->area); //%% prints % sign
  }

  if (spot->x == -1) //coordinates unavailable
    printf("\nCoordinates unavailable\n");
  else
    printf("\nCoordinates: (%.2f,%.2f)\n", spot->x, spot->y);

  printf("\n");

}

int getFiles(const char *dir, struct dirent ***files,
   int(*select)(const struct dirent *),
   int(*compar)(const struct dirent **, const struct dirent **)){
   
  int num = scandir(dir, files, NULL, compar);
  if (num == -1)
    printf("ERROR: could not find files in %s", dir);

  return num; /*will return the number of files in the directory*/ 
}

int parseFile(char *filename, char* dirname, int year, int month, int day){

  char fullpath[strlen(filename) + strlen(dirname) + 1]; 
  if (dirname[strlen(dirname)-1] != '/')
    sprintf(fullpath, "%s%c%s", dirname, '/', filename);
  else
    sprintf(fullpath, "%s%s", dirname, filename);
  
  FILE* file = fopen(fullpath, "r");
  if (file == NULL)
    printf("Could not open file: %s\n", filename);

  int found = FALSE;

  SPOT* spot = malloc(sizeof(SPOT)); 
  char c = getc(file);

  do{
    //get YEAR data
    char y[YEAR_LEN];
    for (int i = 0; i < YEAR_LEN; i++){
      y[i] = c;
      c = getc(file);
    }
    sscanf(y, "%d", spot->year);

    if (year != *spot->year) //check that the year matches
      return FALSE;

    //get MONTH data
    char m[MONTH_LEN];
    for (int i = 0; i < MONTH_LEN; i++){
      m[i] = c;
      c = getc(file);
    }
    sscanf(m, "%d", spot->month);

    //get DAY data
    char d[DAY_LEN];
    for (int i = 0; i < DAY_LEN; i++){
      d[i] = c;
      c = getc(file);
    }
    sscanf(d, "%d", spot->day);

      
    if (month != *spot->month || day != *spot->day) {
      while((c = getc(file)) != '\n'); //get to the next line
      c = getc(file);
      continue;
    }

    //get TIME data
    char time[TIME_LEN];
    for (int i = 0; i < TIME_LEN; i++){
      time[i] = c;
      c = getc(file);
    }
    sscanf(time, "%f", &spot->time);
    spot->time *= 24; //converts to 24 hour format

    for (int i = 0; i < SKIP1_LEN; i++)
      getc(file);
    
    //get AREA data
    char area[AREA_LEN];
    for (int i = 0; i < AREA_LEN; i++){
      area[i] = c;
      c = getc(file);
    }
    if (area[AREA_LEN - 1] == '0')
      spot->area = -1; //data unavaiable
    else{
      sscanf(area, "%f", &spot->area);
      spot->area *= .0001; //converts to percentage; 100/1,000,000
    }
    
    for (int i = 0; i < SKIP2_LEN; i++)
      getc(file);

    //get RADIUS from solar center
    char distance[DISTANCE_LEN];
    for (int i = 0; i < DISTANCE_LEN; i++){
      distance[i] = c;
      c = getc(file);
    }
    float radius;
    sscanf(distance, "%f", &radius);

    for (int i = 0; i < SKIP3_LEN; i++)
      getc(file);

    //get DEGREES from heliographic north
    char degree[DEGREE_LEN];
    for (int i = 0; i < DEGREE_LEN; i++){
      degree[i] = c;
      c = getc(file);
    }
    float angle;
    sscanf(degree, "%f", &angle);

    if (distance[DISTANCE_LEN - 1] == '0'){
      spot->x = -1; //coordinate data unavailable
      spot->y = -1;
    }
    else { //convert from polar to cartesian coordinates
      spot->x = radius * cosf(angle * PI / 180);
      spot->y = radius * sinf(angle * PI / 180);
    }
    
    /*char hash[YEAR_LEN + MONTH_LEN + DAY_LEN];
    for (int i = 0; i < (YEAR_LEN + MONTH_LEN + DAY_LEN); i++){
      if (i < YEAR_LEN)
	hash[i] = spot->year[i];
      else if (i < YEAR_LEN + MONTH_LEN)
	hash[i] = spot->month[i - YEAR_LEN];
      else
	hash[i] = spot->day[i - YEAR_LEN - MONTH_LEN];
    }*/
    
    printSpot(spot);
    found = TRUE;
    
    //addSpot(spot, hash);

    while((c = getc(file)) != '\n'); //get to the next line
    c = getc(file);

  }while(c != EOF); 

  fclose(file);

  if (found == TRUE)
    return TRUE;
  return FALSE;
}
