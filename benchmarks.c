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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <math.h>
#include <limits.h>
#include <fcntl.h>

#include "benchmarks.h"
#include "utils.h"

const long long numThreadSwitches = 10000000;
const long long numMemAccesses = 100000000;
const long long numFileAccesses = 100000;

const long long numDirectFileAccesses = 1000;

const int FileBlockSize = 4096;

const char* TestFileName = "test.dat";

const long ContentionFileSize = 67108864;

const char* ContentionFileNames[] = {"test_seq_thread1.dat", "test_seq_thread2.dat", "test_seq_thread3.dat", "test_seq_thread4.dat", "test_seq_thread5.dat", "test_seq_thread6.dat", "test_seq_thread7.dat", "test_seq_thread8.dat", "test_seq_thread9.dat", "test_seq_thread10.dat", "test_seq_thread11.dat", "test_seq_thread12.dat", "test_seq_thread13.dat", "test_seq_thread14.dat", "test_seq_thread15.dat", "test_seq_thread16.dat", "test_seq_thread17.dat", "test_seq_thread18.dat", "test_seq_thread19.dat", "test_seq_thread20.dat", "test_seq_thread21.dat", "test_seq_thread22.dat", "test_seq_thread23.dat", "test_seq_thread24.dat", "test_seq_thread25.dat", "test_seq_thread26.dat", "test_seq_thread27.dat", "test_seq_thread28.dat", "test_seq_thread29.dat", "test_seq_thread30.dat", "test_seq_thread31.dat", "test_seq_thread32.dat", "test_seq_thread33.dat", "test_seq_thread34.dat", "test_seq_thread35.dat", "test_seq_thread36.dat"};
const int MaxNumContendingThreads = 36;

pthread_barrier_t ContentionBarrier;

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

void* thread_read_file(void* voidParams)
{
	ThreadContentionParams* params = (ThreadContentionParams*) voidParams;
	int pageSize = getpagesize();
	long* allData;
	long long time1, time2;

	posix_memalign((void**) &allData, pageSize, ContentionFileSize);
	int fId = open(ContentionFileNames[params->threadID], O_RDONLY | O_DIRECT);

	pthread_barrier_wait(&ContentionBarrier);

	time1 = rdtsc();
	read(fId, allData, ContentionFileSize);
	time2 = rdtsc();
	close(fId); 
	free(allData);

	params->overheadPerBlock = (time2 - time1) / (ContentionFileSize / FileBlockSize);
	
	return 0;
}

long long getFileContentionOverhead(int count)
{
	if (count < 1 || count > MaxNumContendingThreads) {
		printf("ERROR; invalid count %d\n", count);
		return 0;
	}
	
	pthread_t* threads = (pthread_t*) calloc( count, sizeof(pthread_t) );
	pthread_barrier_init(&ContentionBarrier, NULL, count);
	ThreadContentionParams* paramArr = (ThreadContentionParams*) calloc( count, sizeof(ThreadContentionParams) );
	
	for (int i = 0; i < count; i++) {
		paramArr[i].overheadPerBlock = 0;
		paramArr[i].threadID = i;
		pthread_create(&(threads[i]), NULL, thread_read_file, (void*) (&paramArr[i]));
	}

	long long overhead = 0;
	for (int i = 0; i < count; i++) {
		pthread_join(threads[i], NULL);
		overhead += paramArr[i].overheadPerBlock;
	}

	free( threads );
	free( paramArr );
	
	return overhead / ((long long) count);
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
		res = syscall(SYS_gettid);
	}
	time2 = rdtsc();
	
	return ((time2 - time1) / (long long) NUM_COLLECTIONS) - loopOverhead;
}

