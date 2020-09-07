#include"Bingo_Header.h"

/*
		FUNCTION WHICH CONFIRMS THE CLIENT'S PRESENCE OTHERWISE REMOVES HIM FROM THE CDLL
		USED BY THE SERVER SIDE 
*/   

void* confirm_t(void* arg)
{
    /************************************************  INITIALIZATIONS **************************************************************************/
    conf_p p=*(conf_p*)arg;
    data d;
    int val;
    /*******************************************************************************************************************************************/

    while((val = recv(((player*)(p.p->d))->sd,&d,sizeof(data),0))==sizeof(data));	//WAITS FOR A RECIEVE MSG FROM CLIENT

    pthread_mutex_lock(&p.pl->lock);				//LOCKING DATA TO ENSURE NO CLASH BETWEEN FUNCTIONS
    close(((player*)p.p->d)->sd);				//CLOSING THE CONNECTION OF THE CLIENT
    p.p->n->p=p.p->p;						
    p.p->p->n=p.p->n;						//REMOVING THE CLIENT FROM LIST
    free(p.p->d);
    free(p.p);							// FREEING FROM THE CDLL
    --p.pl->n;							//DECREMENTING PLAYER COUNT
   
    server_started_screen(p.w,((player*)p.pl->l.h->d)->ad,p.pl->n);		//SCREEN PRINTING OF THE PLAYERS JOINED CHANGE
    pthread_mutex_unlock(&p.pl->lock);							//UNLOCKING THE DATA FOR OTHER FUNCTIONS USE
}
