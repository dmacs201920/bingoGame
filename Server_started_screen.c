#include"Bingo_Header.h"
/*
 * Function takes a window pointer, struct socketaddr_in and an integer for number of
 * players joined
 */
void server_started_screen(WINDOW *w,struct sockaddr_in addr,int n)
{
/********************* Prints border *******************************/
    wattron(w,COLOR_PAIR(5)|A_REVERSE);
    wborder(w,'|','|','-','-','+','+','+','+');
    wattroff(w,COLOR_PAIR(5)|A_REVERSE);
/******************************************************************/

/******** Prints server id and No. of players joined**************/
    mvwprintw(w,2,4,"%s %u","YOUR SERVER ID : ",ntohs(addr.sin_port));
    mvwprintw(w,5,4,"%s %d","PLAYERS JOINED : ",n);
/******************************************************************/

/******************************************************************/
    wattron(w,COLOR_PAIR(4));
    mvwprintw(w,6,3,"(MUST BE MORE THAN 1 TO START) ",n);
    mvwaddch(w,2,2,ACS_DIAMOND);
    mvwaddch(w,5,2,ACS_RARROW);
    wattroff(w,COLOR_PAIR(4));
/******************************************************************/

/******************************************************************/
    wattron(w,COLOR_PAIR(6));
    mvwprintw(w,10,2,"PRESS ENTER TO START GAME('q' TO EXIT) ",n);
    wattroff(w,COLOR_PAIR(6));
/******************************************************************/

    update_panels();
    doupdate();
}
