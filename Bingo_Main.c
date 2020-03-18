/*
 * This is the main function oile of the Bingo game.
 * This one manages the call to Print_MainMenu.
 */
#include"Bingo_Header.h"
int end_game_flag=0;
void main() 
{
    pthread_setconcurrency(25);
    char *err = NULL;
    initscr(); 
    cbreak(); 
    start_color();
    int c;
    int choice = 0;

    init_pair(1,COLOR_BLUE,COLOR_BLUE);			//INITIALISING ARGUMENT 1 WITH THE COLOR PAIR
    init_pair(2,COLOR_YELLOW,COLOR_BLACK);
    init_pair(3,COLOR_CYAN,COLOR_BLACK);
    init_pair(4,COLOR_RED,COLOR_BLACK);
    init_pair(5,COLOR_CYAN,COLOR_CYAN);
    WINDOW *menu,*title;
    PANEL *pan[2];
    menu = newwin(20,50,6,50);
    title = newwin(5,50,2,50);
    pan[0] = new_panel(menu);
    pan[1] = new_panel(title);
    Print_MainMenu(menu,title,pan,choice);

    keypad( stdscr , TRUE ); // enable keyboard input for the window.
    noecho();
    curs_set(0);
    while(c = getch())
    {
	switch(c)
	{

	    case KEY_DOWN:
		choice++;
		choice = (choice>5) ? 0:choice;
		break;

	    case KEY_UP:
		choice--;
		choice = (choice<0) ? 5:choice;
		break;

	    case 10:
		switch(choice)
		{
		    case 0:
			clear();
			refresh();
			vs_comp(&err);
			wattron(menu,COLOR_PAIR(4));
			if(err!=NULL)
			{
			    mvwprintw(menu,15,2,"ERROR:%s",err);		
			}
			else
			{
			    mvwprintw(menu,15,2,"                                         ");
			}
			wattroff(menu,COLOR_PAIR(4));

			clear();
			break;
		    case 1:
			clear();
			refresh();
			del_panel(pan[1]);
			del_panel(pan[0]);
			start_server(&err);
			wattron(menu,COLOR_PAIR(4));
			if(err!=NULL)
			{
			    mvwprintw(menu,15,2,"ERROR:%s",err);		
			}
			else
			{
			    mvwprintw(menu,15,2,"                                         ");
			}
			wattroff(menu,COLOR_PAIR(4));

			pan[0] = new_panel(menu);
			pan[1] = new_panel(title);
			clear();
			break;
		    case 2:
			clear();
			refresh();
			connect_to_server(&err);
			wattron(menu,COLOR_PAIR(4));
			if(err!=NULL)
			{
			    mvwprintw(menu,15,2,"ERROR:%s",err);		
			}
			else
			{
			    mvwprintw(menu,15,2,"                                         ");
			}
			wattroff(menu,COLOR_PAIR(4));
			clear();
			break;

		    case 5:
			del_panel(pan[0]);
			delwin(menu);
			del_panel(pan[1]);
			delwin(title);
			endwin();
			exit(0);
			break;


		}
	}

	Print_MainMenu(menu,title,pan,choice);

    }

}
