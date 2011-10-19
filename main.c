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
    unsigned long long time;
    
    time = getMeasureOverhead();
    
    printf("Measurement overhead is %llu cycles\n", time);

    unsigned long long callAvgs[8];
    getProcedureCallOverhead(callAvgs);
	
	printf("Procedure call overhead:\n");
	printf("0 args - %llu\n", callAvgs[0]);
	printf("1 args - %llu\n", callAvgs[1]);
	printf("2 args - %llu\n", callAvgs[2]);
	printf("3 args - %llu\n", callAvgs[3]);
	printf("4 args - %llu\n", callAvgs[4]);
	printf("5 args - %llu\n", callAvgs[5]);
	printf("6 args - %llu\n", callAvgs[6]);
	printf("7 args - %llu\n", callAvgs[7]);
   
    
    exit(1);
    
}