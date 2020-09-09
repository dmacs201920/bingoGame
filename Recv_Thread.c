#include"Bingo_Header.h"
/*
 * recv_t is the thread that calls recv() function on the required socket.
 * it cancels the timer_2 thread when it is done and sets status variable.
 *
 * timer_2 is the thread that sleeps for a finite and given amount of time
 * cancels recv_t when it wakes up and sets status to -3.
 *
 * timed_recv is a function which does the function of recv function
 * but blocks for only the given amount of time.
 *
 * All the threads use recv_p as the parameter to be passed.
 */

/****************************************************************/
/*
void* recv_t(void* arg)
{
    recv_p *p=arg;

    int x=recv(p->sd,p->data,p->size,p->flags);
    pthread_cancel(p->tmrt);
    p->status=x;
}

//****************************************************************

void* timer_2(void* arg)
{
    recv_p *par=arg;
    sleep(par->sec);
    if(par->status==-2)
	{
        pthread_cancel(par->recvt);
        par->status=-3;
    }
}

//****************************************************************
 //* sd, data, size, flags 	-	Same as recv function.
 //* sec				-	Number os seconds to wait.
 //*
//****************************************************************
int timed_recv(int sd,void* data,int size,int flags,int sec)
{
//************Initialization of par variable********************
    recv_p par;
    par.sd=sd;
    par.status=-2;	// -2 means nothing has happened
    par.size=size;
    par.flags=flags;
    par.sec=sec;
    par.data=data;
//****************************************************************
    if(pthread_create(&par.tmrt,NULL,timer_2,&par)!=0)  // creates timer_2 thread.
    {
       return -1;
    }
    if(pthread_create(&par.recvt,NULL,recv_t,&par)!=0)	// creates recv_t thread
    {
            pthread_cancel(par.tmrt);
	       return -1;
    }


    while(par.status==-2)sleep(0.2);		// Waits for one of those threads to complete their work.
    
    return par.status;		// returns the status.
}*/
/****************************************************************/

int timed_recv(int sd,void* data,int size,int flags,int sec)
{    
    struct timeval t1;
    t1.tv_sec=0;
    t1.tv_usec=10000;
    setsockopt(sd ,SOL_SOCKET, SO_RCVTIMEO, &t1, sizeof(t1));
    return recv(sd,data, size, flags);
}