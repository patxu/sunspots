/*
 * author: Patrick Xu
 *
 * file: hash.c
 *
 * description: deals with the sunspot hashtable, namely adding and retrieving SPOTS
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "common.h"

//sTable* sTable = NULL;

//hash called djb2
unsigned long hash(char* str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++) != 0)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % HASH_SIZE;
}


void addSpot(SPOT* spot, char hashString[]){

  
  int num = hash(hashString);

  printf("%d\n", num);

}
