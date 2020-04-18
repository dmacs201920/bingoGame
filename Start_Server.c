#include"Bingo_Header.h"

/*
 * cpy if for copying a player pointer's location to another player pointer's location.
 * cmp compares data of two player pointers
 * These are used for initializing cdll
 */
void cpy(void* d,void* s)
{
    bcopy(s,d,sizeof(player));
}
int cmp(void* d1,void* d2)
{
    return bcmp(d1,d2,sizeof(player));
}


extern int end_game_flag;

/*
 * start_server function intializes all the variables required for the game
 * and wait for the game to end.
 */
void start_server(char **err)
{
    int i,j,t1,t2,counter,port_no = 6000;	// i,j,t1,t2 are counter variables.
    end_game_flag=0;	// initailizes end_game_flag.
    game_p par;
    par.get.x=par.get.y=par.get.p=par.get.q=0;	// Initializes co-ordinate variables for get_key thread.
    par.get.pl.n=1;	// Initializes no. of players to 1.
    player p;
    /********************* Initializes mutex and conition variables *************************/
    if(pthread_mutex_init(&par.get.get_m,NULL)!=0)
    {
	*err = "MUTEX INIT ERROR";
	return;
    }
    if(pthread_mutex_init(&par.get.pl.lock,NULL)!=0)
    {
	*err = "MUTEX INIT ERROR";
	return;
    }
    if(pthread_mutex_init(&par.get.done_mutex,NULL)!=0)
    {
	*err = "MUTEX INIT ERROR";
	return;
    }
    if(pthread_cond_init(&par.get.done,NULL)!=0)
    {
	*err = " PTHREAD COND INIT ERROR";
	return;
    }
    /****************************************************************************************/
    fill_bingo(par.get.array);	// fills the server size bingo array.
    p.adl=sizeof(p.ad);		// Sets address length.
    init(&par.get.pl.l,sizeof(player),cmp,NULL,cpy);	// Initializes cdll.

    if((par.sersd=p.sd=socket(AF_INET,SOCK_STREAM,0))<0)	// Gets a stream socket.
    {
	*err="Unable to open stream socket";
	return;
    }
    p.bngcnt=0;		// Initaializes bingo count.
    bzero(&p.ad,sizeof(p.ad));	// fills address variable with zeros
    p.ad.sin_family=AF_INET;	// Sets socket family
    p.ad.sin_addr.s_addr=inet_addr(MY_ADDR);	// Sets internet address
    p.plid=0;		// Sets player id.
    /*********************** Chooses a free port number by itrating port number from 6000 to 2000 *****/
    while(port_no>2000)
    {
	p.ad.sin_port=htons(port_no);
	if(bind(p.sd,ADCAST &p.ad,p.adl)<0)
	{
	    --port_no;
	    continue;
	}
	break;
    }
    /**************************************************************************************************/
    if(port_no<2000)	// Unable to find a free prot number
    {
	close(p.sd);
	*err="Unable to bind with the local address";
	return;
    }
    /**************************************************************************************************/

    if(listen(p.sd,5)<0) // listens to the socket for connections
    {
	*err="Unable to listen on the port";
	return;
    }

    /**************************************************************************************************/
    insertl(&par.get.pl.l,&p,0); // puts server in the cdll of players
    conf_p conf;
    conf.status=0;		// Initializes status
    conf.pl=&par.get.pl;	// Sets the address of player list to conf.pl
    if(( conf.w = newwin(15,45,10,40))==NULL)	// Creates a accept window
    {
	close(p.sd);
	*err="Unable to create WINDOW";
	return;
    }
    if((conf.pan= new_panel(conf.w))==NULL)	// Wraps that accept window with a panel
    {
	delwin(conf.w);
	*err="Unable to create PANEL";
	close(p.sd);
	return;
    }
    //print p.sd
    //Start both accept and quitstart threads
    if(pthread_create(&conf.acct,NULL,accept_t,&conf)!=0)	// Creates accept_t thread
    {
	close(p.sd);
	*err="Unable to create accept pthread";
	return;
    }

    if(pthread_create(&conf.sqt,NULL,startquit,&conf)!=0)	// Creates startquit thread
    {
	close(p.sd);
	pthread_cancel(conf.acct);
	node *tmp=par.get.pl.l.h;
	do
	{
	    close(((player*)tmp->d)->sd);
	    tmp=tmp->n;
	}while(tmp!=par.get.pl.l.h);
	freecdll(par.get.pl.l);
	*err="Unable to create startquit pthread";
	return;
    }
    while(conf.status==0)	// Waits for start or quit the game.
	sleep(0.2);
    /**************************************************************************************************/

    /******************** Remove all that is used only in accept_t*************************************/
    del_panel(conf.pan);
    delwin(conf.w);
    clear();	// Clears screen for printing bingo grid clean
    refresh();
    ((player*)par.get.pl.l.h->d)->plid=0;
    node* temp=conf.pl->l.h->n;
    i=0;
    do
    {
	((player*)temp->d)->plid=++i;		// Sets player id
	pthread_cancel(((player*)temp->d)->tid);// Cancels confirm thread of each player. 
	temp=temp->n;
    }while(temp!=conf.pl->l.h);
    /**************************************************************************************************/
    if(conf.status<1)
    {
	if(conf.status==-1)
	    pthread_join(conf.acct,(void**)err);	// Checks for error
	node *tmp=par.get.pl.l.h;
	    if(tmp!=NULL)
	do
	{
	    close(((player*)tmp->d)->sd);
	    tmp=tmp->n;
	}while(tmp!=par.get.pl.l.h);
	freecdll(par.get.pl.l);
	return;
    }
    /******************** Creates windows and panels for bingo screen**********************************/
    //print screen
    int startx = 7,starty = 60,row,col;
    par.playchance = newwin(3,120,3,starty);		//CREATES THE WINDOW AND RETURNS A POINTER TO THE PLAYCHANCE
    if(par.playchance==NULL)				
    {
	*err="Unable to create WINDOW";				//ERROR MSG
	node *tmp=par.get.pl.l.h;
	do
	{
	    close(((player*)tmp->d)->sd);
	    tmp=tmp->n;
	}while(tmp!=par.get.pl.l.h);
	freecdll(par.get.pl.l);
	return;
    }

    par.chancepan = new_panel(par.playchance);			//CREATES THE PANEL AND RETURN THE POINTER TO CHANCEPAN
    if(par.chancepan==NULL)				
    {
	delwin(par.playchance);
	*err="Unable to create PANEL";				//ERROR MSG
	node *tmp=par.get.pl.l.h;
	do
	{
	    close(((player*)tmp->d)->sd);
	    tmp=tmp->n;
	}while(tmp!=par.get.pl.l.h);
	freecdll(par.get.pl.l);
	return;
    }

    par.bingocnt = newwin(60,3,startx+2,starty-5);
    if(par.bingocnt==NULL)				
    {
	delwin(par.playchance);
	del_panel(par.chancepan);
	node *tmp=par.get.pl.l.h;
	do
	{
	    close(((player*)tmp->d)->sd);
	    tmp=tmp->n;
	}while(tmp!=par.get.pl.l.h);
	freecdll(par.get.pl.l);
	*err="Unable to create WINDOW";				//ERROR MSG
	return;
    }

    par.bingcnt = new_panel(par.bingocnt);
    if(par.bingcnt==NULL)				
    {
	delwin(par.playchance);
	del_panel(par.chancepan);
	delwin(par.bingocnt);
	node *tmp=par.get.pl.l.h;
	do
	{
	    close(((player*)tmp->d)->sd);
	    tmp=tmp->n;
	}while(tmp!=par.get.pl.l.h);
	freecdll(par.get.pl.l);
	*err="Unable to create PANEL";				//ERROR MSG
	return;
    }

    ////////////////////////////////////////////////////		CREATING BINGO WINDOWS AND PANELS    


    for(i=0;i<5;i++)
    {
	for(j=0;j<5;j++)
	{


	    par.get.bingo[i][j] = newwin(width,length,startx,starty);
	    if(par.get.bingo[i][j]==NULL)
	    {
		delwin(par.playchance);
		del_panel(par.chancepan);
		delwin(par.bingocnt);
		del_panel(par.bingcnt);
		for(t1=0;t1<=i;++t1)
		    for(t2=0;t2<5;++t2)
		    {
			if(t1==i&&t2==j)
			    break;
			delwin(par.get.bingo[t1][t2]);
		    }
		*err="Unable to create WINDOW";				//ERROR MSG
		node *tmp=par.get.pl.l.h;
		do
		{
		    close(((player*)tmp->d)->sd);
		    tmp=tmp->n;
		}while(tmp!=par.get.pl.l.h);
		freecdll(par.get.pl.l);
		return;
	    }
	    par.pan[i][j] = new_panel(par.get.bingo[i][j]);
	    if(par.pan[i][j]==NULL)
	    {
		delwin(par.playchance);
		del_panel(par.chancepan);
		delwin(par.bingocnt);
		del_panel(par.bingcnt);
		for(t1=0;t1<=i;++t1)
		    for(t2=0;t2<5;++t2)
		    {
			if(t1==i&&t2==j)
			    break;
			del_panel(par.pan[t1][t2]);
		    }
		*err="Unable to create PANEL";				//ERROR MSG
		node *tmp=par.get.pl.l.h;
		do
		{
		    close(((player*)tmp->d)->sd);
		    tmp=tmp->n;
		}while(tmp!=par.get.pl.l.h);
		freecdll(par.get.pl.l);
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




    /**************************************************************************************************/
    /**************************************************************************************************/
    wattron(par.get.bingo[0][0],A_STANDOUT);
    mvwprintw(par.get.bingo[0][0],2,3,"%d",par.get.array[0][0]);	// Highlighting a position in grid
    wattroff(par.get.bingo[0][0],A_STANDOUT);
    update_panels();	
    doupdate();				//REFRESHES ALL THE PANELS IN ORDER REQUIRED


    /*************************************** Createing server game and get_key threads**********************/
    if(pthread_create(&par.get.gameid,NULL,serv_game_t,&par)!=0)
    {
	pthread_cancel(par.getid);
	node *tmp=par.get.pl.l.h;
	do
	{
	    close(((player*)tmp->d)->sd);
	    tmp=tmp->n;
	}while(tmp!=par.get.pl.l.h);
	freecdll(par.get.pl.l);
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
	*err="Unable to create game pthread";
	return;
    }



    if(pthread_create(&par.getid,NULL,get_key_t,&par.get)!=0)
    {
	node *tmp=par.get.pl.l.h;
	do
	{
	    close(((player*)tmp->d)->sd);
	    tmp=tmp->n;
	}while(tmp!=par.get.pl.l.h);
	freecdll(par.get.pl.l);
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
	*err="Unable to create Get Key thread";
	return;
    }
    /**************************************************************************************************/

    while(end_game_flag==0)		// Waits for game to end
	sleep(0.1);
    if(end_game_flag>0)			// Cgets erro from the game.
	pthread_join(par.get.gameid,(void**)err);
    /***************************** Destroys windows, panels, cdll and sozkets ***************************/
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
    node *tmp=par.get.pl.l.h;
    do
    {
	close(((player*)tmp->d)->sd);
	tmp=tmp->n;
    }while(tmp!=par.get.pl.l.h);
    freecdll(par.get.pl.l);
    /****************************************************************************************************/
    return;
}
