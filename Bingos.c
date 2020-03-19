#include"Bingo_Header.h"

/*
		FUNCTION TO CHECK THE BINGS NUMBER(NUMBER OF ROWS, COLUMNS OR DIAGONALS COMPLETELY STRIKEN)
*/   

int bingos(int bingo[5][5],int i,int j) 	// 'i' AND 'j' ARE THE ROW AND COLUMN COORDINATES IN THE ARRAY WHERE NUMBER STRIKED BY PLAYER
{
    int x,bing=0,flag=1;		//INITIALIZATIONS

    /************************************* CHECKING THE ROW IN WHICH THE PLAYER STRIKED FOR BINGOS  ***********************************************/
    for(x=0;x<5;++x)	
	if(bingo[x][j]!=0)		// 0 IMPLIES THE NUMBER HAS BEEN STRIKED BY THE USER
	{
	    flag=0;			// IF EVEN ONE NUMBER IN THE RWO IS NOT ZERO THEN IT'S NOT COMPLETE FOR INCREMENTING BINGO
	    break;
	}
    if(flag==1)			// IF ALL THE ROW NUMBERS ARE 0 THEN INCREMENT BINGO COUNT
	++bing;

    /***********************************************************************************************************************************************/	
    flag=1;

    /*************************************  CHECKING THE COLUMN IN WHICH THE PLAYER STRIKED FOR BINGOS  ********************************************/
    for(x=0;x<5;++x)
	if(bingo[i][x]!=0)
	{
	    flag=0;
	    break;
	}
    if(flag==1)				// IF ALL THE COLUMN NUMBERS ARE 0 THEN INCREMENT BINGO COUNT
	++bing;

    /***********************************************************************************************************************************************/	
    flag=1;

    /***********************************  CHECKING THE DIAGONAL 1 IN WHICH THE PLAYER STRIKED FOR BINGOS  ******************************************/
    if(i==j)
    {
	for(x=0;x<5;++x)
	    if(bingo[x][x]!=0)
	    {
		flag=0;
		break;
	    }
	if(flag==1)			// IF ALL THE DIAGONAL 1 NUMBERS ARE 0 THEN INCREMENT BINGO COUNT
	    ++bing;
    /***********************************************************************************************************************************************/	
	flag=1;
    }

    /***********************************  CHECKING THE DIAGONAL 2 IN WHICH THE PLAYER STRIKED FOR BINGOS  ******************************************/
    if(i+j==4)
    {
	for(x=0;x<5;++x)
	    if(bingo[x][4-x]!=0)
	    {
		flag=0;
		break;
	    }
	if(flag==1)			// IF ALL THE DIAGONAL 2 NUMBERS ARE 0 THEN INCREMENT BINGO COUNT
	    ++bing;
    }

    return bing;			//RETURN THE BINGO COUNT 
}
