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
#include "benchmarks.h"

int main(int argc, char *argv[])
{
	for (int i = 0; i < NUM_COLLECTIONS; i++) {
		printSingleProcessCreateTime();
	}

    exit(1);
    
}
