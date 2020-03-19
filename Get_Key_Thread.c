#include"Bingo_Header.h"
/*
 * This function is a thread used in client and server side of the game.
 * It manages the keyboard screen interface.
 * It takes a getkey_p variable as argument.
 */
extern int end_game_flag;	// Global variable for indicating end of the game.
void* get_key_t(void *arg)
{

    getkey_p *par=arg;
    print_array(par->bingo,par->array,(par->x),(par->y));	
    /*Prints the bingo array on the window*/
    int ch;
/***************************** Takes key board input dous the same thing as Get_Key ****************/
    while(ch=getch())
    {
	switch(ch)
	{
	    /************************ if q is pressed exit the game by canceling game thread and				setting end game flag ************************************************/
	    case 'q':
		pthread_cancel(par->gameid);
		end_game_flag = -1;
		pthread_exit(NULL);
		break;
	    case KEY_UP:

		--(par->x);
		if((par->x)<0)
		    (par->x) = 4;


		break;

	    case KEY_DOWN:

		++(par->x);
		if((par->x)>4)
		    (par->x) = 0;
		break;

	    case KEY_LEFT:

		--(par->y);
		if((par->y)<0)
		    (par->y) = 4;
		break;

	    case KEY_RIGHT:
		++(par->y);
		if((par->y)>4)
		    (par->y) = 0;
		break;

	    case 10:
		if(par->array[(par->x)][(par->y)]==0)
		    continue;
		/* If lock is obtained it means that the game thread wants input
		 * Puts the data co-ordinates to par->p and par->q (x & y co-ordinates)
		 * Then signals game thread that data is ready.
		 */
		if(pthread_mutex_trylock(&par->get_m)==0)
		{
		    pthread_mutex_lock(&par->done_mutex);
		    par->p=(par->x);
		    par->q=(par->y);
		    pthread_cond_signal(&par->done);
		    pthread_mutex_unlock(&par->done_mutex);
		    pthread_mutex_unlock(&par->get_m);
		}
	}
	print_array(par->bingo,par->array,(par->x),(par->y));

    }
}