long double getMemoryLatency(int power, long stride)
{
	double arrLenDub = pow(2.0, (double) power) / ((double) sizeof(long));
	long arrLen = (long)arrLenDub;
	
	long long time1, time2, loopOverhead;
	
	long idx1, idx2, i;
	idx2 = 0;
	
	long offset = 0;
	time1 = rdtsc();
	for(i = 0; i < numMemAccesses; i++)
	{
		offset += 1;
	}
	time2 = rdtsc();
	
	loopOverhead = (time2 - time1) / (numMemAccesses);
	
	//printf("size of long=%d, arr size=%li\n", (int)sizeof(long), arrLen);
	//fflush(stdout);
	
	long* arr = (long*) malloc(arrLen*sizeof(long));
	for(i = 0; i < arrLen; i++)
	{
		arr[i] = -1;
	}
	
	idx2 = 0;
	idx1 = 0;
	long numFill = (long) (0.97 * (double) arrLen);
	if (numMemAccesses < numFill) {
		numFill = numMemAccesses + 1;
	}
	for(i = 0; i < numFill; i++)
	{
		idx2 = (idx1 + stride) % (arrLen-1);
		
		while (arr[idx2] >= 0 && idx2 != idx1) {
			idx2 = (idx2 >= arrLen) ? 1 : idx2 + 1;
		}
		//printf("idx1=%li, idx2=%li\n", idx1, idx2);
		//fflush(stdout);
		
		arr[idx1] = idx2;
		idx1 = idx2;
	}
	
	arr[idx2] = 0;

	time1 = rdtsc();
	for(i = 0; i < numMemAccesses; i++)
	{
		idx2 = arr[idx2];
	}
	time2 = rdtsc();
	free(arr);

	long double latency = (((long double) (time2 - time1)) / ((long double) numMemAccesses)) - (long double) loopOverhead;
	
	return latency;
}

long double getMemoryWriteBandwith(void)
{
	double arrLenDub = pow(2.0, 24.0);
	int arrLen = (int)arrLenDub;
	
	long long j, ref1, time1, time2, loopOverhead, overhead, dataSize;
	long long numRepeats = 20;
	
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
	
	long long* arr = (long long*) malloc(arrLen*sizeof(long long));
	
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
	dataSize = ((long long) (arrLen*sizeof(long long))) * numRepeats;
	
	return ((long double)dataSize) / ((long double) overhead);
}

long double getMemoryReadBandwith(void)
{
	double arrLenDub = pow(2.0, 25.0);
	int arrLen = (int)arrLenDub;
	
	long long j, ref1, time1, time2, loopOverhead, overhead, dataSize;
	long long numRepeats = 20;
	
	int i;
	
	//printf("arrLen = %d\n", arrLen);
	//fflush(stdout);
	
	time1 = rdtsc();
	for (j = 0; j < numRepeats; j++)
	{
		//printf("j=%lli,", j);
		//fflush(stdout);
		for(i = 0; i < arrLen; i++)
		{
			ref1 = j;
		}
	}
	time2 = rdtsc();
	
	//printf("here2\n");
	//fflush(stdout);
	
	loopOverhead = time2 - time1;
	
	long long* arr = (long long*) malloc(arrLen*sizeof(long long));
	for(i = 0; i < arrLen; i++)
	{
		arr[i] = numRepeats;
	}
	
	time1 = rdtsc();
	for (j = 0; j < numRepeats; j++)
	{
		//printf("j=%lli,", j);
		//fflush(stdout);
		for(i = 0; i < arrLen; i++)
		{
			ref1 = arr[i];
		}
	}
	time2 = rdtsc();
	
	free(arr);
	
	overhead = (time2 - time1) - loopOverhead;
	dataSize = ((long long) (arrLen*sizeof(long long))) * numRepeats;
	
	return ((long double)dataSize) / ((long double) overhead);
}

long long getPageFaultOverhead(void)
{
	long long measureOv = (long long)getMeasureOverhead();
	
	double arrLenDub = pow(2.0, 30.0);
	int arrLen = (int)arrLenDub;
	int idx1;
	long long ref1;
	long long time1, time2, locOverhead, totalOverhead, numPageFaults;
	
	long long numPageAccesses = 15000000;
	long long minPageOv = 2000000;
	
	long long stride = 1041553;
	//int stride = 223;
	
	long long j = 0 + stride;
	long long i;
	long long maxInt = INT_MAX - stride - 1;
	long long arrLastIdx = (long long) arrLen - 1;
	
	totalOverhead = 0;
	numPageFaults = 0;
	long long* arr = (long long*) malloc(arrLen*sizeof(long long));
	
	long long numChecks = 100;
	long long step = numPageAccesses / numChecks;
	long long cur = step;
	for (i = 0; i < numPageAccesses; i++)
	{
		if (i >= cur)
		{
			printf("%lli,", cur/step);
			fflush(stdout);
			cur += step;
		}
		j = j % maxInt;
		//idx1 = (int) (i % arrLastIdx);
		idx1 = (int) (j % arrLastIdx);
		
		arr[idx1] = (long long) idx1;
		
		j += stride;
	}
	
	printf("\nDone writing, now reading\n");
	fflush(stdout);
	
	numPageAccesses = numPageAccesses / 10;
	
	ref1 = 0;
	j = 0 + stride;
	cur = step;
	for (i = 0; i < numPageAccesses; i++)
	{
		if (i >= cur)
		{
			printf("%lli,", cur/step);
			fflush(stdout);
			cur += step;
		}
		
		j = j % maxInt;
		//idx1 = (int) (i % arrLastIdx);
		idx1 = (int) (j % arrLastIdx);
		
		time1 = rdtsc();
		ref1 += arr[idx1];
		time2 = rdtsc();
		
		j += stride;
		
		locOverhead = time2 - time1 - measureOv;
		
		if (locOverhead > minPageOv)
		{
			fprintf(stderr, "%lli\n", locOverhead);
			//fflush(stdout);
			//totalOverhead += locOverhead;
			//++numPageFaults;
		}
	}
	
	printf("\nDone reading\n");
	fflush(stdout);
	
	fflush(stderr);
	
	free(arr);
	
	//printf("numPageFaults=%lli\n", numPageFaults);
	
	return 0;
}

