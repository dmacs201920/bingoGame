#include"Bingo_Header.h"
extern int end_game_flag;
void* client_game_t(void *arg)
{

    game_p *par = arg;
    data d={0,0,0,0};

    int posx,posy,cntr;

    pthread_mutex_lock(&par->get.get_m);

    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
    mvwprintw(par->playchance,1,1,"    WAITING FOR SERVER        ");
    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
    update_panels();
    doupdate();

    while(1)
    {
	if(read(par->sersd,&d,sizeof(data))!=sizeof(data))	// if recv is not functioning
	{
	    end_game_flag = -1;
	    pthread_cancel(par->getid);
	    //Print the error
	    pthread_exit(NULL);
	}

	wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
	mvwprintw(par->playchance,1,1,"       OPPONENT %d PLAYING        ",d.opp);
	wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
	update_panels();
	doupdate();


	if(d.com=='n'||d.com=='y'||d.com=='t')
	{
	    //Stike the number if not 0 
	    if(d.num!=0)
	    {
		search_strike(par->get.array,d.num,&posx,&posy);
		if(posx!=-1)
		{
		    par->get.array[posx][posy] = 0;
		    //	player_bingo+=bingos(par->get.array,posx,posy);
		    bingodisp(par->bingocnt,d.bng);		//to display no of bingos completed



		    if(posx==par->get.x&&posy==par->get.y)
		    {
			wattron(par->get.bingo[posx][posy],A_STANDOUT|COLOR_PAIR(3));
			mvwprintw(par->get.bingo[posx][posy],2,3,"X ");
			wattroff(par->get.bingo[posx][posy],A_STANDOUT|COLOR_PAIR(3));
		    }
		    else
		    {
			wattron(par->get.bingo[posx][posy],COLOR_PAIR(3));
			mvwprintw(par->get.bingo[posx][posy],2,3,"X ");
			wattroff(par->get.bingo[posx][posy],COLOR_PAIR(3));
		    }
		    update_panels();
		    doupdate();
		}

	    }//d.num!=0 if close

	    //strike the number on the screen (ncurses)

	    if(d.com=='y')
	    {
		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
		mvwprintw(par->playchance,1,1,"       YOU ARE PLAYING     ");
		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD); 
		update_panels();
		doupdate();
		//and play your chance

		/*
		   par->get.done=0;
		   par->get.get=1;		//asks for user data
		   for(cntr=0;cntr<10;cntr++)
		 */
		pthread_mutex_unlock(&par->get.get_m);
		if(timedwait_cond(&par->get.done,&par->get.done_mutex,10)==0)
		{
		    pthread_mutex_lock(&par->get.get_m);
		    // sleep(1);
		    // if(par->get.done==1)		//number received
		    // {

		    d.com = 'c'; 	//sending
		    d.num = par->get.array[par->get.p][par->get.q];
		    write(par->sersd,&d,sizeof(data));
		    par->get.array[par->get.p][par->get.q] = 0;
		    //		    player_bingo+=bingos(par->get.array,par->get.p,par->get.q);

		    bingodisp(par->bingocnt,d.bng);

		    if(par->get.p==par->get.x&&par->get.q==par->get.y)
		    {
			wattron(par->get.bingo[par->get.p][par->get.q],A_STANDOUT|COLOR_PAIR(3));
			mvwprintw(par->get.bingo[par->get.p][par->get.q],2,3,"X ");
			wattroff(par->get.bingo[par->get.p][par->get.q],A_STANDOUT|COLOR_PAIR(3));
		    }
		    else
		    {
			wattron(par->get.bingo[par->get.p][par->get.q],COLOR_PAIR(3));
			mvwprintw(par->get.bingo[par->get.p][par->get.q],2,3,"X ");
			wattroff(par->get.bingo[par->get.p][par->get.q],COLOR_PAIR(3));
		    }
		    //screen change (curses)
		    //	break;
		    //  }//if close
		}//if close

		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
		mvwprintw(par->playchance,1,1,"       OPPONENT %d PLAYING        ",d.opp);
		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);

		update_panels();
		doupdate();
	    }//d.com==y if close

	    pthread_mutex_trylock(&par->get.get_m);

	    if(d.com=='t')
	    {
		if(d.bng>4)
		{
		    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		    mvwprintw(par->playchance,1,1,"       YOU WON!!!!!        ");
		    wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
		    update_panels();
		    doupdate();
		    sleep(2);
		    pthread_cancel(par->getid);
		    end_game_flag = 1;
		    pthread_exit(NULL);

		}

		else
		{
		    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		    mvwprintw(par->playchance,1,1,"       YOU LOST           ");
		    wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
		    update_panels();
		    doupdate();		sleep(2);
		    pthread_cancel(par->getid);
		    end_game_flag = 2;
		    pthread_exit(NULL);

		}

	    }
	}//d.com multiple case if close

    }//while close

}//func close
