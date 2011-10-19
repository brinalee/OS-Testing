#ifndef UTILS_H
#define UTILS_H
/*=====================================================================
    UTILS.h
    Description         : Utility functions to be shared between 
                          measurement modules
======================================================================*/

/*=====================================================================
    Defines
======================================================================*/

/*=====================================================================
    Typedefs
======================================================================*/

/*=====================================================================
    Constants
======================================================================*/

/*=====================================================================
    Functions
======================================================================*/
double calculate_average(int* array_ints, int num_ints);

unsigned long long calculate_average_long_long(unsigned long long* array_longs, int num_longs);

inline unsigned long long rdtsc(void)
{
     unsigned int lo, hi;
     __asm__ volatile ("rdtsc" : "=a" (lo), "=d" (hi));
     return ((unsigned long long)hi << 32 | lo);
}


#endif
