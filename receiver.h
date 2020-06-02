FILE *fileNameRec(int connfd, char filename[]);
void writefile(int sockfd, FILE *fp,char filename[],char client[], ssize_t totalRec);

int receive(char receiver_ip[]) 
{
    ssize_t totalRec=0;
	// WSADATA wsaData;
	int sockfd ,c;
    struct sockaddr_in clientaddr, serveraddr;
    char filename[BUFFSIZE] = {0}; 
    FILE *fp;
    //Init WinSock
    sockfd  = iniSocket();
    
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(receiver_ip);
    serveraddr.sin_port = htons(SERVERPORT);
//    memset(&serveraddr, 0, sizeof(ServAddr));

    if (bind(sockfd, (const struct sockaddr *) &serveraddr, sizeof(serveraddr)) == -1) 
    {
        perror("\n Bind Error");
        WSACleanup();
        getch();
        exit(1);
    }
    printf("\n Binding IP and Port............");

    if (listen(sockfd, LINSTENPORT) == -1) 
    {
        perror("\n Listen Error");
        WSACleanup();
        getch();
        exit(1);
    }
    printf("\n Receiver Started Listening at PORT  %d............",SERVERPORT);

    c = sizeof(struct sockaddr_in);
    int connfd = accept(sockfd, (struct sockaddr *) &clientaddr, &c);
    if (connfd == -1) 
    {
        perror("\n Connect Error");
        WSACleanup();
        getch();
        exit(1);
    }
    close(sockfd); 

    printf("\n Waiting For sender..............");
    printf("\n Connection Accepted from Host : %s" ,inet_ntoa(clientaddr.sin_addr));


    fp = fileNameRec(connfd,filename);
    printf("\n File name Received : %s" ,filename);

    printf("\n  I am Started Receiving file: %s from %s\n ", filename,inet_ntoa(clientaddr.sin_addr) );
    writefile(connfd, fp , filename, inet_ntoa(clientaddr.sin_addr),totalRec);
    

    fclose(fp);
    close(connfd);
    // WSACleanup();
    // getch();
    return 0;
}

FILE *fileNameRec(int connfd, char filename[])
{
     FILE *fp;
    if (recv(connfd, filename, BUFFSIZE, 0) == -1) 
    {
        perror("\n Can't receive filename");
        WSACleanup();
        getch();
        exit(1);
    }
    fp = fopen(filename, "wb");
    if (fp == NULL) 
    {
        perror("\n Can't open file");
        WSACleanup();
        getch();
        exit(1);
    }

    return fp;
}



void writefile(int sockfd, FILE *fp , char filename[], char client[] ,ssize_t totalRec)
{
    ssize_t n;
    char buff[MAX_LINE] = {0};
    while ((n = recv(sockfd, buff, MAX_LINE, 0)) > 0) 
    {
        printf("\n Receiving  %d bytes file: %s from %s- -------\n ",totalRec, filename,client );

	    totalRec+=n;
        if (n == -1)
        {
            perror("\n Receive File Error");
            exit(1);
        }
        
        if (fwrite(buff, sizeof(char), n, fp) != n)
        {
            perror("\n Write File Error");
            exit(1);
        }

        memset(buff, 0, MAX_LINE);
    }

    printf("\n Receive Success, NumBytes = %ld\n ", totalRec);
    printf("\n File Received Successfully and Stored as: %s \n", filename);

}
