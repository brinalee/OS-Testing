/*=====================================================================
    UTILS.c
    Description         : Utility functions to be shared between 
                          measurement modules
======================================================================*/

/*=====================================================================
                        INCLUDE FILES 
 ======================================================================*/

/* Standard Libraries */

/* Local Headers */
#include "utils.h"

/*=====================================================================
                    DEFINITIONS AND DECLARATIONS 
======================================================================*/

/* Typedefs and Enums */

/* Constants and Macros */

/* Variables */

/*=====================================================================
                     FUNCTION DECLARATIONS 
======================================================================*/

/* External */

/* Local */

/*=====================================================================
                     FUNCTION DEFINITIONS
======================================================================*/

double calculate_average(int* array_ints, int num_ints)
{
    int i;
    int sum = 0;
    double average = 0;
    
    for (i = 0; i < num_ints; i++)
    {
        sum += array_ints[i];
    }
    average = (double)(sum) / num_ints;
    return average;
}
