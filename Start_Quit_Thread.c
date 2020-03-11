#include"Bingo_Header.h"
void* startquit(void* arg)
{
    playerlist *p=arg;
    int c;
    while(p->status==0)
    {
	c=getch();
	update_panels();
	doupdate();
	switch(c)
	{
	    case '\n':
		if(p->n==1)
		    continue;
		p->status=1;
		break;
	    case 'q':
		if(p->n>1)
		p->status=-1;
	}
    }
    pthread_mutex_lock(&p->lock);
    pthread_cancel(p->acct);
    pthread_mutex_unlock(&p->lock);
    pthread_exit(NULL);
}
