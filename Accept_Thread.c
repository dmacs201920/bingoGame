#include"Bingo_Header.h"


void* cleanup_t(void* arg)
{
	playerlist *pl=arg;
	node* t=pl->l.h->n;
	pthread_mutex_lock(&pl->lock);
	int i=-1;
	do
	{
		((player*)t->d)->plid=++i;
		pthread_cancel(((player*)t->d)->tid);
		t=t->n;
	}while(t!=pl->l.h);
	pthread_mutex_unlock(&pl->lock);
}

void* accept_t(void* arg)
{
    playerlist *pl=arg;
    player p;
    conf.w = newwin(15,45,10,40);
    conf.cancel = derwin(conf.w,3,10,12,35);
    conf.start = derwin(conf.w,3,9,12,0);
    conf.pan[0] = new_panel(conf.w);
    conf.pan[1] = new_panel(conf.start);
    conf.pan[2] = new_panel(conf.cancel);

    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_RED,COLOR_BLACK);
    init_pair(3,COLOR_BLUE,COLOR_BLACK);
    int status;
    init(&pl->l,sizeof(player),cmp,NULL,cpy);
    node* t=pl->l.h;
	conf_p conf;
	conf.lock=&pl->lock;
    fill_bingo(((player*)t->d)->array);
    ((player*)t->d)->bngcnt=0;
	pthread_cleanup_push(cleanup_t,arg);
    while(pl->n<5)
    {
	if((p.sd=accept(((player*)t->d)->sd,ADCAST &p.ad,&p.adl))<0)
	{
	    pthread_exit("Unable to accept connction");
	}
	pthread_mutex_lock(&pl->lock);
	++pl->n;
	fill_bingo(p.array);
	if((status=send(p.sd,p.array,sizeof(p.array),0))!=sizeof(p.array))
	{
	    close(p.sd);
	    pthread_mutex_unlock(&pl->lock);
	    continue;
	}
	p.bngcnt=0;
	insertl(&pl->l,&p,-1);
	conf.pl=pl->l.h->p;
	if(pthread_create(&(((player*)conf.pl->d)->tid),NULL,confirm_t,&conf)!=0)
	{
		//error
	}
	pthread_mutex_unlock(&pl->lock);
    }
	pthread_cleanup_pop(1);
	delwin(start);
	del_panel(pan[1]);
	delwin(cancel);
	del_panel(pan[1]);
	delwin(w);
	del_panel(pan[0]);
    pthread_cancel(pl->sqt);
    pthread_exit(NULL);
}
