#include"Bingo_Header.h"
/*
 * list is an array of strings containing the names of all the main menu items.
 * head is a string printed on the title window.
 * n_choices contains the number of items on the main menu.
 *
 * This function takes a pointer of main menu window, title window and the choice
 * to highlight.
 */

#define head "THE BINGO"
#define n_choices  6
#define list_x 2

char list[6][25] = {"\tVS COMPUTER","\tSTART A SERVER","\tCONNECT TO A SERVER", "\tHOW TO PLAY", "\tABOUT", "\tQUIT GAME" };


void Print_MainMenu(WINDOW *main_menu,WINDOW *title, int highlight)
{
    int i;
    clear();
    refresh();
/****************** Prints the boader *****************************************/
    wattron(main_menu,COLOR_PAIR(5)|A_REVERSE);
    wattron(title,COLOR_PAIR(5)|A_REVERSE);

    wborder(title,'|','|','-','-','+','+','+','+');	
    wborder(main_menu,'x','x',' ','x',' ',' ','+','+');	

    wattroff(main_menu,COLOR_PAIR(5)|A_REVERSE);
    wattroff(title,COLOR_PAIR(5)|A_REVERSE);
/********************Prints title*************************************************/
    wattron(title,COLOR_PAIR(4)|A_BOLD|A_UNDERLINE);

    mvwprintw(title,2,20,"%s",head);

    wattroff(title,COLOR_PAIR(4)|A_BOLD|A_UNDERLINE);
/********************Prints those choices******************************************/

    for(i=0;i<n_choices;++i)
    {
	if(i==highlight)	// Checks whether to highlight the current choice or not.
	{
	    wattron(main_menu,A_STANDOUT);
	    mvwprintw(main_menu, i+1, list_x, "%s", list[i]);
	    wattroff(main_menu,A_STANDOUT);

	}
	else
	    mvwprintw( main_menu, i+1, list_x, "%s", list[i]);

    }    
    update_panels();
    doupdate();
}
