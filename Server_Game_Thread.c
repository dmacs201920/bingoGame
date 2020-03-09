#include"Bingo_Header.h"
int end_game_flag;
void* serv_game_t(void* arg)
{
    char* err=NULL;
    data d;
    int counter,i,j,status;
    game_p *par=arg;
    node *Current_player=par->get.pl.l.h,*tr,*t,*trav=par->get.pl.l.h;
    int ch,flag=0,id;
    int startx = 7,starty = 60,row,col;

    while(Current_player!=Current_player->n)
    {
	if(Current_player==par->get.pl.l.h)
	{
	    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
	    mvwprintw(par->playchance,1,1,"       YOU ARE PLAYING     ");
	    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD); 
	    update_panels();
	    doupdate();
	    pthread_mutex_unlock(&par->get.get_m);
	    if(timedwait_cond(&par->get.done,&par->get.done_mutex,10)==0)
	    {
		pthread_mutex_lock(&par->get.get_m);
		d.num=((player*)Current_player->d)->array[par->get.p][par->get.q];
		do
		{
		    search_strike(((player*)tr->d)->array,((player*)Current_player->d)->array[par->get.x][par->get.y],&i,&j);
		    if((((player*)t->d)->bngcnt+=bingos(((player*)t->d)->array,i,j))>4)
			flag=1;
		}while(t!=Current_player);
		print_array(par->get.bingo,((player*)par->get.pl.l.h->d)->array,par->get.x,par->get.y);
	    }
	    else
	    {
		pthread_mutex_lock(&par->get.get_m);
		d.num=0;
	    }
	    if(flag!=1)
	    {
		tr=Current_player->n;
		d.com='y';
		d.opp=((player*)tr->d)->plid;
		d.bng=((player*)tr->d)->bngcnt;
		send(((player*)tr->d)->sd,&d,sizeof(data),0);
		t=Current_player->n;
		tr=tr->n;
		d.com='n';
		for(;tr!=Current_player->n;tr=tr->n)
		    if(tr!=par->get.pl.l.h)
		    {
			d.bng=((player*)tr->d)->bngcnt;
			send(((player*)tr->d)->sd,&d,sizeof(data),0);
		    }
	    }
	    else
	    {
		tr=Current_player->n;
		d.com='t';
		for(;tr!=Current_player->n;tr=tr->n)
		    if(tr!=par->get.pl.l.h)
		    {
			d.bng=((player*)tr->d)->bngcnt;
			send(((player*)tr->d)->sd,&d,sizeof(data),0);
		    }
		if(((player*)par->get.pl.l.h->d)->bngcnt>4)
		{
		    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		    mvwprintw(par->playchance,1,1,"       YOU WON!!!!!        ");
		    wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
		    update_panels();
		    doupdate();
		    sleep(2);
		    pthread_cancel(par->pid);
		    end_game_flag = 1;
		    pthread_exit(NULL);
		}
		else
		{
		    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		    mvwprintw(par->playchance,1,1,"       YOU LOST           ");
		    wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
		    update_panels();
		    doupdate();		sleep(2);
		    pthread_cancel(par->pid);
		    end_game_flag = 2;
		    pthread_exit(NULL);

		}
	    }
	}
	    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
	    mvwprintw(par->playchance,1,1,"        OPPONENT %d IS PLAYING     ",((player*)Current_player->d)->plid);
	    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD); 
	    update_panels();
	    doupdate();
	if((status=timed_recv(((player*)Current_player)->sd,&d,sizeof(data),0,10))!=sizeof(data)&&status!=-1)
	{
	    end_game_flag=-2;
	    err="Unable to create recv pthread";
	    close(((player*)trav->d)->sd);
	    trav=trav->n;
	    for(;trav!=par->get.pl.l.h;trav=trav->n)
		close(((player*)trav->d)->sd);
	}
	else if(status==-1)
	{
	    d.num=-1;
	}
	else
	{	
	    d.num=((player*)Current_player->d)->array[par->get.p][par->get.q];
	    do
	    {
		search_strike(((player*)tr->d)->array,((player*)Current_player->d)->array[par->get.x][par->get.y],&i,&j);
		if((((player*)t->d)->bngcnt+=bingos(((player*)t->d)->array,i,j))>4)
		    flag=1;
	    }while(t!=Current_player);
	print_array(par->get.bingo,((player*)par->get.pl.l.h->d)->array,par->get.x,par->get.y);
	}
	if(flag!=1)
	{
	    tr=Current_player->n;
	    d.com='y';
	    d.opp=((player*)tr->d)->plid;
	    d.bng=((player*)tr->d)->bngcnt;
	    send(((player*)tr->d)->sd,&d,sizeof(data),0);
	    t=Current_player->n;
	    tr=tr->n;
	    d.com='n';
	    for(;tr!=Current_player->n;tr=tr->n)
		if(tr!=par->get.pl.l.h)
		{
		    d.bng=((player*)tr->d)->bngcnt;
		    send(((player*)tr->d)->sd,&d,sizeof(data),0);
		} 
	}
	else
	{
	    tr=Current_player->n;
	    d.com='t';
	    for(;tr!=Current_player->n;tr=tr->n)
		if(tr!=par->get.pl.l.h)
		{
		    d.bng=((player*)tr->d)->bngcnt;
		    send(((player*)tr->d)->sd,&d,sizeof(data),0);
		}
		if(((player*)par->get.pl.l.h->d)->bngcnt>4)
		{
		    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		    mvwprintw(par->playchance,1,1,"       YOU WON!!!!!        ");
		    wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
		    update_panels();
		    doupdate();
		    sleep(2);
		    pthread_cancel(par->pid);
		    end_game_flag = 1;
		    pthread_exit(NULL);

		}

		else
		{
		    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		    mvwprintw(par->playchance,1,1,"       YOU LOST           ");
		    wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
		    update_panels();
		    doupdate();		sleep(2);
		    pthread_cancel(par->pid);
		    end_game_flag = 2;
		    pthread_exit(NULL);

		}
	}

    }

    end_game_flag=-1;
    err="No other player playing";
    pthread_cancel(par->pid);
    close(((player*)trav->d)->sd);
    trav=trav->n;
    for(;trav!=par->get.pl.l.h;trav=trav->n)
	close(((player*)trav->d)->sd);
    pthread_exit(err);
}
