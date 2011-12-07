
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "benchmarks.h"

int main(int argc, char *argv[])
{
	long long timeS;
	long double timeD;
	
	printf("<# Contending Threads>\t<sequential read latency per block in us>\n");
	for (int i = 1; i <= 16; i++)
	{
		// 1000003, 510073, 125029, 4003, 2003
		printf("%d\t", i);
		fflush(stdout);
		
		timeS = getFileContentionOverhead(i);
		timeD = (long double) timeS;
		printf("%.2LF\n", timeD / 2.4e3);
		fflush(stdout);
	}
}
