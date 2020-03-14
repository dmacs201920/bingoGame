#include"Bingo_Header.h"

void* recv_t(void* arg)
{
    recv_p *p=arg;
    p->status=recv(p->sd,p->data,p->size,p->flags);
    pthread_cancel(p->tmrt);
    pthread_exit(NULL);
}

void* timer_2(void* arg)
{
    recv_p *par=arg;
    sleep(par->sec);
    if(par->status==-2)
	pthread_cancel(par->recvt);
    par->status=-1;
    pthread_exit(NULL);
}


int timed_recv(int sd,void* data,int size,int flags,int sec)
{
    recv_p par;
    par.sd=sd;
    par.status=-2;
    par.size=size;
    par.flags=flags;
    par.sec=sec;
    par.data=data;
    if(pthread_create(&par.recvt,NULL,recv_t,&par)!=0)
    {
	return -1;
    }

    if(pthread_create(&par.tmrt,NULL,timer_2,&par)!=0)
    {
	pthread_cancel(par.recvt);
	return -1;
    }
    while(par.status==-2);
    return par.status;
}

