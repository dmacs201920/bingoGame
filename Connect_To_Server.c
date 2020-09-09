#include"Bingo_Header.h"
extern int end_game_flag;

/*
   FUNCTION TO HELP CLIENT CONNECT TO THE SERVER
   USED IN THE CLIENT SIDE OF THE PROGRAM
 */   

void connect_to_server(char **err)
{
    /********************************************************  INITIALIZATIONS  ***************************************************************/
    *err=NULL;
    end_game_flag=0;
    int adl = sizeof(struct sockaddr_in),port_no,i,j;


    struct sockaddr_in ad;
    //int port;
    game_p par;

    curs_set(1);
    cbreak();

    bzero(&ad,sizeof(ad));
    ad.sin_family=AF_INET;
    ad.sin_addr.s_addr=inet_addr(MY_ADDR);

    /*****************************************************************************************************************************************/


    WINDOW *ser_det = newwin(20,50,6,50);			//CREATING WINDOW
    if(ser_det==NULL)
    {
	*err = "ser_det window error";
	delwin(ser_det);
	clear();
	refresh();
	return;

    }
    wattron(ser_det,COLOR_PAIR(1));
    box(ser_det,0,0);
    wattroff(ser_det,COLOR_PAIR(1));


    if((par.sersd = socket(AF_INET,SOCK_STREAM,0))==-1)		//INITIALISING THE SOCKET DESCRIPTOR FOR THE SERVER SIDE
    {
	*err = "Socket create error";
	delwin(ser_det);
	clear();
	refresh();
	return;
    }

    echo();							//PRINTS THE USER KEYBOARD INPUT ON SCREEN

    while(1)
    {
	/******************************************  GETTING USER INPUT FOR PORT NUMBER  *********************************************************/
	mvwprintw(ser_det,2,2,"USE ONLY BACKSPACE AND DIGITS!");
	mvwprintw(ser_det,4,2,"ENTER PORT NUMBER(PRESS -1 TO EXIT):");

	refresh();
	wrefresh(ser_det);
	mvwprintw(ser_det,6,5,"         ");
	mvwscanw(ser_det,6,5,"%d",&port_no);

	if(port_no == -1)
	{
	    noecho();
	    curs_set(0);
	    delwin(ser_det);
	    close(par.sersd);
	    clear();
	    refresh();
	    return;
	}
	/*****************************************************************************************************************************************/
	ad.sin_port=htons(port_no);   				//SETTING THE PORT NUMBER


	if((connect(par.sersd,ADCAST &ad,adl))!=0)		//TRYING TO CONNECT TO THE SERVER
	{
	    wattron(ser_det,COLOR_PAIR(4));
	    mvwprintw(ser_det,15,2,"UNABLE TO CONNECT TO SERVER!!!");
	    mvwprintw(ser_det,16,2,"PLEASE TRY AGAIN");
	    wattroff(ser_det,COLOR_PAIR(4));
	    continue;
	}

	break;
    }		//while close

    noecho();								//DISABLES ECHO

    delwin(ser_det);							//DELETING THE WINDOW
    clear();
    refresh();

    curs_set(0);							//CURSER HIDING FROM SCREEN


    /***********************************************  RECIEVING THE BINGO GAME PLAY ARRAY FROM THE SERVER  ******************************************/
    for(i=0;i<5;++i)
    {
	for(j=0;j<5;++j)
	{
	    if(timed_recv(par.sersd,&par.get.array[i][j],sizeof(int),0,2)!=sizeof(int))
	    {
		close(par.sersd);
		*err = "Array recieve error";
		return;
	    }

	}

    }

    /*****************************************************************************************************************************************/

    par.get.x = par.get.y = par.get.p =  par.get.q = 0;
    pthread_mutex_init(&par.get.get_m,NULL);			//MUTEX VARIABLE INITIALIZATIONS
    pthread_mutex_init(&par.get.done_mutex,NULL);
    pthread_cond_init(&par.get.done,NULL);			//CONDITION VARIABLE INITIALIZATION

    //BINGO IS FOR DISPLAYING THE ARRAY NUMBERS
    //PLAYCHANCE FOR DISPLAYING WHO'S CHANCE IT IS
    //BINGOCNT IS FOR DISPLAYING THE THE NUMBER OF ROWS,COLS AND DIAGONALS COMPLETED

    if((*err=mkbingo(&par))!=NULL)
    {
    	close(par.sersd);
    	return;
    }


    /*****************************************************************************************************************************************/

    if(pthread_create(&par.getid,NULL,get_key_t,&par.get)!=0)			//STARTING THE GET KEY THREAD FUNCTION
    	*err="Unable to create Get Key thread";
    else if(pthread_create(&par.get.gameid,NULL,client_game_t,&par)!=0)		//STARTING THE CLIENT GAME THREAD FUNCTION
    	*err="Unable to create Game thread";
    else
    {
    	 while(end_game_flag==0)							//WAITS FOR THE END GAME FLAG TO CHANGE
		sleep(0.2);

    	if(end_game_flag>0)
		pthread_join(par.get.gameid,(void**)err);				//RECIEVING ERROR MESSAGE FROM CLIENT GAME THREAD FUNCTION
    }
   	pthread_cancel(par.getid);
   	pthread_cancel(par.get.gameid);
   	close(par.sersd);

	for(i=0;i<5;++i)
	    for(j=0;j<5;++j)
	    {
		delwin(par.get.bingo[i][j]);
		del_panel(par.pan[i][j]);
	    }
	del_panel(par.chancepan);
	delwin(par.playchance);
	del_panel(par.bingcnt);
	delwin(par.bingocnt);
	return;
}
