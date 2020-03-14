#include"Bingo_Header.h"
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
