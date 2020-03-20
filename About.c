#include"Bingo_Header.h"
void about()
{
    attron(COLOR_PAIR(2));
    mvwprintw(stdscr,1,58,"AUM SRI SAI RAM\n\n");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(6));
    mvwprintw(stdscr,3,58,"ABOUT THE GAME\n\n");
    attroff(COLOR_PAIR(6));

    attron(COLOR_PAIR(3));
    printw(" Works through inter process communication under the same computer\n\n");
    printw(" This is a multi-threaded program using sockets and ncurses.\n\n\n\n");
    printw("Developed @ \n\tComputer Lab of Sri Sathya Sai Institute of Higher Learning, Brindavan Campus\n");
    printw("\n\n\n\nUnder the guidence of Darshan Gera and few alumni.\n\n\n\n");
    printw(" By Sai Vignesh S. and Sai Aravind S.V.\n\n");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(4));
    printw("\n\nPRESS q TO RETURN TO MAIN MENU\n");
    attroff(COLOR_PAIR(4));

    refresh();
    while(getch()!='q');
}
