#include"Bingo_Header.h"
/*
 * This function takes the bingo array.( bingo )
 * the number to search.( num )
 * two integer pointers for output, the output is the position of the number. ( i , j )
 * if num does not exist, function sets i and j as -1.
 */
void search_strike(int bingo[5][5],int num,int *i,int *j)
{
    for((*i)=0;(*i)<5;++(*i))
	for((*j)=0;(*j)<5;++(*j))
	    if(bingo[(*i)][(*j)]==num)
	    {
		bingo[(*i)][(*j)]=0;
		return;
	    }
    (*j)=(*i)=-1;
}
