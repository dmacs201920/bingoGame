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

    init_pair(1,COLOR_BLUE,COLOR_BLUE);		
    init_pair(2,COLOR_YELLOW,COLOR_BLACK);
    init_pair(3,COLOR_CYAN,COLOR_BLACK);
    init_pair(4,COLOR_RED,COLOR_BLACK);
    init_pair(5,COLOR_CYAN,COLOR_CYAN);
    init_pair(6,COLOR_GREEN,COLOR_BLACK);
    init_pair(7,COLOR_MAGENTA,COLOR_BLACK);

    WINDOW *menu,*title;
    PANEL *pan[2];
    if((menu = newwin(20,50,6,50))==NULL)
    {
	perror("WINDOW CREATE ERROR\n");
	exit(1);
    }
    if((title = newwin(5,50,2,50))==NULL)
    {
	delwin(menu);
	perror("WINDOW CREATE ERROR\n");
	exit(2);
    }
    if((pan[0] = new_panel(menu))==NULL)
    {

	delwin(menu);
	delwin(title);
	perror("PANEL CREATE ERROR\n");
	exit(1);

    }
    if((pan[1] = new_panel(title))==NULL)
    {
	del_panel(pan[0]);
	delwin(menu);
	delwin(title);
	perror("PANEL CREATE ERROR\n");
	exit(1);

    }
    Print_MainMenu(menu,title,choice);

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
			hide_panel(pan[0]);
			hide_panel(pan[1]);
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

			break;

		    case 1:
			hide_panel(pan[0]);
			hide_panel(pan[1]);
			clear();
			refresh();

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

			break;

		    case 2:
			clear();
			refresh();
			hide_panel(pan[0]);
			hide_panel(pan[1]);
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

			break;
		    case 3:
			clear();
			refresh();
			how_to_play();

			break;

		    case 4:
			clear();
			refresh();
			about();

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
		show_panel(pan[0]);
		show_panel(pan[1]);
	}

	Print_MainMenu(menu,title,choice);

    }

}
