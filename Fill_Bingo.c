#include"Bingo_Header.h"

/*
		FUNCTION TO FILL THE BINGO GAME PLAY ARRAY WITH NUMBERS
		THIS IS DONE BY USING RANDOMIZE FUNCTION
		THIS FUNCTION ALSO ENSURES THE RANDOM FUNCTION CREATES ARRAYS FOR PLAYERS DIFFERENTS BY ALTERING THE ARRANGEMENTS ALSO
*/

/***************************************************  CDLL FUNCTIONS  ***********************************************************************/
int cmp1(void* d1,void* d2)
{
    return (*((int*)d1))-(*(int*)d2);
}
void disp1(void* d)
{
    printf("%d",*(int*)d);
}
void cpy1(void* d,void* s)
{
    *(int*)d=*(int*)s;
}

    /*****************************************************************************************************************************************/

void fill_bingo(int bingo[5][5])
{
    srand((int)bingo);
    cdll l;
    init(&l,sizeof(int),cmp1,disp1,cpy1);
    int i,len=25,j;
    for(i=1;i<26;++i)
	insertl(&l,&i,rand()%i);			
    for(i=0;i<5;++i)
	for(j=0;j<5;++j)
	    bingo[i][j]=*(int*)pop(&l);
    freecdll(l);
}
