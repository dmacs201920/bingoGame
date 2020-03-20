#include"Bingo_Header.h"
/*
 * Prints the array of numbers to the bingo window screen
 * with x,y as the coordinates to highlight.
 */
void print_array(WINDOW *bingo[5][5],int array[5][5],int x,int y)
{
    int i,j;
    for(i=0;i<5;++i)
    {
	for(j=0;j<5;++j)
	{
	    wattron(bingo[i][j],COLOR_PAIR(1)|A_REVERSE);		//ENABLES ATTRIBUTES IN THE ARGUMENTS


	    wborder(bingo[i][j],'|','|','-','-','+','+','+','+');	//FOR BORDERING THE WINDOW

	    wattroff(bingo[i][j],COLOR_PAIR(1)|A_REVERSE);		//DISABLES ATTRIBUTES IN THE ARGUMENTS

	    if(i!=x||j!=y)	// Checks whether to highlight the number or not.
	    {
		if(array[i][j]!=0)	// If the number is non-zero print it as it is.
		    mvwprintw(bingo[i][j],2,3,"%d",array[i][j]);
		else		// else the number is 0 print 'x'
		{
		    wattron(bingo[i][j],COLOR_PAIR(6));
		    mvwprintw(bingo[i][j],2,3,"X ");
		    wattroff(bingo[i][j],COLOR_PAIR(6));
		}
	    }
	    /***************** if the position is not highlighted  ******************/
	    else
	    {
		if(array[i][j]!=0)
		{	
		    wattron(bingo[i][j],A_STANDOUT);
		    mvwprintw(bingo[i][j],2,3,"%d",array[i][j]);
		    wattroff(bingo[i][j],A_STANDOUT);
		}
		else
		{
		    wattron(bingo[i][j],COLOR_PAIR(6)|A_STANDOUT);
		    mvwprintw(bingo[i][j],2,3,"X ");
		    wattroff(bingo[i][j],COLOR_PAIR(6)|A_STANDOUT);
		}

	    }
	}
    }
    update_panels();
    doupdate();
}
