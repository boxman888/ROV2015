/********************************************************************
*			ROV TEAM 2016
*		LINN-BENTON COMMUNITY COLLEGE
*		  client code for ROV server
* Created by Ethan Patterson <January 26 2016>
* Last modified by Ethan Patterson (April 10th 2016)
*
*	To compile with pthread.h add ext -pthread
********************************************************************/

#include <stdio.h>
#include <pthread.h>
#include "socket.h"

#define packetSize 256

FILE file(struct toolbox *toolBox,char ch, char *buff);//where the action happens 
void *controller(void *myvar);
void *lin_math(void *myvar);

char ch = ' ';

int main (void)
{
	//pthread_t thread1, thread2;//creats a thread 
	//int ret1 = 0, ret2 = 0;//return value for thread 
	char buffer[packetSize];//ch for characters and buffer to store them 
	struct toolbox toolBox;//use the toolbox struct from socket.h
	
	//ret1 = pthread_create(&thread1,NULL,controller,NULL);//gives function to the tread
	//ret2 = pthread_create(&thread2,NULL,lin_math,NULL); 
	//if (ret1 == 1 || ret2 == 1)
		//printf("ERROR: creating pthread");
		
	while (buffer[0] != '#')
	while (1)
		file(&toolBox,ch,buffer);
		
	//pthread_join(thread1,NULL);
	//pthread_join(thread2,NULL);

	return 0;
}

FILE file(struct toolbox *toolBox, char ch, char *buff)//writes to a file 
{
	toolBox-> fi = fopen("Regionals_old.txt","r");
	if (toolBox->fi == NULL)
	{
		perror("ERROR while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	
	while (!feof(toolBox->fi))
	{
		fgets(buff, packetSize,toolBox->fi);
		packet(buff);//packet is defined in socket.h
		//usleep(10000);
	}	
	fclose(toolBox->fi);	
}

void *controller(void *myvar)//runs the controler program 
{	
	int ret = 0;

	ret = system("python ControllerInterface.py");
	if (ret != 0)
	{
		printf("ERROR: in controller\n");
		printf("\nTry Pluging in a Controller\n\n");
	}
	ch = '#';

	return NULL;
}
void *lin_math(void *myvar)
{
	int ret = 0;

	ret = system("./joymap");
	if (ret != 0)
		printf("ERROR: joymap failed");

	ch = '#';

	return NULL;
}
