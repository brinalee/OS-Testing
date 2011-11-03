/*=====================================================================
    pageFault.c
    Description         : Main function for page fault measurements
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
	long long timeS;
	
	//printf("Page fault overhead = ");
	fflush(stdout);
	timeS = getPageFaultOverhead();
	//printf("%lli cycles\n\n", timeS);
	
	exit(1);
}
