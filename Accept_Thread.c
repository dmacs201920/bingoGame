#include"Bingo_Header.h"

void* accept_t(void* arg)
{
    player p;
    p.adl=sizeof(p.ad);
    conf_p *pl=arg;;
    node* t=pl->pl->l.h;
    struct sockaddr_in head_ad = ((player*)t->d)->ad;
    player *pnt;
    int i,j,flag = 0;
    server_started_screen(pl->w,pl->pan,head_ad,pl->pl->n);
    while(pl->pl->n<5)
    {
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
		    flag = 1;
		    break;
		}
	    }
		if(flag)
		    break;
		
	}
		if(flag)
		    continue;

	if(pthread_create(&pnt->tid,NULL,confirm_t,arg)!=0)
	{
	    close(p.sd);
	    pthread_mutex_unlock(&pl->pl->lock);
	    continue;
	}
	server_started_screen(pl->w,pl->pan,head_ad,++pl->pl->n);
	pthread_mutex_unlock(&pl->pl->lock);
    }

    del_panel(pl->pan);
    delwin(pl->w);
    pthread_cancel(pl->sqt);
    pl->status=1;
    pthread_exit(NULL);
}
