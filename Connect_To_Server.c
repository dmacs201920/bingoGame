#include"Bingo_Header.h"
extern int end_game_flag;

void connect_to_server(char **err)
{
    *err=NULL;
    end_game_flag=0;
    pthread_t gamet,getkeyt;
    int adl = sizeof(struct sockaddr);
    int port_no;
    
    struct sockaddr_in ad;
    //int port;
    game_p par;

    

    curs_set(1);
    cbreak();
    WINDOW *ser_det = newwin(20,50,6,50);
    box(ser_det,0,0);
	echo();
	while(1)
	{
    mvwprintw(ser_det,2,2,"USE ONLY BACKSPACE AND DIGITS!");
    mvwprintw(ser_det,4,2,"ENTER PORT NUMBER(PRESS -1 TO EXIT):");

    refresh();
    wrefresh(ser_det);
    wscanw(ser_det,"%d",&port_no);

if(port_no == -1)
{
    noecho();
    delwin(ser_det);
    clear();
    refresh();
    return;
}
    bzero(&ad,sizeof(ad));

    par.sersd = socket(AF_INET,SOCK_STREAM,0);
    ad.sin_family=AF_INET;
    //port=get_port_num();
    ad.sin_port=htons(port_no);
    ad.sin_addr.s_addr=inet_addr(MY_ADDR);
    if((connect(par.sersd,ADCAST&ad,adl))!=0)
    {
	wattron(ser_det,COLOR_PAIR(4));
    mvwprintw(ser_det,15,2,"UNABLE TO CONNECT TO SERVER!!!");
	wattroff(ser_det,COLOR_PAIR(4));
	continue;
    }
    break;
	}
    noecho();

    delwin(ser_det);
    clear();
    refresh();
    
    curs_set(0);
    int startx = 7,starty = 60,row,col;

    

   for(int i=0;i<5;++i)
    {
	for(int j=0;j<5;++j)
	{
    	if(timed_recv(par.sersd,&par.get.array[i][j],sizeof(int),0,2)!=sizeof(int))
//	if(read(par.sersd,&par.get.array,sizeof(par.get.array)!=sizeof(par.get.array)))
	    {
		close(par.sersd);
		*err = "Array recieve error";
		return;
	    }

	}

    }
 
    par.get.x = par.get.y = par.get.p =  par.get.q = 0;
    pthread_mutex_init(&par.get.get_m,NULL);
    pthread_mutex_init(&par.get.done_mutex,NULL);
    pthread_cond_init(&par.get.done,NULL);

    //BINGO IS FOR DISPLAYING THE ARRAY NUMBERS
    //PLAYCHANCE FOR DISPLAYING WHO'S CHANCE IT IS
    //BINGOCNT IS FOR DISPLAYING THE THE NUMBER OF ROWS,COLS AND DIAGONALS COMPLETED



    par.playchance = newwin(3,120,3,starty);		//CREATES THE WINDOW AND RETURNS A POINTER TO THE PLAYCHANCE
    if(par.playchance==NULL)				
    {
	*err="Unable to create WINDOW";				//ERROR MSG
	//	pthread_mutex_destoy(&par.get.get_m);
	//	pthread_mutex_destoy(&par.get.done_mutex);
	//	pthread_cond_destoy(&par.get.done);
	return;
    }

    par.chancepan = new_panel(par.playchance);			//CREATES THE PANEL AND RETURN THE POINTER TO CHANCEPAN
    if(par.chancepan==NULL)				
    {
	delwin(par.playchance);
	//	pthread_mutex_destoy(&par.get.get_m);
	//	pthread_mutex_destoy(&par.get.done_mutex);
	//	pthread_cond_destoy(&par.get.done);
	*err="Unable to create PANEL";				//ERROR MSG
	return;
    }

    par.bingocnt = newwin(60,3,startx+2,starty-5);
    if(par.bingocnt==NULL)				
    {
	del_panel(par.chancepan);
	delwin(par.playchance);

	*err="Unable to create WINDOW";				//ERROR MSG
	//	pthread_mutex_destoy(&par.get.get_m);
	//	pthread_mutex_destoy(&par.get.done_mutex);
	//	pthread_cond_destoy(&par.get.done);
	return;
    }

    par.bingcnt = new_panel(par.bingocnt);
    if(par.bingcnt==NULL)				
    {
	del_panel(par.chancepan);
	delwin(par.playchance);

	delwin(par.bingocnt);
	*err="Unable to create PANEL";				//ERROR MSG
	//	pthread_mutex_destoy(&par.get.get_m);
	//	pthread_mutex_destoy(&par.get.done_mutex);
	//	pthread_cond_destoy(&par.get.done);
	return;
    }

    ////////////////////////////////////////////////////		CREATING BINGO WINDOWS AND PANELS    

    int i,j,t1,t2;

    for(i=0;i<5;i++)
    {
	for(j=0;j<5;j++)
	{


	    par.get.bingo[i][j] = newwin(width,length,startx,starty);
	    if(par.get.bingo[i][j]==NULL)
	    {
		del_panel(par.chancepan);
		delwin(par.playchance);

		del_panel(par.bingcnt);
		delwin(par.bingocnt);

		for(t1=0;t1<=i;++t1)
		    for(t2=0;t2<5;++t2)
		    {
			if(t1==i&&t2==j)
			    break;
			delwin(par.get.bingo[t1][t2]);
		    }
		*err="Unable to create WINDOW";				//ERROR MSG
		//	pthread_mutex_destoy(&par.get.get_m);
		//	pthread_mutex_destoy(&par.get.done_mutex);
		//	pthread_cond_destoy(&par.get.done);
		return;
	    }
	    par.pan[i][j] = new_panel(par.get.bingo[i][j]);
	    if(par.pan[i][j]==NULL)
	    {
		del_panel(par.chancepan);
		delwin(par.playchance);
		del_panel(par.bingcnt);
		delwin(par.bingocnt);
		for(i=0;i<5;i++)
		    for(j=0;j<5;j++)
			delwin(par.get.bingo[i][j]);
		for(t1=0;t1<=i;++t1)
		    for(t2=0;t2<5;++t2)
			{
				if(t1==i&&t2==j)
			 	   break;
				del_panel(par.pan[t1][t2]);
			}

		*err="Unable to create PANEL";				//ERROR MSG
		//	pthread_mutex_destoy(&par.get.get_m);
		//	pthread_mutex_destoy(&par.get.done_mutex);
		//	pthread_cond_destoy(&par.get.done);
		return;
	    }

	    wattron(par.get.bingo[i][j],COLOR_PAIR(1)|A_REVERSE);		//ENABLES ATTRIBUTES IN THE ARGUMENTS


	    wborder(par.get.bingo[i][j],'|','|','-','-','+','+','+','+');	//FOR BORDERING THE WINDOW

	    wattroff(par.get.bingo[i][j],COLOR_PAIR(1)|A_REVERSE);		//DISABLES ATTRIBUTES IN THE ARGUMENTS

	    mvwprintw(par.get.bingo[i][j],2,3,"%d",par.get.array[i][j]);		//MOVES TO THE REQ POSITION AND PRINTS IN THE WINDOW

	    starty+=right;

	}
	startx+=width-1;
	starty = sy; 
    }




    wattron(par.get.bingo[0][0],A_STANDOUT);
    mvwprintw(par.get.bingo[0][0],2,3,"%d",par.get.array[0][0]);
    wattroff(par.get.bingo[0][0],A_STANDOUT);
    update_panels();	
    doupdate();				//REFRESHES ALL THE PANELS IN ORDER REQUIRED





    if(pthread_create(&par.pid,NULL,get_key_t,&par.get)<0)
    {
	close(par.sersd);
	del_panel(par.chancepan);
	delwin(par.playchance);
	del_panel(par.bingcnt);
	delwin(par.bingocnt);

	for(t1=0;t1<5;++t1)
	    for(t2=0;t2<5;++t2)
	    {
		delwin(par.get.bingo[t1][t2]);
		del_panel(par.pan[t1][t2]);
	    }
	*err="Unable to create Get Key thread";
	//	pthread_mutex_destoy(&par.get.get_m);
	//	pthread_mutex_destoy(&par.get.done_mutex);
	//	pthread_cond_destoy(&par.get.done);
	return;
    }

    if(pthread_create(&par.get.pid,NULL,client_game_t,&par)<0)
    {
	close(par.sersd);
	pthread_cancel(par.pid);
	del_panel(par.chancepan);
	delwin(par.playchance);
	del_panel(par.bingcnt);
	delwin(par.bingocnt);

	for(t1=0;t1<5;++t1)
	    for(t2=0;t2<5;++t2)
	    {
		del_panel(par.pan[t1][t2]);
		delwin(par.get.bingo[t1][t2]);
	    }

	*err="Unable to create Game thread";
	//	pthread_mutex_destoy(&par.get.get_m);
	//	pthread_mutex_destoy(&par.get.done_mutex);
	//	pthread_cond_destoy(&par.get.done);
	return;
    }

    while(1)
    {
	switch(end_game_flag)
	{
	    case 0:
		sleep(0.2);
		break;


	    case -1:

		//TERMINATE	

	    default:
		close(par.sersd);
		for(i=0;i<5;i++)
		{
		    for(j=0;j<5;j++)
		    {
			del_panel(par.pan[i][j]);
			delwin(par.get.bingo[i][j]);
		    }
		}
		del_panel(par.chancepan);
		delwin(par.playchance);
		del_panel(par.bingcnt);
		delwin(par.bingocnt);

		//	pthread_mutex_destoy(&par.get.get_m);
		//	pthread_mutex_destoy(&par.get.done_mutex);
		//	pthread_cond_destoy(&par.get.done);
		return;


	}

    }
}
