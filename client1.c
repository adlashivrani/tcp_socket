#include "header.h"

int main()
{
    char buff[SIZE]; //creating buffer
	char BUF[SIZE];
   	int cfd; //file descriptor for client
	
    struct sockaddr_in client;//calling structure for client   
    client.sin_family = AF_UNIX;
    client.sin_port = htons(_PORT_);
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_zero[8] = '\0';
	
    //creating server socket file descriptor
    if ((cfd = socket(AF_UNIX, SOCK_STREAM,0)) == -1) {
		printf("\nCLIENT SOCKET FD NOT CREATED\n");
    	exit(1);//socket not created
    }
  	
	if ((connect(cfd, (struct sockaddr*)&client, sizeof(client))) == -1) {
		printf("\nNOT CONNECTED TO THE SERVER!\n");
		exit(1);
	}
	printf("\nWrite a message to server from client1\n");
	fgets(BUF, SIZE, stdin);
	write(cfd,BUF, SIZE); // writing to the server file descriptor
    read(cfd, buff, SIZE); //reading from the client file descriptor
    printf("%s\n", buff);
    close(cfd);
   	
    return 0;
}
 
