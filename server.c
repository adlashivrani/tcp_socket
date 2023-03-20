#include "header.h"

int main()
{
	pid_t id;
	int res;
	int len;
	int bin;
	char buff[SIZE]; //creating buffer
	char BUF[SIZE];
	int sfd;//file descriptor for server
	int cfd; //file descriptor for client
	struct sockaddr_in server; //calling the structure for server
 	struct sockaddr_in client;//calling structure for client
	server.sin_family = AF_UNIX;
	server.sin_port = htons(_PORT_);
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_zero[8] = '\0';

	//creating server socket file descriptor
	if ((sfd = socket(AF_UNIX, SOCK_STREAM,0)) == -1) {
		printf("\nSERVER SOCKET FD NOT CREATED\n");
		exit(1);//socket not created
	}
	//binding
	if((bin = bind(sfd,(struct sockaddr*)&server, sizeof(server))) == -1) { //to bind end to the socket
		printf("\n SOCKET NOT BINDED\n");
		exit(1);	
	}
	
	//listening
	if ((res = listen(sfd, 5)) == -1) {
		printf("\nERROR IN LISTENING>>\n");
		exit(1);
	}
	len = sizeof(client);	
	while (1) {	
	// creating client file descriptor
		if ((cfd = accept(sfd, (struct sockaddr *)&client,&len)) == -1 ) {
			printf("\n NOT ACCEPTED CLIENT REQUEST\n");
			exit(1);
		}
		if ( (id = fork()) == 0) { //child process created
			read(cfd, buff,SIZE); //reading from the client file descriptor
			printf("%s\n", buff);
			printf("\nWrite a message to the client!\n");
			fgets(BUF, SIZE, stdin);
			write(cfd, BUF, SIZE); //writing to the client file descriptor
			close(cfd);
	}
	}
	close(sfd);
	return 0;
}	
