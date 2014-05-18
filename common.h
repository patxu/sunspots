#ifndef _COMMON_H_
#define _COMMON_H_

#define YEAR_SIZE 4
#define MONTH_SIZE 2
#define DAY_SIZE 2
#define TIME_SIZE 4


//241940 sunspots, so 100,000 slots may even be a bit small
#define HASH_SIZE 100000

/*
 * a SPOT corresponds to a single sunspot and has information about the sunspot
 */
typedef struct _SPOT {
  struct _SPOT  *next;
  char year[YEAR_SIZE];
  char month[MONTH_SIZE];
  char day[DAY_SIZE];
  float time;
} __SPOT;

typedef struct _SPOT SPOT;

/*
 * a sTable has a hashtable that hold all of the sunspots
 */
typedef struct _sTable {
  SPOT* hash[HASH_SIZE];
} __sTable;

typedef struct _sTable sTable;

#endif 
