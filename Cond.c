#include"Bingo_Header.h"
void* cond_wait(void* arg)
{
    cond_p *par=arg;
    pthread_cond_wait(par->c,par->m);
    par->flag=1;
    pthread_cancel(par->tmr);
    pthread_exit(NULL);
}
void* timer(void* arg)
{
    cond_p *par=arg;
    sleep(par->sec);
    if(par->flag==0)
	pthread_cancel(par->cwait);
    par->flag=2;
    pthread_exit(NULL);
}
int timedwait_cond(pthread_cond_t *c,pthread_mutex_t *m,int sec)
{
    cond_p par;
    par.c=c;
    par.m=m;
    par.sec=sec;
    par.flag=0;
    if(pthread_create(&par.cwait,NULL,cond_wait,&par)!=0)
    {
	return -1;
    }
    if(pthread_create(&par.tmr,NULL,timer,&par)!=0)
    {
	pthread_cancel(par.cwait);
	return -1;
    }
    while(par.flag==0);
    return par.flag-1;
}
