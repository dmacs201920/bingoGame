#include"Bingo_Header.h"
void* startquit(void* arg)
{
    conf_p *conf=arg;
    int c;
    while(conf->status==0)
    {
	c=getch();
	switch(c)
	{
	    case '\n':
		if(conf->pl->n==1)
		    continue;
		conf->status=1;
		break;
	    case 'q':
		conf->status=-2;
	}
    }
    pthread_mutex_lock(&conf->pl->lock);
    pthread_cancel(conf->acct);
    pthread_mutex_unlock(&conf->pl->lock);
    pthread_exit(NULL);
}
