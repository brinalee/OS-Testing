/*=====================================================================
    BENCHMARKS.c
    Description         : Utility functions to be shared between 
                          measurement modules
======================================================================*/

/*=====================================================================
                        INCLUDE FILES 
 ======================================================================*/

/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

/* Local Headers */
#include "benchmarks.h"
#include "utils.h"

/*=====================================================================
                    DEFINITIONS AND DECLARATIONS 
======================================================================*/

/* Typedefs and Enums */

/* Constants and Macros */

/* Variables */

/*=====================================================================
                     FUNCTION DECLARATIONS 
======================================================================*/

/* External */

/* Local */

/*=====================================================================
                     FUNCTION DEFINITIONS
======================================================================*/

unsigned long long getMeasureOverhead(void)
{
	unsigned long long times[NUM_COLLECTIONS] = {0};
	unsigned long long time1;
	unsigned long long time2;
	unsigned long long average;
	int i;
	
	for (i = 0; i < NUM_COLLECTIONS; i++) {
		
		time1 = rdtsc();
		time2 = rdtsc();
		times[i] = time2 - time1;
		
		//printf("Time1 = %llu, Time 2 = %llu\n", time1, time2);
	}
	
	average = calculate_average_long_long(times, NUM_COLLECTIONS);
	
	return average;
}

int bogus_test_func0(void)
{
	return 0;
}

int bogus_test_func1(int a1)
{
	return 0;
}

int bogus_test_func2(int a1, int a2)
{
	return 0;
}

int bogus_test_func3(int a1, int a2, int a3)
{
	return 0;
}

int bogus_test_func4(int a1, int a2, int a3, int a4)
{
	return 0;
}

int bogus_test_func5(int a1, int a2, int a3, int a4, int a5)
{
	return 0;
}

int bogus_test_func6(int a1, int a2, int a3, int a4, int a5, int a6)
{
	return 0;
}

int bogus_test_func7(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
	return 0;
}

void getProcedureCallOverhead(long long average[])
{
	long long time1;
	long long time2;
	long long loopOverhead;
	int i;
	int res;
	
	int i1 = rand();
	int i2 = rand();
	int i3 = rand();
	int i4 = rand();
	int i5 = rand();
	int i6 = rand();
	int i7 = rand();
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++) {
		res = 0;
	}
	time2 = rdtsc();
	loopOverhead = (time2 - time1) / (long long) NUM_COLLECTIONS;
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++) {
		res = bogus_test_func0();
	}
	time2 = rdtsc();
	average[0] = ((time2 - time1) / (long long) NUM_COLLECTIONS) - loopOverhead;
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++) {
		res = bogus_test_func1(i1);
	}
	time2 = rdtsc();
	average[1] = ((time2 - time1) / (long long) NUM_COLLECTIONS) - loopOverhead;
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++) {
		res = bogus_test_func2(i1,i2);
	}
	time2 = rdtsc();
	average[2] = ((time2 - time1) / (long long) NUM_COLLECTIONS) - loopOverhead;
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++) {
		res = bogus_test_func3(i1,i2,i3);
	}
	time2 = rdtsc();
	average[3] = ((time2 - time1) / (unsigned long long) NUM_COLLECTIONS) - loopOverhead;
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++) {
		res = bogus_test_func4(i1,i2,i3,i4);
	}
	time2 = rdtsc();
	average[4] = ((time2 - time1) / (long long) NUM_COLLECTIONS) - loopOverhead;
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++) {
		res = bogus_test_func5(i1,i2,i3,i4,i5);
	}
	time2 = rdtsc();
	average[5] = ((time2 - time1) / (long long) NUM_COLLECTIONS) - loopOverhead;
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++) {
		res = bogus_test_func6(i1,i2,i3,i4,i5,i6);
	}
	time2 = rdtsc();
	average[6] = ((time2 - time1) / (long long) NUM_COLLECTIONS) - loopOverhead;
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++) {
		res = bogus_test_func7(i1,i2,i3,i4,i5,i6,i7);
	}
	time2 = rdtsc();
	average[7] = ((time2 - time1) / (long long) NUM_COLLECTIONS) - loopOverhead;

}

void printSingleProcessCreateTime(void)
{
	pid_t piD;
	unsigned long long firstTime = 0;
	unsigned long long secondTime = 0;
	//unsigned long long spanTime = 0;
	//globalTime = 0;
	int childExitStatus;

	
	firstTime = rdtsc();
	piD = fork();
	secondTime = rdtsc();
	if (piD == 0) {
		fprintf(stderr, "%llu\n", secondTime);
		fflush(stderr);
		//printf("child now, secondTime = %llu\n", secondTime);
		//globalTime = secondTime;
		//printf("child now, globalTime = %llu\n", globalTime);
		exit(1);
	} else {
		waitpid(piD, &childExitStatus, 0);
		printf("%llu,%llu\n", firstTime, secondTime);
		fflush(stdout);
		//printf("firstTime = %llu, secondTime = %llu, globalTime = %llu\n", firstTime, secondTime, globalTime);
		//secondTime = (globalTime < secondTime) ? globalTime : secondTime;
		//spanTime = secondTime - firstTime;
	}
	return;
}

void* thread_run(void* llu_ptr)
{
	unsigned long long time = rdtsc();
	//printf("Child: time=%llu\n", time);
	unsigned long long* outTime = (unsigned long long*)llu_ptr;
	*outTime = time;
	return 0;
}

unsigned long long getSingleThreadCreateTime(void)
{
	unsigned long long firstTime = 0;
	unsigned long long secondTime = 0;
	pthread_t thread;
	int rc;
	
	firstTime = rdtsc();
	rc = pthread_create(&thread, NULL, thread_run, (void *)(&secondTime));
	if (rc){
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		return 0;
	}
	pthread_join(thread, NULL);
	//printf("Parent: secondTime=%llu\n", secondTime);
	return secondTime - firstTime;
}

unsigned long long getSingleThreadCreateOverhead(void)
{
	unsigned long long total = 0;
	for (int i = 0; i < NUM_COLLECTIONS; i++) {
		total += getSingleThreadCreateTime();
	}
	return total / ((unsigned long long) NUM_COLLECTIONS);
}