long long getCachedIOLatency(long fileSize, long stride)
{
	double arrLenDub = floor(((double) fileSize) / ((double) sizeof(long)));
	long arrLen = (long) (arrLenDub + 0.1);
	
	long long time1, time2, loopOverhead;
	
	long idx1, idx2, i;
	idx2 = 0;
	
	long offset = 0;
	time1 = rdtsc();
	for(i = 0; i < numFileAccesses; i++)
	{
		offset += 1;
	}
	time2 = rdtsc();
	
	loopOverhead = (time2 - time1) / (numFileAccesses);
	
	//printf("size of long=%d, arr size=%li\n", (int)sizeof(long), arrLen);
	//fflush(stdout);
	
	long* arr = (long*) malloc(arrLen*sizeof(long));
	for(i = 0; i < arrLen; i++)
	{
		arr[i] = -1;
	}
	
	idx2 = 0;
	idx1 = 0;
	long numFill = (long) (0.95 * (double) arrLen);
	if (numFileAccesses < numFill) {
		numFill = numFileAccesses + 1;
	}
	for(i = 0; i < numFill; i++)
	{
		idx2 = (idx1 + stride) % (arrLen-1);
		
		while (arr[idx2] >= 0) {
			idx2 = (idx2 >= arrLen) ? 1 : idx2 + 1;
		}
		//printf("idx1=%li, idx2=%li\n", idx1, idx2);
		//fflush(stdout);
		
		arr[idx1] = (idx2) * sizeof(long);
		idx1 = idx2;
	}
	
	arr[idx2] = 0;
	
	//printf("done preloading, now writing\n");
	//fflush(stdout);
	
	
	FILE *fp = fopen(TestFileName, "w");
	fwrite(arr, sizeof(long), arrLen, fp);
	fflush(fp); // flush buffered data to disk
	fclose(fp);
	free(arr);
	
	//printf("done writing\n");
	//fflush(stdout);
	
	offset = 0;
	fp = fopen(TestFileName, "r");
	time1 = rdtsc();
	for(i = 0; i < numFileAccesses; i++)
	{
		//printf("offset=%li\n", offset);
		//fflush(stdout);
		fseek(fp, offset, SEEK_SET);
		fread(&offset, sizeof(long), 1, fp);
	}
	time2 = rdtsc();
	fclose(fp);
	
	return ((time2 - time1) / numFileAccesses) - loopOverhead;
}

