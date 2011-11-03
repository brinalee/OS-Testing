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
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <math.h>
#include <limits.h>

/* Local Headers */
#include "benchmarks.h"
#include "utils.h"

/*=====================================================================
                    DEFINITIONS AND DECLARATIONS 
======================================================================*/

/* Typedefs and Enums */

/* Constants and Macros */

/* Variables */

// used to measure context switch oerhead
const long long numThreadSwitches = 10000000;
const long long numMemAccesses = 100000000;


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

unsigned long long getLoopOverhead(void)
{
	unsigned long long time1;
	unsigned long long time2;
	int i;
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++) {
	}
	time2 = rdtsc();
	
	return (time2 - time1) / ((unsigned long long) NUM_COLLECTIONS);
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
	//unsigned long long time = rdtsc();
	//printf("Child: time=%llu\n", time);
	//unsigned long long* outTime = (unsigned long long*)llu_ptr;
	//*outTime = time;
	return 0;
}

void* thread_switch(void* idt)
{
	unsigned long long localSwitches = numThreadSwitches / 2;
	unsigned long long switchCount = 0;
	
	for (; switchCount < localSwitches; switchCount++)
	{
		sched_yield();
	}
	
	return 0;
}

long long getThreadContextSwitchOverhead(unsigned long long threadRunOverhead)
{
	pthread_t thread1;
	unsigned long long time1, time2;
	
	long long localSwitches = numThreadSwitches / 2;
	long long switchCount = 0;
	
	time1 = rdtsc();
	pthread_create(&thread1, NULL, thread_switch, NULL);
	
	for (; switchCount < localSwitches; switchCount++)
	{
		sched_yield();
	}
	
	pthread_join(thread1, NULL);
	time2 = rdtsc();
	
	
	return (time2 - time1 - threadRunOverhead) / numThreadSwitches;
}

unsigned long long getSingleThreadRunTime(void)
{
	unsigned long long firstTime = 0;
	unsigned long long secondTime1 = 0;
	unsigned long long secondTime2 = 0;
	pthread_t thread;
	int rc;
	
	firstTime = rdtsc();
	rc = pthread_create(&thread, NULL, thread_run, (void *)(&secondTime2));
	pthread_join(thread, NULL);
	secondTime1 = rdtsc();
	
	if (rc){
		printf("ERROR; return code from pthread_create() is %d\n", rc);
		return 0;
	}
	//secondTime1 = (secondTime1 < secondTime2) ? secondTime1 : secondTime2;
	//printf("Parent: secondTime=%llu\n", secondTime);
	return secondTime1 - firstTime;
}

unsigned long long getSingleThreadRunOverhead(void)
{
	//unsigned long long minTime = getSingleThreadRunTime();
	unsigned long long total = 0;
	for (int i = 0; i < NUM_COLLECTIONS; i++) {
		total += getSingleThreadRunTime();
		//minTime = (nextTime < minTime) ? nextTime : minTime;
	}
	return total / ((unsigned long long) NUM_COLLECTIONS);
}

unsigned long long getSingleProcessRunTime(void)
{
	pid_t piD;
	unsigned long long time1, time2;//, condOverhead;
	time2 = 0;
	int childExitStatus;
	
	time1 = rdtsc();
	piD = fork();
	if (piD == 0) {
		//fprintf(stderr, "%llu\n", secondTime);
		//fflush(stderr);
		//printf("child now, secondTime = %llu\n", secondTime);
		//globalTime = secondTime;
		//printf("child now, globalTime = %llu\n", globalTime);
		exit(1);
	} else {
		waitpid(piD, &childExitStatus, 0);
		time2 = rdtsc();
		//printf("childExitStatus=%d\n", childExitStatus);
		//printf("%llu,%llu\n", firstTime, secondTime);
		//fflush(stdout);
		//printf("firstTime = %llu, secondTime = %llu, globalTime = %llu\n", firstTime, secondTime, globalTime);
		//secondTime = (globalTime < secondTime) ? globalTime : secondTime;
		//spanTime = secondTime - firstTime;
	}
	return time2 - time1;
}

