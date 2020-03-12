#include"Bingo_Header.h"

void* cleanup_t(void* arg)
{
    conf_p *conf=arg;
    node *t=conf->pl->l.h;
    pthread_mutex_lock(conf->lock);
    int i=-1;
    do
    {
	((player*)t->d)->plid=++i;
	pthread_cancel(((player*)t->d)->tid);
	t=t->n;
    }while(t!=conf->pl->l.h);
    pthread_mutex_unlock(conf->lock);
}

void* accept_t(void* arg)
{
    player p;
    p.adl=sizeof(p.ad);
    conf_p *pl=arg;;
    node* t=pl->pl->l.h;
    server_started_screen(pl->w,pl->pan,((player*)t->d)->ad,*(pl->n));
    int i,j;
    pthread_cleanup_push(cleanup_t,arg);
    while(*(pl->n)<5)
    {
senderr:
	if((p.sd=accept(((player*)t->d)->sd,ADCAST &p.ad,&p.adl))<0)
	{
	    pthread_mutex_lock(pl->lock);
	    pthread_cancel(pl->sqt);
	    pthread_mutex_lock(pl->lock);
	    pl->status=-1;
	    pthread_exit("Unable to accept connction");
	}
	pthread_mutex_lock(pl->lock);
	fill_bingo(p.array);
	for(i=0;i<5;++i)
	{
	    for(j=0;j<5;++j)
	    {
		if(send(p.sd,&p.array[i][j],sizeof(int),0)!=sizeof(int))
		{
		    close(p.sd);
		    pthread_mutex_unlock(pl->lock);
		    printw("\nSeand Err\n");
		    refresh();
		    sleep(2);
		    goto senderr;
		}

	    }

	}
	p.bngcnt=0;
	insertl(&pl->pl->l,&p,-1);
	pl->p=pl->pl->l.h->p;
	if(pthread_create(&(((player*)pl->p->d)->tid),NULL,confirm_t,arg)!=0)
	{
	    close(p.sd);
	    pthread_mutex_unlock(pl->lock);
	    goto senderr;
	}
	++(*(pl->n));
	server_started_screen(pl->w,pl->pan,((player*)t->d)->ad,*(pl->n));
	pthread_mutex_unlock(pl->lock);
    }
    pthread_cleanup_pop(1);
    del_panel(pl->pan);
    delwin(pl->w);
    pthread_cancel(pl->sqt);
    pl->status=1;
    pthread_exit(NULL);
}
