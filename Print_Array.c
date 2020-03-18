#include"Bingo_Header.h"
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

	    if(i!=x||j!=y)
	    {
		if(array[i][j]!=0)
		    mvwprintw(bingo[i][j],2,3,"%d",array[i][j]);
		else
		{
		    wattron(bingo[i][j],COLOR_PAIR(3));
		    mvwprintw(bingo[i][j],2,3,"X ");
		    wattroff(bingo[i][j],COLOR_PAIR(3));
		}
	    }
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
		    wattron(bingo[i][j],COLOR_PAIR(3)|A_STANDOUT);
		    mvwprintw(bingo[i][j],2,3,"X ");
		    wattroff(bingo[i][j],COLOR_PAIR(3)|A_STANDOUT);
		}

	    }
	}
    }
    update_panels();
    doupdate();
}
