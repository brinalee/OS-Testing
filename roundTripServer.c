
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


int main(int argc, char *argv[])
{
        int sockRes = 1;
	int connectRes = 1;
	int bytes_recieved = 1;
	int sockOption = 1;  
        char sendBuffer[50];
	char receiveBuffer[50];       

	struct sockaddr_in serverAddress,clientAddress;    

	if ((sockRes = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "Could not create a socket!\n");
		exit(1);
	}

	if (setsockopt(sockRes,SOL_SOCKET,SO_REUSEADDR,&sockOption,sizeof(int)) == -1) {
		fprintf(stderr, "Could not set socket options!\n");
		exit(1);
	}

	serverAddress.sin_family = AF_INET;         
	serverAddress.sin_port = htons(2154);     
	serverAddress.sin_addr.s_addr = INADDR_ANY; 
	bzero(&(serverAddress.sin_zero),8); 

	if (bind(sockRes, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr)) == -1) {
		fprintf(stderr, "Could not bind to socket!\n");
		exit(1);
	}

	if (listen(sockRes, 5) == -1) {
		fprintf(stderr, "Cannot listen to socket!\n");
		exit(1);
	}
		
	printf("\nWaiting on port 2154 for bounce-back\n");
	fflush(stdout);
	sendBuffer[0] = 'q';
	sendBuffer[1] = '\0';
	int _size = sizeof(struct sockaddr_in);

	connectRes = accept(sockRes, (struct sockaddr *)&clientAddress, (socklen_t*) &_size);

	printf("recieved connection from (%s , %d), commencing bounce-back\n", inet_ntoa(clientAddress.sin_addr),ntohs(clientAddress.sin_port));
	fflush(stdout);

	while (1)
	{
		bytes_recieved = recv(connectRes,receiveBuffer,2,0);
		receiveBuffer[1] = '\0';

		if (receiveBuffer[0] == 'q' || receiveBuffer[0] == 'Q')
		{
			printf("Recieved quit\n");
			fflush(stdout);
			break;
		} else {
			send(connectRes, receiveBuffer, 2, 0);
		}
	}
	
	long bufSize = 1073741824;
	long arrLen = bufSize / ((long) sizeof(char));
	char* bigReceiveBuffer = (char*) malloc(bufSize);

	printf("\nWaiting for a big array\n");
	fflush(stdout);

	bytes_recieved = recv(connectRes,bigReceiveBuffer,arrLen,0);
	send(connectRes, sendBuffer, 2, 0);
	close(connectRes);
	free(bigReceiveBuffer);
	close(sockRes);
	return 0;
} 
