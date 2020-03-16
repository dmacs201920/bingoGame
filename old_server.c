
#include"Bingo_Header.h"
int main(int ac, char **ar){
    int welcomeSocket, newSocket;
    struct sockaddr_in serverAddr,serverStorage;
    socklen_t addr_size;
    welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serverAddr,sizeof(struct sockaddr_in));
    bzero(&serverStorage,sizeof(struct sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int array[5][5];
    fill_bingo(array);
    if(bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr))!=0)
    {
	perror("bind");
	exit(1);
    }
	printf("PORT NO : %d\n",ntohs(serverAddr.sin_port));
    if(listen(welcomeSocket,5)==0);
    else{
	printf("\n\nError\n");
	exit(1);
    }
    addr_size = sizeof serverStorage;
    int p1=1;
    data d;
    d.com=0;
    if((newSocket= accept(welcomeSocket, (struct sockaddr *) &serverStorage, &addr_size))<0)
    {
	perror("accept");
	exit(1);
    }
    int i,j;
    for(i=0;i<5;++i)
	for(j=0;j<5;++j)
	    if(write(newSocket,&array[i][j],sizeof(int))!=sizeof(int))
	    {
		close(newSocket);
		close(welcomeSocket);
		exit(1);
	    }
    if((p1=fork())<0)
    {
	printf("\nUnable to fork\n");
	exit(-1);
    }
    while(d.com!='q')
    {
	if(p1==0)
	{
	    if(read(newSocket,&d,sizeof(data))>0)
		printf("\n%c %d\n",d.com,d.num);
	    else
	    {
		close(newSocket);
		perror("read");
		exit(1);
	    }
	}
	else{
	    printf("\nChar,num,bingos,opponent: ");
	    scanf("%c%*c%d%*c%d%*c%d",&d.com,&d.num,&d.bng,&d.opp);
	    getchar();
	    if(write(newSocket,&d,sizeof(data))==sizeof(data));	
	    else
	    {
		close(newSocket);
		perror("write");
		exit(1);
	    }
	}

    }
    close(welcomeSocket);
    close(newSocket);
    return 0;
}

