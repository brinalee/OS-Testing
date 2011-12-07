/*=====================================================================
    seqRemoteFileRead.c
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
	char filename[33];
	printf("<log file size>\t<log cycle latency per block>\n");
	for (int i = 12; i <= 31; i += 1)
	{
		sprintf(filename, "remote_mount/test_seq_log.dat");
		double timeR = getSequentialFileReadTime(i, filename, true);
		printf("%d\t%.2lf\n", i, timeR);
		fflush(stdout);
	}
}
