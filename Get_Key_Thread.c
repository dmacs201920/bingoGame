#include"Bingo_Header.h"
extern int end_game_flag;
void* get_key_t(void *arg)
{

    getkey_p *par=arg;
print_array(par->bingo,par->array,(par->x),(par->y));
    int ch,f;
    
    while(ch=getch())
    {
	switch(ch)
	{
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
