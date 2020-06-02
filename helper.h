void checkHostName(int hostname) ;
void checkHostEntry(struct hostent * hostentry) ;
void checkIPbuffer(char *IPbuffer) ;
int iniSocket();
int WSAInit()
{
        WSADATA wsaData;
        int iResult;
    // Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
		if (iResult != 0) {
    		printf("\nWSAStartup failed: %d\n", iResult);
    	return 1;
		}
	
}


int iniSocket()
{
 int sockfd;
 
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) 
    {
        perror("\nCan't allocate sockfd");
        WSACleanup();
        getch();
        exit(1);
    }
    printf("\nSocket Initialized............");
    return sockfd;
}


void printMySystemInfo()
{
	char hostbuffer[256]; 
    char *IPbuffer; 
    struct hostent *host_entry; 
    int hostname; 
  
    // To retrieve hostname 
    hostname = gethostname(hostbuffer, sizeof(hostbuffer)); 
    checkHostName(hostname); 
  
    // To retrieve host information 
    host_entry = gethostbyname(hostbuffer); 
    checkHostEntry(host_entry); 
  
    // To convert an Internet network 
    // address into ASCII string 
    IPbuffer = inet_ntoa(*((struct in_addr*) 
                           host_entry->h_addr_list[0])); 
  
    printf("\n Your Hostname: %s\n", hostbuffer); 
    printf("\n Your Host IP: %s \n", IPbuffer); 
	printf("\n Or use ipconfig command to check IP \n");
}

void checkHostName(int hostname) 
{ 
    if (hostname == -1) 
    { 
        perror("\ngethostname"); 
        exit(1); 
    } 
} 
  
// Returns host information corresponding to host name 
void checkHostEntry(struct hostent * hostentry) 
{ 
    if (hostentry == NULL) 
    { 
        perror("\ngethostbyname"); 
        exit(1); 
    } 
} 
  
// Converts space-delimited IPv4 addresses 
// to dotted-decimal format 
void checkIPbuffer(char *IPbuffer) 
{ 
    if (NULL == IPbuffer) 
    { 
        perror("\ninet_ntoa"); 
        exit(1); 
    } 
}