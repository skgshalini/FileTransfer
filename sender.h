void sendFileName(char path[], int sockfd);

void sendfile(char path[], int sockfd , ssize_t total);

int sender(char receiver_ip[], char path[])
{
   
   
   	// WSADATA wsaData;
	int sockfd;
    ssize_t total=0;

    sockfd  = iniSocket();

    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(SERVERPORT);
    serveraddr.sin_addr.s_addr = inet_addr(receiver_ip);

    if (connect(sockfd, (const struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0)
    {
        perror("\n Connection Error ");
        WSACleanup();
        getch();
        exit(1);
    }
    
    printf("\n Connection Request Sent............");
    
    sendFileName(path,sockfd);

    sendfile(path, sockfd ,total);
    //puts("Send Success");
    
    close(sockfd);
    //  WSACleanup();
    // getch();
    return 0;
}

void sendFileName(char path[], int sockfd)
{

	char* filename;
    char buff[BUFFSIZE] = {0};

    filename = (char *)basename(path); 
    if (filename == NULL)
    {
        perror("\n Can't get filename");
        WSACleanup();
        getch();
        exit(1);
    }
    
    strncpy(buff, filename, strlen(filename));
    if (send(sockfd, buff, BUFFSIZE, 0) == -1)
    {
        perror("\n Can't send filename");
        WSACleanup();
        getch();
        exit(1);
    }
    
    printf("\n File Name Sent ............");
    




}


void sendfile(char path[], int sockfd ,ssize_t total) 
{
    int n; 
    char sendline[MAX_LINE] = {0};

    
    FILE *fp = fopen(path, "rb");
    if (fp == NULL) 
    {
        perror("\n Can't open file");
        WSACleanup();
        getch();
        exit(1);
    }

    while ((n = fread(sendline, sizeof(char), MAX_LINE, fp)) > 0) 
    {
	    total+=n;
        if (n != MAX_LINE && ferror(fp))
        {
            perror("\n Read File Error");
            WSACleanup();
            getch();
            exit(1);
        }
        
        if (send(sockfd, sendline, n, 0) == -1)
        {
            perror("\n Can't send file");
            WSACleanup();
            getch();
            exit(1);
        }
        printf("\n  %ld Byte sent ",total);
        memset(sendline, 0, MAX_LINE);
        
    }

    fclose(fp);
    printf("\n Send Success, Number of Bytes Sent= %ld\n", total);
}
