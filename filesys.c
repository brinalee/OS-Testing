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
	
	printf("<log2(byte file size)>\t<8 MB stride latency>\t<4 MB stride latency>\t<1 MB stride latency>\t<24 KB stride latency>\t<12 KB stride latency>\n");
	for (int i = 8; i <= 20; i++)
	{
		// 1000003, 510073, 125029, 4003, 2003
		printf("%d\t", i);
		fflush(stdout);
		
		timeS = getCachedIOLatency(i, 1000003);
		printf("%lli\t", timeS);
		fflush(stdout);
		
		timeS = getCachedIOLatency(i, 510073);
		printf("%lli\t", timeS);
		fflush(stdout);
		
		timeS = getCachedIOLatency(i, 125029);
		printf("%lli\t", timeS);
		fflush(stdout);
		
		timeS = getCachedIOLatency(i, 4003);
		printf("%lli\t", timeS);
		fflush(stdout);
		
		timeS = getCachedIOLatency(i, 2003);
		printf("%lli\n", timeS);
		fflush(stdout);
	}
}
