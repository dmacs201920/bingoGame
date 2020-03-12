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
		if(conf->n==1)
		    continue;
		conf->status=1;
		break;
	    case 'q':
		if(conf->n>1)
		conf->status=-1;
	}
    }
    pthread_mutex_lock(&conf->lock);
    pthread_cancel(conf->acct);
    pthread_mutex_unlock(&conf->lock);
    pthread_exit(NULL);
}
