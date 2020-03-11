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
    conf_p conf;
   if(( conf.w = newwin(15,45,10,40))==NULL)
   {
       pthread_exit("Unable to create WINDOW");
       pl->status=-1;
   }
    if((conf.pan= new_panel(conf.w))==NULL)
    {
	delwin(conf.w);
	pthread_exit("Unable to create PANEL");
       pl->status=-1;
    }
    node* t=pl->l.h;
    conf.lock=&pl->lock;
    conf.n=&pl->n;
    server_started_screen(conf.w,conf.pan,((player*)t->d)->ad,*conf.n);
    pthread_cleanup_push(cleanup_t,arg);
   int i,j;
    while(pl->n<5)
    {
	if((p.sd=accept(((player*)t->d)->sd,ADCAST &p.ad,&p.adl))<0)
	{
	    pthread_exit("Unable to accept connction");
	    pl->status=-1;
	}
	pthread_mutex_lock(&pl->lock);
	++pl->n;
	fill_bingo(p.array);
   for(i=0;i<5;++i)
    {
	for(j=0;j<5;++j)
	{
    	if(send(p.sd,&p.array[i][j],sizeof(int),0)!=sizeof(int))
	    {
	    close(p.sd);
	    pthread_mutex_unlock(&pl->lock);
	    continue;
	    }

	}

    }
	p.bngcnt=0;
	insertl(&pl->l,&p,-1);
	conf.pl=pl->l.h->p;
	server_started_screen(conf.w,conf.pan,((player*)t->d)->ad,*conf.n);
	if(pthread_create(&(((player*)conf.pl->d)->tid),NULL,confirm_t,&conf)!=0)
	{
	    del_panel(conf.pan);
	    delwin(conf.w);
	    pthread_exit("Unable to create confirm pthread");
	    pl->status=-1;
	}
	pthread_mutex_unlock(&pl->lock);
    }
    pthread_cleanup_pop(1);
    del_panel(conf.pan);
    delwin(conf.w);
    pthread_cancel(pl->sqt);
    pl->status=1;
    pthread_exit(NULL);
}
