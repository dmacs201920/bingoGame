#include"Bingo_Header.h"
void server_started_screen(WINDOW *w,PANEL *pan,struct sockaddr_in addr,int n)
{

    wattron(w,COLOR_PAIR(5)|A_REVERSE);
    wborder(w,'|','|','-','-','+','+','+','+');
    wattroff(w,COLOR_PAIR(5)|A_REVERSE);


//    wattron(w,COLOR_PAIR(2));
    mvwprintw(w,2,4,"%s %u","YOUR SERVER ID : ",ntohs(addr.sin_port));
    mvwprintw(w,5,4,"%s %d","PLAYERS JOINED : ",n);
 //   wattroff(w,COLOR_PAIR(2));

    wattron(w,COLOR_PAIR(4));
    mvwprintw(w,6,3,"(MUST BE MORE THAN 1 TO START) ",n);
    mvwaddch(w,2,2,ACS_DIAMOND);
    mvwaddch(w,5,2,ACS_RARROW);
    wattroff(w,COLOR_PAIR(4));

    wattron(w,COLOR_PAIR(6));
    mvwprintw(w,10,2,"PRESS ENTER TO START GAME('q' TO EXIT) ",n);
    wattroff(w,COLOR_PAIR(6));

    update_panels();
    doupdate();
}
