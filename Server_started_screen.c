#include"Bingo_Header.h"
void server_started_screen(WINDOW *w,PANEL *pan,struct sockaddr_in addr,int n)
{
    wborder(w,'|','|','-','-','+','+','+','+');

    //   mvwaddch(w,1,2,ACS_DIAMOND);
    mvwprintw(w,1,4,"%s %u","YOUR SERVER ID : ",ntohs(addr.sin_port));
    //  mvwaddch(w,5,2,ACS_RARROW);
    mvwprintw(w,5,4,"%s %d","PLAYERS JOINED : ",n);
    //  mvwaddch(w,8,2,ACS_RARROW);
    update_panels();
    doupdate();
}
