#include"Bingo_Header.h"

void cleanup_t(void* arg)
{
    conf_p *conf=arg;
    node *t=conf->pl->l.h;
    int i=-1;
    do
    {
	((player*)t->d)->plid=++i;
	pthread_cancel(((player*)t->d)->tid);
	t=t->n;
    }while(t!=conf->pl->l.h);
}

void* accept_t(void* arg)
{
    player p;
    p.adl=sizeof(p.ad);
    conf_p *pl=arg;;
    node* t=pl->pl->l.h;
    struct sockaddr_in head_ad = ((player*)t->d)->ad;
    player *pnt;
    int i,j;
    for(i=0;i<5;++i)
    {
	for(j=0;j<5;++j)
	{
	    printw("%d  ",((player*)t->d)->array[i][j]);
	}
	printw("\n");
    }
    refresh();
    sleep(2);
    server_started_screen(pl->w,pl->pan,head_ad,pl->pl->n);
    pthread_cleanup_push(cleanup_t,arg);
    while(pl->pl->n<5)
    {
senderr:
	if((p.sd=accept(((player*)t->d)->sd,ADCAST &p.ad,&p.adl))<0)
	{
	    pthread_mutex_lock(&pl->pl->lock);
	    pthread_cancel(pl->sqt);
	    pthread_mutex_unlock(&pl->pl->lock);
	    pl->status=-1;
	    pthread_exit("Unable to accept connction");
	}

	pthread_mutex_lock(&pl->pl->lock);
	insertl(&pl->pl->l,&p,1);
	pl->p=pl->pl->l.h->n;
	pnt=pl->p->d;
	fill_bingo(pnt->array);
	pnt->bngcnt=0;
	for(i=0;i<5;++i)
	{
	    for(j=0;j<5;++j)
	    {
		if(send(pnt->sd,&pnt->array[i][j],sizeof(int),0)!=sizeof(int))
		{
		    close(p.sd);
		    pthread_mutex_unlock(&pl->pl->lock);
		    printw("\nSend Err\n");
		    refresh();
		    sleep(2);
		    goto senderr;
		}

	    }

	}
	printw("\n\n");
	for(i=0;i<5;++i)
	{
	    for(j=0;j<5;++j)
	    {
		printw("%d  ",pnt->array[i][j]);
	    }
	    printw("\n");
	}
	refresh();

	if(pthread_create(&pnt->tid,NULL,confirm_t,arg)!=0)
	{
	    close(p.sd);
	    pthread_mutex_unlock(&pl->pl->lock);
	    goto senderr;
	}
	server_started_screen(pl->w,pl->pan,head_ad,++pl->pl->n);
	pthread_mutex_unlock(&pl->pl->lock);
    }

    del_panel(pl->pan);
    delwin(pl->w);
    pthread_cancel(pl->sqt);
    pl->status=1;
    pthread_cleanup_pop(1);
    pthread_exit(NULL);
}
