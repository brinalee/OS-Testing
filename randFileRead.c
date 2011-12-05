/*=====================================================================
    randFileRead.c
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
	
	printf("<log file size>\t<log cycle latency per block>\n");
	for (int i = 12; i <= 31; i += 1)
	{
		double timeR = getRandomFileReadTime(i);
		printf("%d\t%.2lf\n", i, timeR);
		fflush(stdout);
	}
}
