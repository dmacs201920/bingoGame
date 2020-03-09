#include"Bingo_Header.h"
void server_started_screen(WINDOW *w,WINDOW *start,WINDOW *cancel,PANEL *pan[3],struct sockaddr_in addr,int n)
{
    wborder(w,'|','|','-','-','+','+','+','+');
    box(cancel,'|','-');
    box(start,'|','-');

    wattron(start,COLOR_PAIR(1));
    wattron(cancel,COLOR_PAIR(2));
    mvwprintw(start,1,2,"%s","START");
    mvwprintw(cancel,1,2,"%s","CANCEL");
    wattroff(cancel,COLOR_PAIR(2));
    wattroff(start,COLOR_PAIR(1));
    //touchwin(w);
    mvwaddch(w,1,2,ACS_DIAMOND);
    mvwprintw(w,1,4,"%s %u","YOUR SERVER ID : ",addr.sin_port);
    mvwaddch(w,5,2,ACS_RARROW);
    mvwprintw(w,5,4,"%s %d","PLAYERS JOINED : ",2);
    mvwaddch(w,8,2,ACS_RARROW);
    mvwprintw(w,8,4,"%s %d","YOUR SERVER ID : ",5);
    update_panels();
    doupdate();
}
