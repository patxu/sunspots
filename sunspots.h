#ifndef _SUNSPOTS_H_
#define _SUNDPOTS_H_

#define FALSE 0
#define TRUE 1

/*
 * a SPOT corresponds to a single sunspot and has information about the sunspot
 */
typedef struct _SPOT {
  struct _SPOT  *next;
  char* year;
} __SPOT;

typedef struct _SPOT SPOT;

/*
 * checks the arguments, ensuring that we took in a valid data directory
 */
int argcheck(int argc, char *argv[]);

/*
 * given a SPOT, it will print out all the information about the spot
 */
void printspot(SPOT* spot);

#endif
