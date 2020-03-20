#include"Bingo_Header.h"
/*
		FUNCTION TO ACCEPT PLAYERS AND STORE IT IN THE CDLL.
*/

void* accept_t(void* arg)
{//////////////////////////////////////////////////////// INITIALIZATIONS OF VARIABLES ////////////////////////////////////////////////////////////
    player p;
    p.adl=sizeof(p.ad);
    conf_p *pl=arg;		
    node* t=pl->pl->l.h;
    struct sockaddr_in head_ad = ((player*)t->d)->ad;
    player *pnt;
    int i,j,flag = 0;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    server_started_screen(pl->w,head_ad,pl->pl->n);	// TO PRINT THE START SERVER SCREEN

    while(pl->pl->n<5)			//CAN ACCEPT ONLY 5 PLAYERS MAXIMUM
    {
	/////////////////////////////////////////////// SOCKET ACCEPT FUNCTION.. ACCEPTS THE PLAYER'S CONNECTION//////////////////////////////
	if((p.sd=accept(((player*)t->d)->sd,ADCAST &p.ad,&p.adl))<0)
	{
	    pthread_mutex_lock(&pl->pl->lock);
	    pthread_cancel(pl->sqt);
	    pthread_mutex_unlock(&pl->pl->lock);
	    pl->status=-1;
	    pthread_exit("Unable to accept connction");		//ERROR IN ACCEPT
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	pthread_mutex_lock(&pl->pl->lock);		// TO ENSURE DATA FROM GETTING CORRUPT BY OTHER PLAYER DETAILS
	insertl(&pl->pl->l,&p,1);			// CDLL FUNCTION TO INSERT THE PLAYER INTO THE LIST
	pl->p=pl->pl->l.h->n;				// ADDING THE PLAYER FROM REAR
	pnt=pl->p->d;
	fill_bingo(pnt->array);				// FILLS THE BINGO GAME PLAY ARRAY
	pnt->bngcnt=0;					//SETTING THE BINGO COUNT TO ZERO

	/////////////////////////////////////// SENDING THE BINGO GAME PLAY ARRAY//////////////////////////////////////////////////////////////
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
		    flag = 1;			//ERROR IN SENDING. SETTING FLAG TO 1
		    break;
		}
	    }
	    if(flag)
		break;				//BREAKING OUT OF LOOP

	}
	if(flag)
	    continue;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////////////////// CREATING THREAD TO CONFIRM THE PLAYER'S EXISTANCE/////////////////////////////////////////
	if(pthread_create(&pnt->tid,NULL,confirm_t,arg)!=0)
	{
	    close(p.sd);
	    pthread_mutex_unlock(&pl->pl->lock);
	    continue;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	server_started_screen(pl->w,head_ad,++pl->pl->n);
	pthread_mutex_unlock(&pl->pl->lock);			//UNLOCKING MUTEX SO THE DATA CAN BE FILLED FOR THE NEXT
    }

    //////////////////////////////////////////// WHEN PLAYERS JOINED ABOVE FIVE THIS THREAD EXITS WITH STATUS 1 /////////////////////////////////////

    pthread_cancel(pl->sqt);		// CANCELLING THE START_QUIT THREAD
    pl->status=1;
    pthread_exit(NULL);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
