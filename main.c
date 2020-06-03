
#include<winsock2.h>
#include <ws2tcpip.h>
//#include <wininet.h>

#include <libgen.h>
#include <unistd.h>

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "helper.h"
#include "receiver.h"
#include "sender.h"


#pragma comment(lib,"ws2_32.lib") //Winsock Library

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	
	int choice;
	char ipAddress[MAX_IP];
	char path[MAX_PATHLEN];
	
	
	
	do{
	WSAInit();
	
	printf("----------------------------------------------------\n");
	printf("		Welcome to File Transer	System				\n");	
	printf("----------------------------------------------------\n");
	printf("Enter Your Choice (1-3):\n");
	printf("--> 1. Receive File\n");
	printf("--> 2. Send File\n");
	printf("--> 3. Exit \n");
	printf("Your Choice : ");
	scanf("%d" , &choice);
	
	switch(choice)
	{
		case 1: 	printMySystemInfo();
					printf("\nEnter your IP Address : ");
					scanf(" %s",ipAddress);		
					// printf("%s ",ipAddress);
					
		// Call Receiver Function here
					bindSocket(ipAddress);
					WSACleanup();
					break;
		case 2:
				printf("\nEnter Receiver IP Address : ");
				scanf(" %s",ipAddress);		
				printf("\nEnter the  File Path :  ");
				scanf(" %s",path);

	
//				printf("%s  %s ",ipAddress,basename(path));
//			Call Sender function here			
					validateInput(ipAddress,path);		
					WSACleanup();
					break;
		case 3:		WSACleanup();
					
					return 0;
					break;
		default :
					 
					printf("\n Please Enter valid choice");
					break;
		
	}
	
	printf("\nPress Any Key to continue ->\n");
	getch();
	
}while(1);
//	printf("%s  %s %d",ipAddress,basename(path),choice);
		
	
	
	return 0;
}
