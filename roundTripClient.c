
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	int sockRes;
	int bytesRecieved;  
	char sendBuffer[50];
	char receiveBuffer[50];
	struct hostent *host;
	struct sockaddr_in serverAddress;  

	host = gethostbyname("137.110.161.199");

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

	long numBouceBacks = 1000;
	long count = 0;
	long long time1, time2 = 0;
	sendBuffer[0] = 'g';
	sendBuffer[1] = '\0';

	for (count = 0; count < numBouceBacks; count++)
	{
		send(sockRes, sendBuffer, 2, 0);
		recv(sockRes, receiveBuffer, 2, 0);
		receiveBuffer[bytesRecieved] = '\0';
 
		if (strcmp(receiveBuffer , "q") == 0 || strcmp(receiveBuffer , "Q") == 0)
		{
			close(sockRes);
			break;
		} else {
			printf("\nRecieved data = %s " , receiveBuffer);
		}

		printf("\nSEND (q or Q to quit) : ");
		gets(sendBuffer);
           
		if (strcmp(sendBuffer , "q") != 0 && strcmp(sendBuffer , "Q") != 0) {
			
		} else {
			send(sockRes,sendBuffer,strlen(sendBuffer), 0);   
			close(sockRes);
			break;
		}
        
        }   
	return 0;
}
