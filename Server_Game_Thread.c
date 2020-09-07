#include"Bingo_Header.h"
/*
 * This thread manages the server side of the game.
 * Server contains details of all the clients.
 * It has the bingo count, their bingo array and all that in a Circular Double Linked List.
 * The node pointer Current_player determines who is the current player.
 * Head of the list is the server.
 */
extern int end_game_flag;
void* serv_game_t(void* arg)
{
    game_p *par=arg;
    pthread_mutex_lock(&par->get.get_m);	// Locks the input from get_key
    print_array(par->get.bingo,par->get.array,par->get.x,par->get.y);	// Prints the array
    char* err=NULL;		// Initializes error variable
    data d;
    int i,j,status,t1,t2;	// i,j,t1 & t2 are all counter variables
    node *Current_player=par->get.pl.l.h,*tr;		// tr is a temorary pointer, Current_player is initialized to head

    int flag=0;		// Bingo count >4 flag is initialized
/******************************************************************************************************/
    wattron(stdscr,COLOR_PAIR(2)|A_BOLD);
    mvwprintw(stdscr,29,70,"(PRESS 'q' TO QUIT GAME)");
    wattroff(stdscr,COLOR_PAIR(2)|A_BOLD);
/**************************** Game Starts Here ********************************************************************/
    while(Current_player!=Current_player->n)
    {
/****************************If the current player is server ******************************************************/
	if(Current_player==par->get.pl.l.h)
	{
	    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
	    mvwprintw(par->playchance,1,1,"                                     ");
	    mvwprintw(par->playchance,1,1,"YOU ARE PLAYING!!!");
	    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD); 
	    update_panels();
	    doupdate();
/******************************************************************************************************************/
	    pthread_mutex_unlock(&par->get.get_m);	// Let get_key thread put selected number's co-ordinates into par->get.p and par->get.q
	    if(timedwait_cond(&par->get.done,&par->get.done_mutex,10)==0) // Waits for 10 seconds for the user to enter data
	    {
		pthread_mutex_lock(&par->get.get_m);		// Sets d.num as the number entered.
		d.num=par->get.array[par->get.p][par->get.q];
	    }
	    else		//OF TIMED WAIT		// else sets d.num as 0, implying that the player has not played
	    {
		pthread_mutex_lock(&par->get.get_m);
		d.num=0;
	    }
/******************************************************************************************************************/
	}
/******************************* Current player is a client *******************************************************/
	else
	{
/******************************************************************************************************************/
	    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
	    mvwprintw(par->playchance,1,1,"                                            ");
	    mvwprintw(par->playchance,1,1,"OPPONENT %d IS PLAYING",((player*)Current_player->d)->plid);
	    wattron(par->playchance,COLOR_PAIR(2)|A_BOLD); 
	    update_panels();
	    doupdate();
/******************************************************************************************************************/
	    if((status=timed_recv(((player*)Current_player->d)->sd,&d,sizeof(data),0,10))!=sizeof(data))	// Wait for 10 second for the client to give the number
	    {
/********************* If it wasn't time out ( -3 means time out) *************************************************/
		if(status!=-3)
		{
/************************* Remove the player from the list*********************************************************/
		    tr = Current_player->p;
		    close(((player*)Current_player->d)->sd);
		    --(par->get.pl.n);
		    Current_player->n->p = Current_player->p;
		    Current_player->p->n = Current_player->n;
		    free(Current_player->d);
		    free(Current_player);

		    Current_player = tr;
		}
/************************* Since the player hasn't chosen a number, d.num=0***************************************/
		d.num=0;
	    }
	}
/*************************** When the data was entered ************************************************************/
	if(d.num!=0)
	{
	    tr = Current_player;
	    /*************************** Strike the number for all the players and update their bingo count*********************************************************************/
	    search_strike(par->get.array,d.num,&i,&j);	// Strike for server
	    if(i==-1)	// If the number is invalid set d.num to zero and break from loop
	    {
		d.num=0;
	    }
	    else
	    {
		par->get.array[i][j] = 0;
		par->get.x = i;
		par->get.y = j;

		if((((player*)par->get.pl.l.h->d)->bngcnt+=bingos(par->get.array,i,j))>4)
		    flag=1;
		do
		{
		    if(tr != par->get.pl.l.h)
		    {
			search_strike(((player*)tr->d)->array,d.num,&i,&j);
			((player*)tr->d)->array[i][j] = 0;
			if((((player*)tr->d)->bngcnt+=bingos(((player*)tr->d)->array,i,j))>4)
			    flag=1;
		    }
		    tr = tr->n;
		}while(tr!=Current_player);
	    /******************************************************************************************************************/
	    /********* display bingo grid and count****************************************************************************/
	    bingodisp(par->bingocnt,((player*)par->get.pl.l.h->d)->bngcnt);
	    print_array(par->get.bingo,par->get.array,par->get.x,par->get.y);
	    }
	}
/****************** When game is not done ************************************************************************************************/
	if(flag!=1)
	{
/******************* Send to all clients the player id of the next player******************************************/
	    tr=Current_player->n;
	    d.com='y';			// Means you are the next player
	    d.opp=((player*)tr->d)->plid;	// Next player's player id
	    d.bng=((player*)tr->d)->bngcnt;	// Bingo count of that player
	    if(tr!=par->get.pl.l.h)		// Send to the next player that it's next
		send(((player*)tr->d)->sd,&d,sizeof(data),0);
	    d.com='n';		// Means you are not the next player
/***************** Send to all their bingo count and number to strike *********************************************/
	    for(tr=tr->n;tr!=Current_player->n;tr=tr->n)
		if(tr!=par->get.pl.l.h)
		{
		    d.bng=((player*)tr->d)->bngcnt;
		    send(((player*)tr->d)->sd,&d,sizeof(data),0);
		}
/************************ Change current player ******************************************************************************************/
	    Current_player = Current_player->n;
	}
	else
	{
/************* Game is done ***************************************************************************************/
	    d.com='t';	// t means terminate game
	    tr=Current_player;
/***************** Send all clients their bingo counts and number to strike ******************************************************************************************/
	    do
	    {
		if(tr!=par->get.pl.l.h)
		{
		    d.bng=((player*)tr->d)->bngcnt;
		    send(((player*)tr->d)->sd,&d,sizeof(data),0);
		}
		tr=tr->n;
	    }while(tr!=Current_player);
/******************************************************************************************************************/

/***************************** Print whether the server is a winner or not ****************************************/
	    if(((player*)par->get.pl.l.h->d)->bngcnt>4)
	    {
		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		mvwprintw(par->playchance,1,1,"                                     ");
		mvwprintw(par->playchance,1,1,"YOU WON!!!!!                          ");
		mvwprintw(par->playchance,2,1,"PRESS ANY KEY TO CONTINUE...");
		wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
	    }
	    else
	    {
		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
		mvwprintw(par->playchance,1,1,"                                     ");
		mvwprintw(par->playchance,1,1,"YOU LOST                             ");
		mvwprintw(par->playchance,2,1,"PRESS ANY KEY TO CONTINUE...");
		wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
	    }
/******************************************************************************************************************/
	    update_panels();
	    doupdate();
	    sleep(2);
	    pthread_cancel(par->getid);
	    getch();
	    if(((player*)par->get.pl.l.h->d)->bngcnt>4)
		end_game_flag = 1;
	    else
		end_game_flag = 2;

	    pthread_exit(NULL);
	}//else close of flag!=1

    }//if(current_player!=head ) close
/******************************************************************************************************************/
    err="No other player playing";
    pthread_cancel(par->getid);
    end_game_flag=3;
    pthread_exit(err);
}
