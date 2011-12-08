
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
	char sendBuffer[50];
	char receiveBuffer[50];
	struct hostent *host;
	struct sockaddr_in serverAddress;  

	host = gethostbyname("137.110.161.199");
	// rodney.ucsd.edu: 137.110.161.199
	// cyclo.ucsd.edu: 137.110.161.115

	if ((sockRes = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Could not create a socket!\n");
		exit(1);
	}

	serverAddress.sin_family = AF_INET;     
	serverAddress.sin_port = htons(2154);   
	serverAddress.sin_addr = *((struct in_addr *)host->h_addr);
	bzero(&(serverAddress.sin_zero),8); 

	if (connect(sockRes, (struct sockaddr *)&serverAddress,
                    sizeof(struct sockaddr)) == -1) 
	{
		fprintf(stderr, "Could not connect!\n");
		exit(1);
	}

	long numBouceBacks = 10000;
	long count = 0;
	long long time1, time2 = 0;
	sendBuffer[0] = 'g';
	sendBuffer[1] = '\0';

	time1 = rdtsc();
	for (count = 0; count < numBouceBacks; count++)
	{
		send(sockRes, sendBuffer, 2, 0);
		recv(sockRes, receiveBuffer, 2, 0);
		receiveBuffer[1] = '\0';
        }
	time2 = rdtsc();

	sendBuffer[0] = 'q';
	send(sockRes,sendBuffer,strlen(sendBuffer), 0);
	
	printf("Round-trip time = %.2LF\n", ((long double) (time2 - time1)) / ((long double) numBouceBacks));

	printf("\nSending big array ...\n");
	fflush(stdout);

	long bufSize = 1073741824;
	long arrLen = bufSize / ((long) sizeof(char));
	char* bigSendBuffer = (char*) malloc(bufSize);
	for (long i = 0; i < arrLen-1; i++) {
		bigSendBuffer[i] = 'a';
	}
	bigSendBuffer[arrLen-1] = '\0';

	printf("sending %li a's\n", arrLen-1);

	time1 = rdtsc();
	send(sockRes, bigSendBuffer, arrLen, 0);
	recv(sockRes, receiveBuffer, 2, 0);
	time2 = rdtsc();

	free(bigSendBuffer);
	close(sockRes);
	
	printf("time = %lli\n", time2 - time1);

	long double totalTime = ((long double) bufSize) / ((long double) (time2 - time1));
	printf("Bandwidth = %.2LF GB/sec\n", totalTime * (2.4e9/1.0e9));
	return 0;
}