unsigned long long getProcessContextSwitchOverhead(unsigned long long processRunOverhead)
{
	unsigned long long time1, time2;
	int childExitStatus;
	pid_t piD;
	
	long long totalSwitches = numThreadSwitches;
	long long switchCount = 0;
	long long localSwitches = totalSwitches / 2;
	
	time1 = rdtsc();
	piD = fork();
	if (piD == 0)
	{ // child 1's execution domain
		for (; switchCount < localSwitches; switchCount ++)
		{
			sched_yield();
		}
		exit(1);
	} else {
		for (; switchCount < localSwitches; switchCount ++)
		{
			sched_yield();
		}
		waitpid(piD, &childExitStatus, 0);
		//printf("childExitStatus=%d\n", childExitStatus);
		time2 = rdtsc();
	}
	
	//printf("time1=%llu, ", time1);
	//printf("time2=%llu, ", time2);
	//printf("time2-time1=%llu\n", time2-time1);
	//fflush(stdout);
	
	return (time2 - time1 - processRunOverhead) / totalSwitches;
}

unsigned long long getSingleProcessCondOverhead(void)
{
	pid_t piD;
	unsigned long long time1, time2, condOverhead;
	time2 = 0;
	condOverhead = 0;
	
	
	for (int i = 0; i < NUM_COLLECTIONS; i++)
	{
		piD = 0;
		time1 = rdtsc();
		if (piD == 0) {
			time2 = rdtsc();
		} else {
			time2 = 0;
		}
		condOverhead += (time2 - time1);
	
		piD = 1;
		time1 = rdtsc();
		if (piD == 0) {
			time2 = 0;
		} else {
			time2 = rdtsc();
		}
		condOverhead += (time2 - time1);
	}
	return condOverhead / ((unsigned long long) NUM_COLLECTIONS);
}

long long getSingleProcessRunOverhead(void)
{
	long long totalOverhead, condOverhead;
	totalOverhead = getSingleProcessRunTime();
	condOverhead = 0;
	
	int res = 10;
	int step = NUM_COLLECTIONS/res;
	int prog = 0;
	
	printf("Creating, running, and ending a process %i times ... ", NUM_COLLECTIONS);
	fflush(stdout);
	for (int i = 0; i < NUM_COLLECTIONS; i++)
	{
		if (i >= prog) {
			printf("%d%s > ", (i * 100)/NUM_COLLECTIONS, "%");
			fflush(stdout);
			prog += step;
		}
		totalOverhead += getSingleProcessRunTime();
	}
	printf("100%s\n", "%");
	fflush(stdout);
	
	totalOverhead = totalOverhead / ((unsigned long long) NUM_COLLECTIONS);
	//printf("totalOverhead = %lli\n", totalOverhead);
	fflush(stdout);
	condOverhead = getSingleProcessCondOverhead();
	//printf("condOverhead = %lli\n", condOverhead);
	fflush(stdout);
	
	return totalOverhead - condOverhead;
}

long long getSystemCallOverhead(void)
{
	long long time1, time2, loopOverhead;
	int res;
	int i;
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++)
	{
		res = 0;
	}
	time2 = rdtsc();
	loopOverhead = (time2 - time1) / (long long) NUM_COLLECTIONS;
	
	time1 = rdtsc();
	for (i = 0; i < NUM_COLLECTIONS; i++)
	{
		res = getpid();
	}
	time2 = rdtsc();
	
	return ((time2 - time1) / (long long) NUM_COLLECTIONS) - loopOverhead;
}

