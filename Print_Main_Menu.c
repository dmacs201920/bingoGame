#include"Bingo_Header.h"

char list[6][25] = {"\tVS COMPUTER","\tSTART A SERVER","\tCONNECT TO A SERVER", "\tHOW TO PLAY", "\tABOUT", "\tQUIT GAME" };
char head[20] = "THE BINGO";
int n_choices = 6;


void Print_MainMenu(WINDOW *main_menu,WINDOW *title,PANEL *pan[2], int highlight)
{
    int x = 2,i;

    wattron(main_menu,COLOR_PAIR(5)|A_REVERSE);
    wattron(title,COLOR_PAIR(5)|A_REVERSE);

    wborder(title,'|','|','-','-','+','+','+','+');	
    wborder(main_menu,'x','x',' ','x',' ',' ','+','+');	

    wattroff(main_menu,COLOR_PAIR(5)|A_REVERSE);
    wattroff(title,COLOR_PAIR(5)|A_REVERSE);
    ////////////////////////////////////////////////////////////////////////////////
    wattron(title,COLOR_PAIR(4)|A_BOLD|A_UNDERLINE);

    mvwprintw(title,2,20,"%s",head);

    wattroff(title,COLOR_PAIR(4)|A_BOLD|A_UNDERLINE);



    for(i=0;i<n_choices;++i)
    {
	if(i==highlight)
	{
	    wattron(main_menu,A_STANDOUT);
	    mvwprintw(main_menu, i+1, x, "%s", list[i]);
	    wattroff(main_menu,A_STANDOUT);

	}
	else
	    mvwprintw( main_menu, i+1, x, "%s", list[i]);

    }    
    update_panels();
    doupdate();
}
