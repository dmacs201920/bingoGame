#include"Bingo_Header.h"
void vs_comp(char **err)
{
    int player[5][5],comp[5][5],x=0,y=0,temp,p=0,q=0,i,j,t1,t2;
    fill_bingo(player);					//FILLS THE GAME ARRAY FOR THE USER
    fill_bingo(comp);					//FILLS THE GAME ARRAY FOR THE COMPUTER
    int player_bingo=0,comp_bingo=0;			//COUNTS THE NUMBER OF ROWS,COLS AND DIAGONALS FINISHED

    int ch,flag;

    int row,col;
/************************************ Creates window and panels for bingo game grid *******************************/
    WINDOW *bingo[5][5],*playchance,*bingocnt;		//BINGO IS FOR DISPLAYING THE ARRAY NUMBERS
    //PLAYCHANCE FOR DISPLAYING WHO'S CHANCE IT IS
    //BINGOCNT IS FOR DISPLAYING THE THE NUMBER OF ROWS,COLS AND DIAGONALS COMPLETED
    PANEL *pan[5][5],*chancepan,*bingcnt;



    playchance = newwin(nline,ncols,startx-nline-1,starty);		//CREATES THE WINDOW AND RETURNS A POINTER TO THE PLAYCHANCE
    if(playchance==NULL)				
    {
	*err="Unable to create WINDOW";				//ERROR MSG
	return;
    }

    chancepan = new_panel(playchance);			//CREATES THE PANEL AND RETURN THE POINTER TO CHANCEPAN
    if(chancepan==NULL)				
    {
	delwin(playchance);
	*err="Unable to create PANEL";				//ERROR MSG
	return;
    }

    bingocnt = newwin(60,3,startx+2,starty-5);
    if(bingocnt==NULL)				
    {
	del_panel(chancepan);
	delwin(playchance);

	*err="Unable to create WINDOW";				//ERROR MSG
	return;
    }

    bingcnt = new_panel(bingocnt);
    if(bingcnt==NULL)				
    {
	del_panel(chancepan);
	delwin(playchance);

	delwin(bingocnt);
	*err="Unable to create PANEL";				//ERROR MSG
	return;
    }

    ////////////////////////////////////////////////////		CREATING BINGO WINDOWS AND PANELS    


    for(i=0;i<5;i++)
    {
	for(j=0;j<5;j++)
	{


	    bingo[i][j] = newwin(width,length,startx+down*i,starty+right*j);
	    if(bingo[i][j]==NULL)
	    {
		del_panel(chancepan);
		delwin(playchance);

		del_panel(bingcnt);
		delwin(bingocnt);

		for(t1=0;t1<=i;++t1)
		    for(t2=0;t2<5;++t2)
		    {
			if(t1==i&&t2==j)
			    break;
			delwin(bingo[t1][t2]);
		    }
		*err="Unable to create WINDOW";				//ERROR MSG
		return;
	    }
	    pan[i][j] = new_panel(bingo[i][j]);
	    if(pan[i][j]==NULL)
	    {
		del_panel(chancepan);
		delwin(playchance);
		del_panel(bingcnt);
		delwin(bingocnt);
		for(t1=0;t1<5;t1++)
		    for(t1=0;t1<5;t1++)
			delwin(bingo[i][j]);
		for(t1=0;t1<=i;++t1)
		    for(t2=0;t2<5;++t2)
		    {
			if(t1==i&&t2==j)
			    break;
			del_panel(pan[t1][t2]);
		    }

		*err="Unable to create PANEL";				//ERROR MSG
		return;
	    }

	    wattron(bingo[i][j],COLOR_PAIR(1)|A_REVERSE);		//ENABLES ATTRIBUTES IN THE ARGUMENTS


	    wborder(bingo[i][j],'|','|','-','-','+','+','+','+');	//FOR BORDERING THE WINDOW

	    wattroff(bingo[i][j],COLOR_PAIR(1)|A_REVERSE);		//DISABLES ATTRIBUTES IN THE ARGUMENTS

	    mvwprintw(bingo[i][j],2,3,"%d",player[i][j]);		//MOVES TO THE REQ POSITION AND PRINTS IN THE WINDOW

	}
    }

/******************************************************************************************************************/


    wattron(bingo[0][0],A_STANDOUT);
    mvwprintw(bingo[0][0],2,3,"%d",player[0][0]);		// Highlights the first position on the grid
    wattroff(bingo[0][0],A_STANDOUT);
    update_panels();	
    doupdate();				//REFRESHES ALL THE PANELS IN ORDER REQUIRED

/******************************************************************************************************************/

    wattron(stdscr,COLOR_PAIR(4));
    mvwprintw(stdscr,29,70,"   PRESS 'q' TO EXIT GAME  ");
    wattroff(stdscr,COLOR_PAIR(4));
/******************************************************************************************************************/
/************************** Game starts now************************************************************************/
    while(player_bingo<5&&comp_bingo<5)
    {
/************************* Firs is the user's chance **************************************************************/
	wattron(playchance,COLOR_PAIR(2));
	mvwprintw(playchance,1,1,"   YOU ARE PLAYING  ");
	wattroff(playchance,COLOR_PAIR(2));
	update_panels();
	doupdate();
/******************************************************************************************************************/
	if(get_key(bingo,&x,&y,player)==1)			//GETS READY FOR INPUT FORM USER
	{	
	    	// If error Deletes every thing end exits.

	    for(i=0;i<5;++i)
		for(j=0;j<5;++j)
		{
		    del_panel(pan[i][j]);
		    delwin(bingo[i][j]);
		}
	    del_panel(chancepan);
	    delwin(playchance);
	    del_panel(bingcnt);
	    delwin(bingocnt);
	    return;
	}
	search_strike(comp,player[x][y],&i,&j);			//STRIKES THE NUMBER FOR COMPUTER GIVEN FROM THE USER
	player[x][y] = 0;					// Stiking is actually making it zero
	player_bingo+=bingos(player,x,y);			// Increments bingo count for player
	comp_bingo+=bingos(comp,i,j);				//INCREMENTS THE BINGO COUNT IF ANY ROW,COL OR DIAGONAL IS COMPLETE
/******************************************************************************************************************/
	if(i==-1)				// Means the number does not exist
	{
	    mvwprintw(playchance,1,1,"    ERROR!!!       ");
	    update_panels();
	    doupdate();
	    sleep(2);

	    for(i=0;i<5;++i)
		for(j=0;j<5;++j)
		{
		    del_panel(pan[i][j]);
		    delwin(bingo[i][j]);
		}
	    del_panel(chancepan);
	    delwin(playchance);
	    del_panel(bingcnt);
	    delwin(bingocnt);
	    return;
	}
/******************************************************************************************************************/
	bingodisp(bingocnt,player_bingo);		// Displays the BINGO word in accordence with bingo count
/*************************************** Computes Chance***********************************************************/
	mvwprintw(playchance,1,1,"COMPUTER IS PLAYING");
	//Print Comp is playing
	update_panels();
	doupdate();
	sleep(1);
/*************************** Finds a number in it's array which is non zero ***************************************/
	while(comp[p][q]==0)
	{
	    ++q;
	    if(q==5)
	    {
		++p;
		q=0;
	    }
	}
/******************************* Strike s that non-zeor number for both *******************************************/
	search_strike(player,comp[p][q],&i,&j);
	comp[p][q]=0;
	comp_bingo+=bingos(comp,p,q);
	player_bingo+=bingos(player,i,j);
	bingodisp(bingocnt,player_bingo);
	if(i==-1)
	{
	    mvwprintw(playchance,1,1,"    ERROR!!!       ");
	    update_panels();
	    doupdate();
	    sleep(2);
	    for(i=0;i<5;++i)
		for(j=0;j<5;++j)
		{
		    del_panel(pan[i][j]);
		    delwin(bingo[i][j]);
		}
	    del_panel(chancepan);
	    delwin(playchance);
	    del_panel(bingcnt);
	    delwin(bingocnt);
	    return;
	}
/******************************************************************************************************************/
	if(i!=x||j!=y)		// Checks whether not to highlight that position or not
	{
	    wattron(bingo[i][j],A_BOLD|COLOR_PAIR(3));
	    mvwprintw(bingo[i][j],2,3,"%s","X ");		//to hide comp number
	    wattron(bingo[i][j],A_BOLD|COLOR_PAIR(3));
	}
	else			// else just print it with hichlight
	{
	    wattron(bingo[i][j],A_BOLD|A_STANDOUT|COLOR_PAIR(3));
	    mvwprintw(bingo[i][j],2,3,"%s","X ");		//to hide comp number
	    wattron(bingo[i][j],A_BOLD|A_STANDOUT|COLOR_PAIR(3));
	}
/******************************************************************************************************************/

	update_panels();
	doupdate();
    }
/*************************** Checks whether some one won or not ***************************************************/

/******************* It's a draw **********************************************************************************/
    if(player_bingo>4&&comp_bingo>4)
    {
	wattron(playchance,COLOR_PAIR(3));
	mvwprintw(playchance,1,1,"  Press any key to exit  ");
	mvwprintw(playchance,2,1,"      IT'S A DRAW!!     ");
	wattroff(playchance,COLOR_PAIR(3));
    }
/********************* Computer won *********************************************************************************************/
    else if(comp_bingo>4)
    {
	wattron(playchance,COLOR_PAIR(3));
	mvwprintw(playchance,1,1,"  Press any key to exit  ");
	mvwprintw(playchance,2,1,"	 COMPUTER WON!?!  ");
	wattroff(playchance,COLOR_PAIR(3));
    }
/****************** Player won ************************************************************************************/
    else
    {    
	wattron(playchance,COLOR_PAIR(3));
	mvwprintw(playchance,1,1,"  Press any key to exit  ");
	mvwprintw(playchance,2,1,"	 YOU WON!!  ");
	wattroff(playchance,COLOR_PAIR(3));
    }
/******************************************************************************************************************/
    update_panels();
    doupdate();
    sleep(2);
    getch();
/********************** Makes a clean exit ************************************************************************/
    for(i=0;i<5;++i)
	for(j=0;j<5;++j)
	{
	    del_panel(pan[i][j]);
	    delwin(bingo[i][j]);
	}
    del_panel(chancepan);
    delwin(playchance);
    del_panel(bingcnt);
    delwin(bingocnt);
/******************************************************************************************************************/
}
