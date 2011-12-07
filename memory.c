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
	long double timeD;
	
	printf("<log2(byte array size)>\t<8 MB stride latency>\t<4 MB stride latency>\t<1 MB stride latency>\t<24 KB stride latency>\t<12 KB stride latency>\n");
	for (int i = 8; i <= 31; i++)
	{
		printf("%d\t", i);
		timeD = getMemoryLatency(i,  1000003);
		printf("%.2LF\t", timeD);
		fflush(stdout);

		timeD = getMemoryLatency(i,  510073);
		printf("%.2LF\t", timeD);
		fflush(stdout);

		timeD = getMemoryLatency(i,  125029);
		printf("%.2LF\t", timeD);
		fflush(stdout);

		timeD = getMemoryLatency(i,  4003);
		printf("%.2LF\t", timeD);
		fflush(stdout);

		timeD = getMemoryLatency(i,  2003);
		printf("%.2LF\n", timeD);
		fflush(stdout);
	}
	
	printf("Memory read bandwith = ");
	fflush(stdout);
	timeD = getMemoryReadBandwith();
	timeD = timeD * (2.4e9/1.0e9);
	printf("%.2LF GB/sec\n\n", timeD);
	
	printf("Memory write bandwith = ");
	fflush(stdout);
	timeD = getMemoryWriteBandwith();
	timeD = timeD * (2.4e9/1.0e9);
	printf("%.2LF GB/sec\n\n", timeD);
	
	exit(1);
}
