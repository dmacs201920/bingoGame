#include"Bingo_Header.h"
extern int end_game_flag;

/*
		FUNCTION THAT HANDLES THE GAME FOR THE CLIENT SIDE PLAYER.  THIS IS A THREAD FUNCTION.
*/

void* client_game_t(void *arg)
{
/*********************************************  INITIALIZATIONS OF VARIABLES  *********************************************************************/

    game_p *par = arg;
    data d={0,0,0,0};

    int posx,posy,cntr;

/**************************************************************************************************************************************************/

    pthread_mutex_lock(&par->get.get_m);		//LOCKS THE DATA SO THAT USER CANNOT ENTER NUMBER TILL IT IS HIS CHANCE

    
/*********************************************  INITIALIZATIONS OF SCREEN FOR CLIENT  **************************************************************/
    wattron(stdscr,COLOR_PAIR(4));
    mvwprintw(stdscr,29,70,"   PRESS 'q' TO EXIT GAME  ");
    wattroff(stdscr,COLOR_PAIR(4));
    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
    mvwprintw(par->playchance,1,1,"    WAITING FOR SERVER        ");
    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
    update_panels();
    doupdate();

/**************************************************************************************************************************************************/

    while(1)
    {
	if(recv(par->sersd,&d,sizeof(data),0)!=sizeof(data))	// SOCKET RECIEVE FUNCTION ERROR CHECK
	{
	    pthread_cancel(par->getid);
	    end_game_flag = 3;
	    pthread_exit("SERVER HAS EXITED");					//CLOSE THE REQUIRED AND EXIT FROM THE FUNCTION
	}

	wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
	mvwprintw(par->playchance,1,1,"       OPPONENT %d PLAYING        ",d.opp);
	wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
	bingodisp(par->bingocnt,d.bng);		//to display no of bingos completed
	update_panels();
	doupdate();

/**************************************************** CHECKS FOR THE INPUT MESSAGE *****************************************************************/
	if(d.com=='n'||d.com=='y'||d.com=='t')		// 'n' - OPPONENTS CHANCE, 'y' - YOUR CHANCE, 't' - TERMINATE GAME
	{
	    //Stike the number if not 0 
	    if(d.num!=0)
	    {
		search_strike(par->get.array,d.num,&posx,&posy);
		if(posx!=-1)				// WHEN THE POSITION IS VALID
		{
		    par->get.array[posx][posy] = 0;


/////////////////////////////////////////////////// SCREEN PRINTING OF THE STRIKED NUMBER///////////////////////////////////////////////////////////

		    print_array(par->get.bingo,par->get.array,posx,posy);
		    par->get.x = posx;
		    par->get.y = posy;
	/*	    if(posx==par->get.x&&posy==par->get.y)
		    {
			wattron(par->get.bingo[posx][posy],A_STANDOUT|COLOR_PAIR(6));
			mvwprintw(par->get.bingo[posx][posy],2,3,"X ");
			wattroff(par->get.bingo[posx][posy],A_STANDOUT|COLOR_PAIR(6));
		    }
		    else
		    {
			wattron(par->get.bingo[posx][posy],COLOR_PAIR(6));
			mvwprintw(par->get.bingo[posx][posy],2,3,"X ");
			wattroff(par->get.bingo[posx][posy],COLOR_PAIR(6));
		    }
		    update_panels();
		    doupdate();*/
		}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	    }//d.num!=0 if close

	    if(d.com=='y')
	    {
		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
		mvwprintw(par->playchance,1,1,"       YOU ARE PLAYING     ");
		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD); 
		update_panels();
		doupdate();

/*******************************************  UNLOCKING FO CLIENT TO ENTER DATA  ******************************************************************/
		pthread_mutex_unlock(&par->get.get_m);

		if(timedwait_cond(&par->get.done,&par->get.done_mutex,10)==0) // WAITS 10 SEC FOR THE USER DATA
		{
		    pthread_mutex_lock(&par->get.get_m);

		    d.com = 'c'; 	//sending
		    d.num = par->get.array[par->get.p][par->get.q];
		    write(par->sersd,&d,sizeof(data));
		    par->get.array[par->get.p][par->get.q] = 0;


/////////////////////////////////////////////////// SCREEN PRINTING OF THE STRIKED NUMBER///////////////////////////////////////////////////////////

		    
		    print_array(par->get.bingo,par->get.array,par->get.p,par->get.q);
/*		    if(par->get.p==par->get.x&&par->get.q==par->get.y)
		    {
			wattron(par->get.bingo[par->get.p][par->get.q],A_STANDOUT|COLOR_PAIR(6));
			mvwprintw(par->get.bingo[par->get.p][par->get.q],2,3,"X ");
			wattroff(par->get.bingo[par->get.p][par->get.q],A_STANDOUT|COLOR_PAIR(6));
		    }
		    else
		    {
			wattron(par->get.bingo[par->get.p][par->get.q],COLOR_PAIR(6));
			mvwprintw(par->get.bingo[par->get.p][par->get.q],2,3,"X ");
			wattroff(par->get.bingo[par->get.p][par->get.q],COLOR_PAIR(6));
		    }
   */
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}//if close
		else
		    pthread_mutex_lock(&par->get.get_m);		//DATA LOCKED, USER CANNOT ENTER


		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
		mvwprintw(par->playchance,1,1,"       OPPONENT %d PLAYING        ",d.opp);
		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);

		update_panels();
		doupdate();
	    }//d.com==y if close


	    if(d.com=='t')						//SERVER HAS SENT TERMINATE MESSAGE, IMPLIES GAME COMPLETE
	    {
		if(d.bng>4)
		{
		    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		    mvwprintw(par->playchance,1,1,"       YOU WON!!!!!                ");
		    mvwprintw(par->playchance,2,1,"PRESS ANY KEY TO CONTINUE...");
		    wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
		}

		else
		{
		    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		    mvwprintw(par->playchance,2,1,"PRESS ANY KEY TO CONTINUE...");
		    mvwprintw(par->playchance,1,1,"       YOU LOST                    ");
		    wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
		}
		update_panels();
		doupdate();
		sleep(2);
		pthread_cancel(par->getid);
		getch();
	
		if(d.bng>4)
		    end_game_flag = 1;					// SETTING END GAME FLAG
		else
		    end_game_flag = 2;
		pthread_exit(NULL);
	    }
	}//d.com multiple case if close

    }//while close

}//func close

