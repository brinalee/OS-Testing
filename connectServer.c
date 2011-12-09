
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
	int sockOption = 1;
	char sendBuffer[50];

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
	serverAddress.sin_port = htons(2155);     
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
		
	printf("\nWaiting on port 2155 for bounce-back\n");
	fflush(stdout);
	int _size = sizeof(struct sockaddr_in);
	sendBuffer[0] = 'q';
	sendBuffer[1] = '\0';
	while (1)
	{
		connectRes = accept(sockRes, (struct sockaddr *)&clientAddress, (socklen_t*) &_size);
	}

	//close(connectRes);
	//close(sockRes);
	return 0;
} 