double getSequentialFileReadTime(int power, const char* filename, bool create)
{
	double arrLenDub = pow(2.0, (double) power) / ((double) sizeof(long));
	long arrLen = (long)arrLenDub;

	long intsPerBlock = ((long) FileBlockSize) / ((long) sizeof(long));
	if (arrLen < intsPerBlock) {
		arrLen = intsPerBlock;
	} else {
		arrLen = (arrLen / intsPerBlock) * intsPerBlock;
	}
	long numBlocks = arrLen / intsPerBlock;
	long i;
	long long time1, time2;

	long* arr;// = (long*) malloc(FileBlockSize);
	int pageSize = getpagesize();
	posix_memalign((void**) &arr, pageSize, FileBlockSize);

	for (i = 0; i < intsPerBlock; i++) {
		arr[i] = 1;
	}

	//printf("loopOverhead=%lli\n", loopOverhead);
	//fflush(stdout);
	int fId;
	if (create) {
		fId = open(filename, O_WRONLY | O_DIRECT | O_CREAT);
		for (i = 0; i < numBlocks; i++) {
			arr[0] = (i+1) * FileBlockSize;
			if (i == numBlocks - 1) {
				arr[0] = 0;
			}
			write(fId, arr, FileBlockSize);
		}
		close(fId);
	}
	//printf("now reading\n");
	//fflush(stdout);

	free(arr);
	long* allData;
	posix_memalign((void**) &allData, pageSize, FileBlockSize*numBlocks);
	time1 = rdtsc();
	memset(allData, 0, FileBlockSize*numBlocks);
	time2 = rdtsc();
	long long loopOverhead = (time2 - time1) / (numBlocks);
	
	fId = open(filename, O_RDONLY | O_DIRECT);
	arr[0] = 0;
	time1 = rdtsc();
	read(fId, allData, FileBlockSize*numBlocks);
	time2 = rdtsc();
	//printf("access time = %lli\n", (time2-time1) / numDirectFileAccesses);
	close(fId); 
	free(allData);
	

	long long totalTime = ((time2 - time1) / numBlocks) - loopOverhead;
	//printf("totalTime=%lli\n", totalTime);
	//fflush(stdout);
	long double totalTimeDouble = (long double) totalTime;
	return (double) (log(totalTimeDouble) / log((long double) 2.0));
}

double getRandomFileReadTime(int power, const char* filename, bool create)
{
	double arrLenDub = pow(2.0, (double) power) / ((double) sizeof(long));
	long arrLen = (long)arrLenDub;

	long intsPerBlock = ((long) FileBlockSize) / ((long) sizeof(long));
	if (arrLen < intsPerBlock) {
		arrLen = intsPerBlock;
	} else {
		arrLen = (arrLen / intsPerBlock) * intsPerBlock;
	}
	long numBlocks = arrLen / intsPerBlock;
	long i, j, idx1, idx2;
	long long time1, time2, loopOverhead;

	long* arr;// = (long*) malloc(FileBlockSize);
	int pageSize = getpagesize();
	posix_memalign((void**) &arr, pageSize, FileBlockSize);
		
	time1 = rdtsc();
	for(j = 0; j < numDirectFileAccesses; j++)
	{
		memset(arr, 0, FileBlockSize);
	}
	time2 = rdtsc();
	loopOverhead = (time2 - time1) / (numDirectFileAccesses);

	for (i = 0; i < intsPerBlock; i++) {
		arr[i] = 1;
	}
	int fId;

	if (create) {
		int randMax = RAND_MAX;
		int maxRep = 50;
		double frac;
		long* arrRef = (long*) malloc(numBlocks*sizeof(long));
		for(i = 0; i < numBlocks; i++)
		{
			arrRef[i] = -1;
		}
	
		idx2 = 0;
		idx1 = 0;
		int rep = 0;
		for(i = 0; i < numBlocks; i++)
		{
			frac = (double) rand() / (double) randMax;
			idx2 = (long) (frac * ((double) numBlocks - 1));
			while (rep < maxRep)
			{
				if (arrRef[idx2] < 0 && idx2 != idx1)
				{
					arrRef[idx1] = idx2;
					idx1 = idx2;
					break;
				} else
				{
					rep ++;
					frac = (double) rand() / (double) randMax;
					idx2 = (long) (frac * ((double) numBlocks - 1));
				}
			}
			if (rep >= maxRep)
			{
				break;
			}
			rep = 0;
		}
	
		arrRef[idx2] = 0;

		fId = open(filename, O_WRONLY | O_DIRECT | O_CREAT);
		for (i = 0; i < numBlocks; i++) {
			arr[0] = (arrRef[i] < 0) ? 0 : arrRef[i] * FileBlockSize;
			write(fId, arr, FileBlockSize);
		}
		close(fId);
		free(arrRef);
	}
	//printf("now reading\n");
	//fflush(stdout);

	fId = open(filename, O_RDONLY | O_DIRECT);
	arr[0] = 0;
	time1 = rdtsc();
	for(i = 0; i < numDirectFileAccesses; i++)
	{
		lseek(fId, arr[0], SEEK_SET);
		read(fId, arr, FileBlockSize);
	}
	time2 = rdtsc();
	//printf("access time = %lli\n", (time2-time1) / numDirectFileAccesses);
	close(fId); 
	free(arr);

	long long totalTime = ((time2 - time1) / numDirectFileAccesses) - loopOverhead;
	//printf("totalTime=%lli\n", totalTime);
	//fflush(stdout);
	long double totalTimeDouble = (long double) totalTime;
	return (double) (log(totalTimeDouble) / log((long double) 2.0));
}
