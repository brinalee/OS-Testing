
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "utils.h"

int main(int argc, char *argv[])
{
	int sockRes;
	struct hostent *host;
	//char sendBuffer[50];
	struct sockaddr_in serverAddress;  

	host = gethostbyname("137.110.161.199");
	// rodney.ucsd.edu: 137.110.161.199
	// cyclo.ucsd.edu: 137.110.161.115



	long numBouceBacks = 1000000;
	long long connectTime = 0;
	long long teardownTime = 0;
	long long time1, time2;

	for (long i = 0; i < numBouceBacks; i++) {
		time1 = rdtsc();
		if ((sockRes = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			fprintf(stderr, "Could not create a socket!\n");
			exit(1);
		}

		serverAddress.sin_family = AF_INET;     
		serverAddress.sin_port = htons(2155);   
		serverAddress.sin_addr = *((struct in_addr *)host->h_addr);
		bzero(&(serverAddress.sin_zero),8); 
		connect(sockRes, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr));
		time2 = rdtsc();
		connectTime += time2 - time1;

		time1 = rdtsc();
		close(sockRes);
		time2 = rdtsc();
		teardownTime += time2 - time1;
	}

	close(sockRes);
	

	long double overheadC = ((long double) connectTime) / ((long double) numBouceBacks);
	long double overheadT = ((long double) teardownTime) / ((long double) numBouceBacks);
	
	printf("Setup latency = %.2LF ns\n", overheadC / (2.4));
	printf("Tear-down latency = %.2LF ns\n", overheadT / (2.4));
	return 0;
}
