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
	
	printf("<log2(array size)>\t<latency in cycles>\n");
	for (int i = 6; i <= 28; i++)
	{
		timeS = getMemoryLatency(i);
		printf("%d\t%lli\n", i, timeS);
	}
	exit(1);
}
