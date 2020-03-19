#include"Bingo_Header.h"
/* This Function is used only in vs_comp.
 * This Function manages the movement of the highlighted
 * number in the bingo grid and also sees whether the user wants
 * to exit the game by pressing 'q'.
 * This function uses getch and manages arrow keys, enter and 'q'
 * and ignores everything else.
 */
int get_key(WINDOW *bingo[5][5],int *x,int *y,int array[5][5])
{
    /*bingo is a matrix of order 5*5 of type WINDOW*, is used for printing
     * the matrix of numbers from array onto it.
     * x and y are pointers of the variables containing the x and y co-ordinates
     * of the highlighted position on grid.
     */
    int ch;
    init_pair(9,COLOR_YELLOW,COLOR_BLACK);
    while((ch=getch())!='q')
    {
	switch(ch)
	{
	    /********************************************************************/
	    case KEY_UP:

		if(array[*x][*y]==0)		// Prints 'X' if the number there is 0
		{
		    wattron(bingo[*x][*y],A_BOLD|COLOR_PAIR(9));
		    mvwprintw(bingo[*x][*y],2,3,"X ");
		    wattroff(bingo[*x][*y],A_BOLD|COLOR_PAIR(9));
		}
		else				// else Prints the number normally
		{
		    wattron(bingo[*x][*y],A_NORMAL);
		    mvwprintw(bingo[*x][*y],2,3,"%d",array[*x][*y]);
		    wattroff(bingo[*x][*y],A_NORMAL);
		}

		/*********************************************************************/

		--*x;			// Since, key up came we have to move up.
		if(*x<0)		// If the variable x is out of bounds then get it back.
		    *x=4;
		/********************************************************************/

		if(array[*x][*y]==0)
		{
		    wattron(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));
		    mvwprintw(bingo[*x][*y],2,3,"X ");
		    wattroff(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));
		}
		else
		{
		    wattron(bingo[*x][*y],A_STANDOUT);
		    mvwprintw(bingo[*x][*y],2,3,"%d",array[*x][*y]);
		    wattroff(bingo[*x][*y],A_STANDOUT);
		}


/*************************************************************************************/
		break;

	    case KEY_DOWN:

		/***********************************************************************/
		if(array[*x][*y]==0)
		{
		    wattron(bingo[*x][*y],A_BOLD|COLOR_PAIR(9));
		    mvwprintw(bingo[*x][*y],2,3,"X ");
		    wattroff(bingo[*x][*y],A_BOLD|COLOR_PAIR(9));
		}
		else
		{
		    wattron(bingo[*x][*y],A_NORMAL);
		    mvwprintw(bingo[*x][*y],2,3,"%d",array[*x][*y]);
		    wattroff(bingo[*x][*y],A_NORMAL);
		}
/*************************************************************************************/
		++*x;
		if(*x>4)
		    *x=0;
		/********************************************************************/
		if(array[*x][*y]==0)
		{
		    wattron(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));
		    mvwprintw(bingo[*x][*y],2,3,"X ");
		    wattroff(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));
		}
		else
		{
		    wattron(bingo[*x][*y],A_BOLD|A_STANDOUT);
		    mvwprintw(bingo[*x][*y],2,3,"%d",array[*x][*y]);
		    wattroff(bingo[*x][*y],A_BOLD|A_STANDOUT);
		}
/****************************************************************************************/

		break;

	    case KEY_LEFT:
/**************************************************************************************/
		if(array[*x][*y]==0)
		{
		    wattron(bingo[*x][*y],A_BOLD|COLOR_PAIR(9));
		    mvwprintw(bingo[*x][*y],2,3,"X ");
		    wattroff(bingo[*x][*y],A_BOLD|COLOR_PAIR(9));
		}
		else
		{
		    wattron(bingo[*x][*y],A_NORMAL);
		    mvwprintw(bingo[*x][*y],2,3,"%d",array[*x][*y]);
		    wattroff(bingo[*x][*y],A_NORMAL);
		}

/*****************************************************************************************/

		--*y;
		if(*y<0)
		    *y=4;
		/************************************************************************/

		if(array[*x][*y]==0)
		{
		    wattron(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));
		    mvwprintw(bingo[*x][*y],2,3,"X ");
		    wattroff(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));
		}
		else
		{
		    wattron(bingo[*x][*y],A_STANDOUT);
		    mvwprintw(bingo[*x][*y],2,3,"%d",array[*x][*y]);
		    wattroff(bingo[*x][*y],A_STANDOUT);
		}

/*********************************************************************************************/
		break;

	    case KEY_RIGHT:
		/**************************************************************************/
		if(array[*x][*y]==0)
		{
		    wattron(bingo[*x][*y],A_BOLD|COLOR_PAIR(9));
		    mvwprintw(bingo[*x][*y],2,3,"X ");
		    wattroff(bingo[*x][*y],A_BOLD|COLOR_PAIR(9));
		}
		else
		{
		    wattron(bingo[*x][*y],A_NORMAL);
		    mvwprintw(bingo[*x][*y],2,3,"%d",array[*x][*y]);
		    wattroff(bingo[*x][*y],A_NORMAL);
		}
/*********************************************************************************************/

		++*y;
		if(*y>4)
		    *y=0;
/*********************************************************************************************/
		if(array[*x][*y]==0)
		{
		    wattron(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));
		    mvwprintw(bingo[*x][*y],2,3,"X ");
		    wattroff(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));
		}
		else
		{
		    wattron(bingo[*x][*y],A_STANDOUT);
		    mvwprintw(bingo[*x][*y],2,3,"%d",array[*x][*y]);
		    wattroff(bingo[*x][*y],A_STANDOUT);
		}
/*********************************************************************************************/


		break;

	    case 10:	// When enter is pressed
/*********************************************************************************************/
		if(array[*x][*y]==0)	// If the number is already 0 then there is nothing to do
		    continue;
		// else change that position on grid to 'X'
		wattron(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));
		mvwprintw(bingo[*x][*y],2,3,"X ");
		wattroff(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));

		update_panels();
		doupdate();
		return 0;
	}
	update_panels();	// Refresh the screen
	doupdate();

    }
    return 1;

}
