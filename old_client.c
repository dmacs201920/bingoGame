#include"header.c"
int main(int ac,char **ar){
    int clientSocket;
    char buffer[1024]=" ";
    struct sockaddr_in serverAddr;
    socklen_t addr_size;

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;

    serverAddr.sin_port = htons(7891);

    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  


    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);


    int i,pid;
    if((pid=fork())<0)
    {
	printf("\nFork error\n");
	exit(0);
    }
    while(buffer[0]!='~'){
	if(pid==0)
	{    
	    fgets(buffer,1024,stdin);
	    strcat(buffer,ar[1]);
	    send(clientSocket,buffer,100,0);	
	}
	else{
	    i=recv(clientSocket, buffer, 1024, 0);
	    if(i>0)
		printf("\n%s\n",buffer);
	    sleep(t);
	}
    }
    close(clientSocket);

    return 0;
}
