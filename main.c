/*=====================================================================
    Main.c
    Description         : Main function for measurements
======================================================================*/

/*=====================================================================
                        INCLUDE FILES 
 ======================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    int array[] = {1, 3, 5, 6, 2, 4, 6};
    int num_ints = 7;
    double result;
    
    result = calculate_average(array, num_ints);
    
    printf("Average is %g", result);
    
    exit(1);
    
}
