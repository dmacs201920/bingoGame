#include"Bingo_Header.h"

/*
	FUNCTION TO DISPLAY THE NUMBER OF ROWS, COLUMNS OR DIAGONALS COMPLETELY STRIKED (BINGO COUNT)
*/

void bingodisp(WINDOW *bingocnt,int player_bingo)
{
    /********************************************  GREATER THAN FIVE SO IT'S BINGOOOOOO!!!!!  ******************************************************/
    if(player_bingo>4)
    {
	wattron(bingocnt,A_BOLD|COLOR_PAIR(3));
	mvwprintw(bingocnt,13,1,"O");
	wattroff(bingocnt,A_BOLD|COLOR_PAIR(3));
    }
    /****************************************  GREATER THAN FOUR SO FOUR OF ROW, COLUMN OR DIAGONAL COMPLETED  *************************************/
    if(player_bingo>3)
    {
	wattron(bingocnt,A_BOLD|COLOR_PAIR(3));
	mvwprintw(bingocnt,10,1,"G");
	wattroff(bingocnt,A_BOLD|COLOR_PAIR(3));
    }
    /****************************************  GREATER THAN THREE SO THREE OF ROW, COLUMN OR DIAGONAL COMPLETED  ***********************************/
    if(player_bingo>2)
    {
	wattron(bingocnt,A_BOLD|COLOR_PAIR(3));
	mvwprintw(bingocnt,7,1,"N");
	wattroff(bingocnt,A_BOLD|COLOR_PAIR(3));
    }
    /****************************************  GREATER THAN TWO SO TWO OF ROW, COLUMN OR DIAGONAL COMPLETED  **************************************/
    if(player_bingo>1)
    {
	wattron(bingocnt,A_BOLD|COLOR_PAIR(3));
	mvwprintw(bingocnt,4,1,"I");
	wattroff(bingocnt,A_BOLD|COLOR_PAIR(3));
    }
    /****************************************  GREATER THAN ZERO SO ONE OF ROW, COLUMN OR DIAGONAL COMPLETED  **************************************/
    if(player_bingo>0)
    {
	wattron(bingocnt,A_BOLD|COLOR_PAIR(3));
	mvwprintw(bingocnt,1,1,"B");
	wattroff(bingocnt,A_BOLD|COLOR_PAIR(3));
    }
}
