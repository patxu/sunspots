#ifndef _COMMON_H_
#define _COMMON_H_

//241940 sunspots, but we only hash with YYYYMMDD string, and we have ~50000 
//days over the period (1874-2013)
#define HASH_SIZE 20000

#define YEAR_SIZE 4
#define MONTH_SIZE 2
#define DAY_SIZE 2
#define TIME_SIZE 4
#define SKIP1_SIZE 28
#define AREA_SIZE 4
#define SKIP2_SIZE 1
#define DISTANCE_SIZE 5
#define SKIP3_SIZE 0
#define DEGREE_SIZE 5

/*
The data format in these the data files is given below.

Columns Quantity
1-4     Year
5-6     Month
7-8     Day of month
9-12    Time in thousandths of day (.500 = 1200 UT)
13-20   Greenwich sunspot group # through 1976; NOAA/USAF grp # after 1976

21-22   00 1874-1976
23-24   Greenwich Group type

21      Suffix to group number 1982 to present
22-24   NOAA Group type (A=Alpha, B=Beta, D=Delta, G=Gamma) 1982 to present

25      Single space
26-29   Observed umbral area in millionths of solar disk 1874 through 1976

26-29      0 from 1977 to present (umbral area unavailable from NOAA)

30      Single space
31-34   Observed whole spot area in mill. of sol. disk
35      Single space
36-39   Corrected (for foreshortening) umbral area in millionths of solar
        hemisphere, 1874 through 1976

36-39       0 from 1977 to present (umbral area unavailable from NOAA)
40      Single space
41-44   Corrected whole spot area in millionths of solar hemisphere
45      Single space
46-50   Distance from center of solar disk in disk radii
51      Single space
52-56   Position angle from heliographic north (0=north, 90=east limb)
57      Single space
58-62   Carrington Longitude in degrees
63      Single space
64-68   Latitude, negative to the South
69      Single space
70-74   Central  meridian distance, negative to the East.
*/


/*
 * a SPOT corresponds to a single sunspot and has information about the sunspot
 */
typedef struct _SPOT {
  struct _SPOT  *next;
  char year[YEAR_SIZE];
  char month[MONTH_SIZE];
  char day[DAY_SIZE];
  float time;
  float area;
  float x;
  float y;
} __SPOT;

typedef struct _SPOT SPOT;

/*
 * a sTable has a hashtable that holds all of the sunspots
 */
typedef struct _sTable {
  SPOT* hash[HASH_SIZE];
} __sTable;

typedef struct _sTable sTable;

#endif 
