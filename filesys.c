/*=====================================================================
    filesys.c
    Description         : Main function for file system measurements
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
	//long double timeD;
	long mb = 1000000;
	
	printf("<MB file size>\t<8 MB stride latency>\t<4 MB stride latency>\t<1 MB stride latency>\t<24 KB stride latency>\t<12 KB stride latency>\n");
	for (long i = 1000; i <= 2100; i += 100)
	{
		// 1000003, 510073, 125029, 4003, 2003
		printf("%li\t", i);
		fflush(stdout);
		
		timeS = getCachedIOLatency(i * mb,  1000003);
		printf("%lli\t", timeS);
		fflush(stdout);
		
		timeS = getCachedIOLatency(i * mb, 510073);
		printf("%lli\t", timeS);
		fflush(stdout);
		
		timeS = getCachedIOLatency(i * mb, 125029);
		printf("%lli\t", timeS);
		fflush(stdout);
		
		timeS = getCachedIOLatency(i * mb, 4003);
		printf("%lli\t", timeS);
		fflush(stdout);
		
		timeS = getCachedIOLatency(i * mb, 2003);
		printf("%lli\n", timeS);
		fflush(stdout);
	}
}
