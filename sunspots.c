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

  initHash();

  //parse files
  for (int i = 2; i < num; i++) {

    if (parseFile(files[i]->d_name, argv[1]) == FALSE)
      printf("Could not parse file: %s\n", files[i]->d_name);
    else{ 
    }
    free(files[i]);
  }

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

void printSpot(SPOT* spot){

  printf("The spot was observed on ");
  
  for (int i = 0; i < MONTH_SIZE; i++){
    if (spot->day[i] == ' ')
      continue;
    printf("%c", spot->month[i]);
  }
  printf("/");

  for (int i = 0; i < DAY_SIZE; i++){
    if (spot->day[i] == ' ')
      continue;
    printf("%c", spot->day[i]);
  }
  printf("/");

  for (int i = 0; i < YEAR_SIZE; i++)
    printf("%c", spot->year[i]);

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

int parseFile(char* filename, char* dirname){

  char fullpath[strlen(filename) + strlen(dirname) + 1]; 
  if (dirname[strlen(dirname)-1] != '/')
    sprintf(fullpath, "%s%c%s", dirname, '/', filename);
  else
    sprintf(fullpath, "%s%s", dirname, filename);
  
  FILE* file = fopen(fullpath, "r");
  if (file == NULL)
    return FALSE;

  SPOT* spot = malloc(sizeof(SPOT)); 
  char c = getc(file);

  do{
    //get YEAR data
    for (int i = 0; i < YEAR_SIZE; i++){
      spot->year[i] = c;
      c = getc(file);
    }

    //get MONTH data
    for (int i = 0; i < MONTH_SIZE; i++){
      spot->month[i] = c;
      c = getc(file);
    }

    //get DAY data
    for (int i = 0; i < DAY_SIZE; i++){
      spot->day[i] = c;
      c = getc(file);
    }

    //get TIME data
    char time[TIME_SIZE];
    for (int i = 0; i < TIME_SIZE; i++){
      time[i] = c;
      c = getc(file);
    }
    sscanf(time, "%f", &spot->time);
    spot->time *= 24; //converts to 24 hour format

    for (int i = 0; i < SKIP1_SIZE; i++)
      getc(file);
    
    //get AREA data
    char area[AREA_SIZE];
    for (int i = 0; i < AREA_SIZE; i++){
      area[i] = c;
      c = getc(file);
    }
    if (area[AREA_SIZE - 1] == '0')
      spot->area = -1; //data unavaiable
    else{
      sscanf(area, "%f", &spot->area);
      spot->area *= .0001; //converts to percentage; 100/1,000,000
    }
    
    for (int i = 0; i < SKIP2_SIZE; i++)
      getc(file);

    //get RADIUS from solar center
    char distance[DISTANCE_SIZE];
    for (int i = 0; i < DISTANCE_SIZE; i++){
      distance[i] = c;
      c = getc(file);
    }
    float radius;
    sscanf(distance, "%f", &radius);

    for (int i = 0; i < SKIP3_SIZE; i++)
      getc(file);

    //get DEGREES from heliographic north
    char degree[DEGREE_SIZE];
    for (int i = 0; i < DEGREE_SIZE; i++){
      degree[i] = c;
      c = getc(file);
    }
    float angle;
    sscanf(degree, "%f", &angle);

    if (distance[DISTANCE_SIZE - 1] == '0'){
      spot->x = -1; //coordinate data unavailable
      spot->y = -1;
    }
    else { //convert from polar to cartesian coordinates
      spot->x = radius * cosf(angle * PI / 180);
      spot->y = radius * sinf(angle * PI / 180);
    }
    
    char hash[YEAR_SIZE + MONTH_SIZE + DAY_SIZE];
    for (int i = 0; i < (YEAR_SIZE + MONTH_SIZE + DAY_SIZE); i++){
      if (i < YEAR_SIZE)
	hash[i] = spot->year[i];
      else if (i < YEAR_SIZE + MONTH_SIZE)
	hash[i] = spot->month[i - YEAR_SIZE];
      else
	hash[i] = spot->day[i - YEAR_SIZE - MONTH_SIZE];
    }
    
    //printSpot(spot);
    if (strcmp(spot->year,"1874") == 1 && strcmp(spot->month,"12") == 1 && strcmp(spot->day, "31") == 1)
      printf("here\n");

    //printSpot(spot);
    addSpot(spot, hash);

    while((c = getc(file)) != '\n'); //get to the next line
    c = getc(file);

  }while(c != EOF); 

  fclose(file);
  return TRUE;
}
