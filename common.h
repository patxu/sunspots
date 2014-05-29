#ifndef _COMMON_H_
#define _COMMON_H_

////// Defines
//general
#define FALSE 0
#define TRUE 1

//options for printing menus
#define WELCOME 0
#define MENU 1
#define HELP 2

//for SPOTs and parsing files
#define YEAR_LEN 4
#define MONTH_LEN 2
#define DAY_LEN 2
#define TIME_LEN 4
#define SKIP1_LEN 28
#define AREA_LEN 4
#define SKIP2_LEN 1
#define DISTANCE_LEN 5
#define SKIP3_LEN 0
#define DEGREE_LEN 5
#define DATE_LEN YEAR_LEN + MONTH_LEN + DAY_LEN + 2

//for parsing the numspots file
#define SSN_LEN 3

/*
The data format for the /data/ files is given below. Taken from 
config/format.txt

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
The data format for the /data1/ file is given below. Taken from 
config/format1.txt

Columns Quantity
1-4     Year
5-6     Month
7-9     SSN (solar sunspot number)

*/

////// Structures

/*
 * a SPOT corresponds to a single sunspot and has information about the sunspot
 */
typedef struct _SPOT {
  struct _SPOT  *next;
  int year[YEAR_LEN];
  int month[MONTH_LEN];
  int day[DAY_LEN];
  float time;
  float area;
  float x;
  float y;
} __SPOT;

typedef struct _SPOT SPOT;

#endif 
