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

sTable* table;

//hash called djb2
unsigned long hash(char* str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++) != 0)
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  return hash % HASH_SIZE;
}

void initHash(){

  table = malloc(sizeof(sTable));

  for (int i = 0; i < HASH_SIZE; i++)
    table->hash[i] = NULL;

}

void addSpot(SPOT* spot, char hashString[]){

  int num = hash(hashString);
  spot->next = NULL;
   // printf("%d\n", num);

  if (table->hash[num] == NULL){ //non collision case
    table->hash[num] = spot; 
  }
  else{ //collision case- search for end of collision (next = NULL)
    SPOT* temp = table->hash[num];
    while (1) { 
    //  printSpot(temp);
      if (temp->next == NULL) {
	temp->next = spot;
	break; 
      }
      temp = temp->next;
    }
  }
  if (num == 914581){
    printf("%s : ", hashString);
    printf("%f : ", spot->time);
    printf("%d\n", num);
  }

}
