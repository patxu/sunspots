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

  for (int i = 0; i < YEAR_SIZE; i++)
    printf("%c", spot->year[i]);

  for (int i = 0; i < MONTH_SIZE; i++)
    printf("%c", spot->month[i]);

  for (int i = 0; i < DAY_SIZE; i++)
    printf("%c", spot->day[i]);

  printf("%f", spot->time);

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

    //addSpot(spot);
    //printSpot(spot);

    while((c = getc(file)) != '\n'); //get to the next line
    c = getc(file);

  }while(c != EOF); 

  fclose(file);
  return TRUE;
}
