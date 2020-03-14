#include"Bingo_Header.h"

int get_key(WINDOW *bingo[5][5],int *x,int *y,int array[5][5])
{
    int ch;
    int flag;
    init_pair(9,COLOR_YELLOW,COLOR_BLACK);
    while((ch=getch())!='q')
    {
	switch(ch)
	{
	    case KEY_UP:

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

		--*x;
		if(*x<0)
		    *x=4;
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



		break;

	    case KEY_DOWN:

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

		++*x;
		if(*x>4)
		    *x=0;
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


		break;

	    case KEY_LEFT:

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

		--*y;
		if(*y<0)
		    *y=4;
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


		break;

	    case KEY_RIGHT:
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

		++*y;
		if(*y>4)
		    *y=0;
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


		break;

	    case 10:
		if(array[*x][*y]==0)
		    continue;

		wattron(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));
		mvwprintw(bingo[*x][*y],2,3,"X ");
		wattroff(bingo[*x][*y],A_BOLD|A_STANDOUT|COLOR_PAIR(9));

		update_panels();
		doupdate();
		return 0;
	}
	update_panels();
	doupdate();

    }
    return 1;

}
