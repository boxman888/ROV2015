/********************************************************************
* Created by Ethan Patterson 
*
* Used to write basic sockets, NOT USED TO READ SOCKETS 
* Created for use with clientROV.c 
* Will need some trimming for use with other programms
*
*********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

const int PORT = 8888;
const char IP[14] = "192.168.1.177";

struct toolbox//holds tools for sockets 
{
	FILE *fi;
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;	
};

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

char packet(char *buffer)
{
	struct toolbox toolBox;
	
	toolBox.portno = PORT;
	toolBox.sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (toolBox.sockfd < 0)
		error("\nERROR opeing socket\n");

	toolBox.server = gethostbyname(IP);	
	if(toolBox.server == NULL)
	{
		fprintf(stderr,"\nERROR, not such host\n");
		exit(0);
	}

	bzero((char*) &toolBox.serv_addr, sizeof(toolBox.serv_addr));
	toolBox.serv_addr.sin_family = AF_INET;
	bcopy((char *) toolBox.server->h_addr,
		(char*)&toolBox.serv_addr.sin_addr.s_addr,
		toolBox.server->h_length);
	toolBox.serv_addr.sin_port= htons(toolBox.portno);
	
	if(connect(toolBox.sockfd,(struct sockaddr *) &toolBox.serv_addr,
		sizeof(toolBox.serv_addr)) < 0)
		error("ERROR connecting\n");
	toolBox.n = write(toolBox.sockfd, buffer,strlen(buffer));
	if (toolBox.n < 0)
		error("\nERROR writing to socket\n");
	usleep(4600);//pauses
	bzero(buffer,256);
	if (toolBox.n < 0)
		error("\nERROR reading from socket\n");
	close(toolBox.sockfd);
}//packet end 