long long getMemoryLatency(int power)
{
	double arrLenDub = pow(2.0, (double) power);
	int arrLen = (int)arrLenDub;
	
	long long time1, time2, loopOverhead;
	int stride = 9973;
	//int stride = 223;
	
	long long j = 0 + (long long) stride;
	long long i;
	long long maxInt = INT_MAX - stride - 1;
	long long arrLastIdx = (long long) arrLen - 1;
	
	int idx2, ref1, ref2;
	
	time1 = rdtsc();
	for(i = 0; i < numMemAccesses; i++)
	{
		j = j % maxInt;
		//idx1 = (int) (i % arrLastIdx);
		idx2 = (int) (j % arrLastIdx);
		ref1 = 1;
		//ref2 = 2;
		j += stride;
	}
	time2 = rdtsc();
	
	loopOverhead = (time2 - time1) / (numMemAccesses);
	
	int* arr = (int*) malloc(arrLen*sizeof(int));
	for(i = 0; i < arrLen; i++)
	{
		 arr[i] = i;
	}
	
	j = 0 + stride;
	
	time1 = rdtsc();
	for(i = 0; i < numMemAccesses; i++)
	{
		j = j % maxInt;
		//idx1 = (int) (i % arrLastIdx);
		idx2 = (int) (j % arrLastIdx);
		//ref1 = arr[idx1];
		ref2 = arr[idx2];
		j += stride;
	}
	time2 = rdtsc();
	
	free(arr);
	
	return ((time2 - time1) / (numMemAccesses)) - loopOverhead;
}

long double getMemoryWriteBandwith(void)
{
	double arrLenDub = pow(2.0, 18.0);
	int arrLen = (int)arrLenDub;
	
	long long j, ref1, time1, time2, loopOverhead, overhead, dataSize;
	long long numRepeats = 10000;
	
	int i;
	
	//printf("arrLen = %d\n", arrLen);
	//fflush(stdout);
	
	
	
	time1 = rdtsc();
	for (j = 0; j < numRepeats; j++)
	{
		//printf("j=%lli,", j);
		for(i = 0; i < arrLen; i++)
		{
			ref1 = j;
		}
	}
	time2 = rdtsc();
	
	//printf("here2\n");
	//fflush(stdout);
	
	loopOverhead = time2 - time1;
	
	int* arr = (int*) malloc(arrLen*sizeof(long long));
	
	time1 = rdtsc();
	for (j = 0; j < numRepeats; j++)
	{
		for(i = 0; i < arrLen; i++)
		{
			arr[i] = j;
		}
	}
	time2 = rdtsc();
	
	free(arr);
	
	overhead = (time2 - time1) - loopOverhead;
	dataSize = ((long long) (arrLen*sizeof(long long))) * numMemAccesses;
	
	return ((long double)dataSize) / ((long double) overhead);
}

long double getMemoryReadBandwith(void)
{
	double arrLenDub = pow(2.0, 18.0);
	int arrLen = (int)arrLenDub;
	
	long long j, ref1, time1, time2, loopOverhead, overhead, dataSize;
	long long numRepeats = 10000;
	
	int i;
	
	//printf("arrLen = %d\n", arrLen);
	//fflush(stdout);
	
	time1 = rdtsc();
	for (j = 0; j < numRepeats; j++)
	{
		//printf("j=%lli,", j);
		for(i = 0; i < arrLen; i++)
		{
			ref1 = j;
		}
	}
	time2 = rdtsc();
	
	//printf("here2\n");
	//fflush(stdout);
	
	loopOverhead = time2 - time1;
	
	int* arr = (int*) malloc(arrLen*sizeof(long long));
	for(i = 0; i < arrLen; i++)
	{
		arr[i] = numRepeats;
	}
	
	time1 = rdtsc();
	for (j = 0; j < numRepeats; j++)
	{
		for(i = 0; i < arrLen; i++)
		{
			ref1 = arr[i];
		}
	}
	time2 = rdtsc();
	
	free(arr);
	
	overhead = (time2 - time1) - loopOverhead;
	dataSize = ((long long) (arrLen*sizeof(long long))) * numMemAccesses;
	
	return ((long double)dataSize) / ((long double) overhead);
}
