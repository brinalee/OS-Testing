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
int StartedSwitching;
unsigned long long ContextSwitchCounter;
unsigned long long TestCounter;
pthread_mutex_t StartThreads;
pthread_mutex_t EndThreads;
pthread_mutex_t PrintLock;
pthread_cond_t SwitchThreads;

pthread_mutex_t TestStart;
pthread_mutex_t TestEnd;
pthread_mutex_t TestSwitch;


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
	//unsigned long long time = rdtsc();
	//printf("Child: time=%llu\n", time);
	//unsigned long long* outTime = (unsigned long long*)llu_ptr;
	//*outTime = time;
	return 0;
}

void* thread_switch(void* idt)
{
	pthread_mutex_lock(&StartThreads);
	pthread_mutex_unlock(&StartThreads);
	
	//int* id = (int*) idt;
	
	pthread_mutex_lock(&EndThreads);
	
	if (StartedSwitching)
	{
		pthread_cond_signal(&SwitchThreads);
	}
	while (0 < 1)
	{
		StartedSwitching = 1;
		pthread_cond_wait(&SwitchThreads, &EndThreads);
		++ContextSwitchCounter;
		//printf("%i,", *id);
		//fflush(stdout);
		pthread_cond_signal(&SwitchThreads);
	}
	pthread_mutex_unlock(&EndThreads);
	
	return 0;
}

void* thread_test(void* idt)
{
	//pthread_mutex_lock(&TestEnd);
	pthread_mutex_lock(&TestStart);
	pthread_mutex_unlock(&TestStart);
	
	//int* id = (int*) idt;
	
	//pthread_mutex_lock(&TestEnd);
/*	if (StartedSwitching)
	{
		pthread_cond_signal(&TestSwitch);
	}
*/
	//printf("Starting test\n");
	//fflush(stdout);
	//pthread_mutex_lock(&TestEnd);
	//pthread_cond_signal(&TestSwitch);
	//pthread_mutex_lock(&TestEnd);
	while (TestCounter < ContextSwitchCounter)
	{
		StartedSwitching = 1;
		//printf("test 1\n");
	//fflush(stdout);
		pthread_mutex_lock(&TestSwitch);
		//printf("test 1\n");
	//fflush(stdout);
		++TestCounter;
		//printf("%i,", *id);
		//fflush(stdout);
		pthread_mutex_unlock(&TestSwitch);
	}
	//printf("Done with test, TestCounter=%llu\n", TestCounter);
	//fflush(stdout);
	//pthread_mutex_unlock(&TestEnd);
	
	return 0;
}

long long getThreadContextSwitchOverhead(void)
{
	pthread_t thread1;
	pthread_t thread2;
	pthread_t testThread;
	long long time1, time2, switchTime, loopOverhead;
	
	int id1, id2, id3;
	id1 = 1;
	id2 = 2;
	id3 = 3;
	
	pthread_mutex_init(&StartThreads, NULL);
	pthread_mutex_init(&EndThreads, NULL);
	pthread_cond_init(&SwitchThreads, NULL);
	
	pthread_mutex_lock(&StartThreads);
	
	ContextSwitchCounter = 0;
	StartedSwitching = 0;
	
	pthread_create(&thread1, NULL, thread_switch, (void*) (&id1));
	pthread_create(&thread2, NULL, thread_switch, (void*) (&id2));
	pthread_detach(thread1);
	pthread_detach(thread2);
	
	//pthread_cond_signal(&SwitchThreads);
	//pthread_mutex_unlock(&EndThreads);
	
	//printf("ContextSwitchCounter=%llu\n", ContextSwitchCounter);
	//fflush(stdout);
	
	printf("Context switching for 10 seconds ...\n");
	fflush(stdout);
	
	time1 = rdtsc();
	pthread_mutex_unlock(&StartThreads);
	
	sleep(10);
	
	pthread_mutex_lock(&EndThreads);
	time2 = rdtsc();
	
	//printf("ContextSwitchCounter=%llu\n", ContextSwitchCounter);
	//fflush(stdout);
	
	switchTime = (time2 - time1) / ((long long) ContextSwitchCounter);
	
	//printf("switchTime=%lli\n", switchTime);
	//fflush(stdout);
	
	pthread_mutex_init(&TestStart, NULL);
	pthread_mutex_init(&TestEnd, NULL);
	pthread_mutex_init(&TestSwitch, NULL);
	
	pthread_mutex_lock(&TestStart);
	
	StartedSwitching = 0;
	
	pthread_create(&testThread, NULL, thread_test, (void*) (&id3));
	//pthread_detach(testThread);
	
	//pthread_mutex_unlock(&TestEnd);
	pthread_mutex_unlock(&TestSwitch);
	
	time1 = rdtsc();
	//printf("Signalling test ...\n");
	//fflush(stdout);
	pthread_mutex_unlock(&TestStart);
	pthread_join(testThread, NULL);
	//pthread_mutex_lock(&TestEnd);
	time2 = rdtsc();
	
	loopOverhead = (time2 - time1) / ((long long) ContextSwitchCounter);
	
	//printf("time1=%lli\n", time1);
	//fflush(stdout);
	//printf("time2=%lli\n", time2);
	//fflush(stdout);
	//printf("loopOverhead=%lli, TestCounter=%llu\n", loopOverhead, TestCounter);
	fflush(stdout);
	
	return switchTime - loopOverhead;
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
		//printf("%llu,%llu\n", firstTime, secondTime);
		//fflush(stdout);
		//printf("firstTime = %llu, secondTime = %llu, globalTime = %llu\n", firstTime, secondTime, globalTime);
		//secondTime = (globalTime < secondTime) ? globalTime : secondTime;
		//spanTime = secondTime - firstTime;
	}
	return time2 - time1;
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
	
	int res = 20;
	int step = NUM_COLLECTIONS/res;
	int prog = 0;
	
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
