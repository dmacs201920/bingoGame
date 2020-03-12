#include"Bingo_Header.h"


void cpy(void* d,void* s)
{
    *(player*)d=*(player*)s;
}
int cmp(void* d1,void* d2)
{
    return bcmp(d1,d2,sizeof(player));
}


extern int end_game_flag;


void start_server(char **err)
{
    int counter,port_no = 6000;
    end_game_flag=0;
    game_p par;
    par.get.pl.status=0;
    par.get.pl.n=1;
    player p;
    conf_p;
    pthread_mutex_init(&par.get.pl.lock,NULL);
    fill_bingo(p.array);

    p.adl=sizeof(p.ad);
    init(&par.get.pl.l,sizeof(player),cmp,NULL,cpy);

    if((p.sd=socket(AF_INET,SOCK_STREAM,0))<0)
    {
	*err="Unable to open stream socket";
	return;
    }
    p.bngcnt=0;
    p.ad.sin_family=AF_INET;
    p.ad.sin_addr.s_addr=inet_addr(MY_ADDR);
    p.plid=0;


    while(port_no>2000)
    {
	p.ad.sin_port=htons(port_no);
	if(bind(p.sd,ADCAST &p.ad,p.adl)<0)
	    --port_no;
	break;
    }
    if(port_no<2000)
    {
	close(p.sd);
	*err="Unable to bind with the local address";
	return;
    }
    if(listen(p.sd,5)<0)
    {
	*err="Unable to listen on the port";
	return;
    }


    insertl(&par.get.pl.l,&p,0);
    conf_p conf;
    conf.status=0;
    conf.lock=&par.get.pl.lock;
    conf.n=&par.get.pl.n;
    if(( conf.w = newwin(15,45,10,40))==NULL)
   {
       close(p.sd);
       *err="Unable to create WINDOW";
       return;
   }
    if((conf.pan= new_panel(conf.w))==NULL)
    {
	delwin(conf.w);
	*err="Unable to create PANEL";
	close(p.sd);
	return;
    }
    //print p.sd
    //Start both accept and quitstart threads
    if(pthread_create(&conf.acct,NULL,accept_t,&conf)!=0)
    {
	close(p.sd);
	*err="Unable to create accept pthread";
	return;
    }
    
    if(pthread_create(&conf.sqt,NULL,startquit,&conf)!=0)
    {
	close(p.sd);
	pthread_cancel(conf.acct);
	*err="Unable to create startquit pthread";
	return;
    }
    while(par.get.pl.status==0)
	sleep(0.2);
    del_panel(conf.pan);
    delwin(conf.w);
    clean();
    refresh();
    pthread_join(par.get.pl.acct,(void**)err);
    if(conf.status==-1)
    {
	close(p.sd);
	return;
    }
    //print screen
    int startx = 7,starty = 60,row,col;
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
	delwin(par.playchance);
	del_panel(par.chancepan);
	*err="Unable to create WINDOW";				//ERROR MSG
	//	pthread_mutex_destoy(&par.get.get_m);
	//	pthread_mutex_destoy(&par.get.done_mutex);
	//	pthread_cond_destoy(&par.get.done);
	return;
    }

    par.bingcnt = new_panel(par.bingocnt);
    if(par.bingcnt==NULL)				
    {
	delwin(par.playchance);
	del_panel(par.chancepan);
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
		//	pthread_mutex_destoy(&par.get.get_m);
		//	pthread_mutex_destoy(&par.get.done_mutex);
		//	pthread_cond_destoy(&par.get.done);
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





    if(pthread_create(&par.getid,NULL,get_key_t,&par.get)!=0)
    {
	close(par.sersd);
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
	//	pthread_mutex_destoy(&par.get.get_m);
	//	pthread_mutex_destoy(&par.get.done_mutex);
	//	pthread_cond_destoy(&par.get.done);
	return;
    }

    if(pthread_create(&par.get.gameid,NULL,serv_game_t,&par)!=0)
    {
	pthread_cancel(par.getid);
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
	close(p.sd);
	*err="Unable to create game pthread";
	return;
    }
    while(end_game_flag==0)
	sleep(0.1);
    if(end_game_flag!=0)
	pthread_join(serv_gamet,(void**)err);

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
    close(p.sd);
    return;
}
