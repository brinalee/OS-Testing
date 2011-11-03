/*=====================================================================
    Memory.c
    Description         : Main function for memory measurements
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
	long double timeD;
	
	printf("Memory read bandwith = ");
	fflush(stdout);
	timeD = getMemoryReadBandwith();
	timeD = timeD * (2.4e9/1.0e9);
	printf("%LF GB/sec\n\n", timeD);
	
	printf("Memory write bandwith = ");
	fflush(stdout);
	timeD = getMemoryWriteBandwith();
	timeD = timeD * (2.4e9/1.0e9);
	printf("%LF GB/sec\n\n", timeD);
	
	printf("<log2(array size)>\t<latency in cycles>\n");
	for (int i = 6; i <= 28; i++)
	{
		timeS = getMemoryLatency(i);
		printf("%d\t%lli\n", i, timeS);
	}
	exit(1);
}
