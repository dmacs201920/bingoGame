#include"Bingo_Header.h"

/*
		FUNCTION FOR TIMED WAITING AND RECIEVING DATA FROM USER
		IF THE TIME COMPLETES BEFORE THE USER ENTERS DATA, USER LOSES HIS CHANCE

*/   
/*
void* cond_wait(void* arg)
{
    cond_p *par=arg;
    pthread_cond_wait(par->c,par->m);
    par->flag=1;
    pthread_cancel(par->tmr);
    pthread_exit(NULL);
}
//***************************************************** RUNS THE TIMER ************************************************************************
void* timer(void* arg)
{
    cond_p *par=arg;
    sleep(par->sec);
    if(par->flag==0)
	pthread_cancel(par->cwait);
    par->flag=2;
    pthread_exit(NULL);
}
//*********************************************************************************************************************************************


int timedwait_cond(pthread_cond_t *c,pthread_mutex_t *m,int sec)
{

    //**********************************************  INITIALIZATIONS  ***********************************************************************

    cond_p par;
    par.c=c;
    par.m=m;
    par.sec=sec;
    par.flag=0;

    //***********************************************************************************************************************

    if(pthread_create(&par.cwait,NULL,cond_wait,&par)!=0) 		//CREATING THE RECIEVE FUNCTION 
    {
	return -1;
    }
    if(pthread_create(&par.tmr,NULL,timer,&par)!=0)			//CREATING THE TIMER FUNCTION
    {
	pthread_cancel(par.cwait);
	return -1;
    }
    while(par.flag==0);						// WAIT TILL FLAG CHANGED

    return par.flag-1;						// IF FLAG = 2 TIME EXCEEDED WITHOUT INPUT
    								// IF FLAG = 1 INPUT TAKEN WITHIN TIME
}
*/
int timedwait_cond(pthread_cond_t *c,pthread_mutex_t *m,int sec)
{
    struct timespec t1;
    struct timeval t2;
    int stat;
    if((stat=gettimeofday(&t2,NULL))!=0)
        return errno;
    t1.tv_sec=t2.tv_sec+sec;
    t1.tv_nsec=t2.tv_usec*1000;
    return pthread_cond_timedwait(c,m,&t1);
}

