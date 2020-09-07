#include"Bingo_Header.h"


char* mkbingo(game_p *par)
{
	par->playchance = newwin(nline,ncols,startx-nline-1,starty);		//CREATES THE WINDOW AND RETURNS A POINTER TO THE PLAYCHANCE
	if(par->playchance==NULL)				
	{
		return "Unable to create WINDOW";				//ERROR MSG
	}
    par->chancepan = new_panel(par->playchance);			//CREATES THE PANEL AND RETURN THE POINTER TO CHANCEPAN
    if(par->chancepan==NULL)				
    {
    	delwin(par->playchance);
		return "Unable to create PANEL";				//ERROR MSG
	}

	par->bingocnt = newwin(bngcnt_ln,bngcnt_col,startx+2,starty-5);
	if(par->bingocnt==NULL)				
	{
		delwin(par->playchance);
		del_panel(par->chancepan);

		return "Unable to create WINDOW";				//ERROR MSG
	}
	par->bingcnt = new_panel(par->bingocnt);
	if(par->bingcnt==NULL)				
	{
		delwin(par->playchance);
		del_panel(par->chancepan);
		delwin(par->bingocnt);
		return "Unable to create PANEL";				//ERROR MSG
	}


	int i,j,t1,t2;

	for(i=0;i<5;i++)
	{
		for(j=0;j<5;j++)
		{
			par->get.bingo[i][j] = newwin(width,length,startx+(width-1)*i,starty+right*j);
			if(par->get.bingo[i][j]==NULL)
			{
				del_panel(par->chancepan);
				delwin(par->playchance);

				del_panel(par->bingcnt);
				delwin(par->bingocnt);

				for(t1=0;t1<=i;++t1)
				{
					for(t2=0;t2<5;++t2)
					{
						if(t1==i&&t2==j)
							break;
						delwin(par->get.bingo[t1][t2]);
					}
				}
				return "Unable to create WINDOW";				//ERROR MSG
			}
			par->pan[i][j] = new_panel(par->get.bingo[i][j]);
			if(par->pan[i][j]==NULL)
			{
				del_panel(par->chancepan);
				delwin(par->playchance);
				del_panel(par->bingcnt);
				delwin(par->bingocnt);
				for(i=0;i<5;i++)
				{
					for(j=0;j<5;j++)
					{
						delwin(par->get.bingo[i][j]);
					}
				}
				for(t1=0;t1<=i;++t1)
				{
					for(t2=0;t2<5;++t2)
					{
						if(t1==i&&t2==j)
							break;
						del_panel(par->pan[t1][t2]);
					}
				}
				return "Unable to create PANEL";				//ERROR MSG
			}

  			wattron(par->get.bingo[i][j],COLOR_PAIR(1)|A_REVERSE);		//ENABLES ATTRIBUTES IN THE ARGUMENTS

    		wborder(par->get.bingo[i][j],'|','|','-','-','+','+','+','+');	//FOR BORDERING THE WINDOW

   			wattroff(par->get.bingo[i][j],COLOR_PAIR(1)|A_REVERSE);		//DISABLES ATTRIBUTES IN THE ARGUMENTS

    		mvwprintw(par->get.bingo[i][j],2,3,"%d",par->get.array[i][j]);		//MOVES TO THE REQ POSITION AND PRINTS IN THE WINDOW


		}
	}


	wattron(par->get.bingo[0][0],A_STANDOUT);
	mvwprintw(par->get.bingo[0][0],2,3,"%d",par->get.array[0][0]);
	wattroff(par->get.bingo[0][0],A_STANDOUT);
	update_panels();	
	doupdate();				//REFRESHES ALL THE PANELS IN ORDER REQUIRED
	return NULL;
}