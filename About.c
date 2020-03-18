#include"Bingo_Header.h"
void about()
{
    attron(COLOR_PAIR(2));
    mvwprintw(stdscr,1,65,"AUM SRI SAI RAM\n\n");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(6));
    mvwprintw(stdscr,3,65,"ABOUT THE GAME\n\n");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(3));
    printw("This program was created in the year 2020\n\n");
    printw("By Sai Vignesh S. and Sai Aravind S.V.\n\n");
    printw("Developed @ \n\tComputer Lab of Sri Sathya Sai Institute of Higher Learning, Brindavan Campus\n");
    printw("Under the guidence of Darshan Gera, our computer science professor,");
    printw("\nand all those people who helped us through this project");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(4));
    printw("\n\nPRESS q TO RETURN TO MAIN MENU\n");
    attroff(COLOR_PAIR(4));
    while(getch()!='q');
}
