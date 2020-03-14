#include"Bingo_Header.h"
void vs_comp(char **err)
{
    int player[5][5],comp[5][5],x=0,y=0,temp,p=0,q=0,i,j,t1,t2;
    fill_bingo(player);					//FILLS THE GAME ARRAY FOR THE USER
    fill_bingo(comp);					//FILLS THE GAME ARRAY FOR THE COMPUTER
    int player_bingo=0,comp_bingo=0;			//COUNTS THE NUMBER OF ROWS,COLS AND DIAGONALS FINISHED

    int ch,flag;

    int startx = 7,starty = 60,row,col;

    WINDOW *bingo[5][5],*playchance,*bingocnt;		//BINGO IS FOR DISPLAYING THE ARRAY NUMBERS
    //PLAYCHANCE FOR DISPLAYING WHO'S CHANCE IT IS
    //BINGOCNT IS FOR DISPLAYING THE THE NUMBER OF ROWS,COLS AND DIAGONALS COMPLETED
    PANEL *pan[5][5],*chancepan,*bingcnt;



    playchance = newwin(3,120,3,starty);		//CREATES THE WINDOW AND RETURNS A POINTER TO THE PLAYCHANCE
    if(playchance==NULL)				
    {
	*err="Unable to create WINDOW";				//ERROR MSG
	//	pthread_mutex_destoy(&m);
	//	pthread_mutex_destoy(&done_mutex);
	//	pthread_cond_destoy(&done);
	return;
    }

    chancepan = new_panel(playchance);			//CREATES THE PANEL AND RETURN THE POINTER TO CHANCEPAN
    if(chancepan==NULL)				
    {
	delwin(playchance);
	//	pthread_mutex_destoy(&m);
	//	pthread_mutex_destoy(&done_mutex);
	//	pthread_cond_destoy(&done);
	*err="Unable to create PANEL";				//ERROR MSG
	return;
    }

    bingocnt = newwin(60,3,startx+2,starty-5);
    if(bingocnt==NULL)				
    {
	del_panel(chancepan);
	delwin(playchance);

	*err="Unable to create WINDOW";				//ERROR MSG
	//	pthread_mutex_destoy(&m);
	//	pthread_mutex_destoy(&done_mutex);
	//	pthread_cond_destoy(&done);
	return;
    }

    bingcnt = new_panel(bingocnt);
    if(bingcnt==NULL)				
    {
	del_panel(chancepan);
	delwin(playchance);

	delwin(bingocnt);
	*err="Unable to create PANEL";				//ERROR MSG
	//	pthread_mutex_destoy(&m);
	//	pthread_mutex_destoy(&done_mutex);
	//	pthread_cond_destoy(&done);
	return;
    }

    ////////////////////////////////////////////////////		CREATING BINGO WINDOWS AND PANELS    


    for(i=0;i<5;i++)
    {
	for(j=0;j<5;j++)
	{


	    bingo[i][j] = newwin(width,length,startx,starty);
	    if(bingo[i][j]==NULL)
	    {
		del_panel(chancepan);
		delwin(playchance);

		del_panel(bingcnt);
		delwin(bingocnt);

		for(t1=0;t1<=i;++t1)
		    for(t2=0;t2<5;++t2)
		    {
			if(t1==i&&t2==j)
			    break;
			delwin(bingo[t1][t2]);
		    }
		*err="Unable to create WINDOW";				//ERROR MSG
		//	pthread_mutex_destoy(&m);
		//	pthread_mutex_destoy(&done_mutex);
		//	pthread_cond_destoy(&done);
		return;
	    }
	    pan[i][j] = new_panel(bingo[i][j]);
	    if(pan[i][j]==NULL)
	    {
		del_panel(chancepan);
		delwin(playchance);
		del_panel(bingcnt);
		delwin(bingocnt);
		for(t1=0;t1<5;t1++)
		    for(t1=0;t1<5;t1++)
			delwin(bingo[i][j]);
		for(t1=0;t1<=i;++t1)
		    for(t2=0;t2<5;++t2)
		    {
			if(t1==i&&t2==j)
			    break;
			del_panel(pan[t1][t2]);
		    }

		*err="Unable to create PANEL";				//ERROR MSG
		//	pthread_mutex_destoy(&m);
		//	pthread_mutex_destoy(&done_mutex);
		//	pthread_cond_destoy(&done);
		return;
	    }

	    wattron(bingo[i][j],COLOR_PAIR(1)|A_REVERSE);		//ENABLES ATTRIBUTES IN THE ARGUMENTS


	    wborder(bingo[i][j],'|','|','-','-','+','+','+','+');	//FOR BORDERING THE WINDOW

	    wattroff(bingo[i][j],COLOR_PAIR(1)|A_REVERSE);		//DISABLES ATTRIBUTES IN THE ARGUMENTS

	    mvwprintw(bingo[i][j],2,3,"%d",player[i][j]);		//MOVES TO THE REQ POSITION AND PRINTS IN THE WINDOW

	    starty+=right;

	}
	startx+=width-1;
	starty = sy; 
    }



    wattron(bingo[0][0],A_STANDOUT);
    mvwprintw(bingo[0][0],2,3,"%d",player[0][0]);
    wattroff(bingo[0][0],A_STANDOUT);
    update_panels();	
    doupdate();				//REFRESHES ALL THE PANELS IN ORDER REQUIRED


    while(player_bingo<5&&comp_bingo<5)
    {
	mvwprintw(playchance,1,1,"   YOU ARE PLAYING  ");
	update_panels();
	doupdate();
	if(get_key(bingo,&x,&y,player)==1)			//GETS READY FOR INPUT FORM USER
	{
	    for(i=0;i<5;++i)
		for(j=0;j<5;++j)
		{
		    del_panel(pan[i][j]);
		    delwin(bingo[i][j]);
		}
	    del_panel(chancepan);
	    delwin(playchance);
	    del_panel(bingcnt);
	    delwin(bingocnt);
	    return;
	}
	search_strike(comp,player[x][y],&i,&j);			//STRIKES THE NUMBER FOR COMPUTER GIVEN FROM THE USER
	player[x][y] = 0;					
	player_bingo+=bingos(player,x,y);			
	comp_bingo+=bingos(comp,i,j);				//INCREMENTS THE BINGO COUNT IF ANY ROW,COL OR DIAGONAL IS COMPLETE
	if(i==-1)
	{
	    mvwprintw(playchance,1,1,"    ERROR!!!       ");
	    update_panels();
	    doupdate();
	    sleep(2);

	    for(i=0;i<5;++i)
		for(j=0;j<5;++j)
		{
		    del_panel(pan[i][j]);
		    delwin(bingo[i][j]);
		}
	    del_panel(chancepan);
	    delwin(playchance);
	    del_panel(bingcnt);
	    delwin(bingocnt);
	    return;
	}
	bingodisp(bingocnt,player_bingo);
	mvwprintw(playchance,1,1,"COMPUTER IS PLAYING");
	//Print Comp is playing
	update_panels();
	doupdate();
	sleep(0.25);
	while(comp[p][q]==0)
	{
	    ++q;
	    if(q==5)
	    {
		++p;
		q=0;
	    }
	}
	search_strike(player,comp[p][q],&i,&j);
	comp[p][q]=0;
	comp_bingo+=bingos(comp,p,q);
	if(i==-1)
	{
	    mvwprintw(playchance,1,1,"    ERROR!!!       ");
	    update_panels();
	    doupdate();
	    sleep(2);
	    for(i=0;i<5;++i)
		for(j=0;j<5;++j)
		{
		    del_panel(pan[i][j]);
		    delwin(bingo[i][j]);
		}
	    del_panel(chancepan);
	    delwin(playchance);
	    del_panel(bingcnt);
	    delwin(bingocnt);
	    return;
	}
	if(i!=x||j!=y)
	{
	    wattron(bingo[i][j],A_BOLD|COLOR_PAIR(3));
	    mvwprintw(bingo[i][j],2,3,"%s","X ");		//to hide comp number
	    wattron(bingo[i][j],A_BOLD|COLOR_PAIR(3));
	}
	else
	{
	    wattron(bingo[i][j],A_BOLD|A_STANDOUT|COLOR_PAIR(3));
	    mvwprintw(bingo[i][j],2,3,"%s","X ");		//to hide comp number
	    wattron(bingo[i][j],A_BOLD|A_STANDOUT|COLOR_PAIR(3));
	}
	player_bingo+=bingos(player,i,j);

	bingodisp(bingocnt,player_bingo);
	update_panels();
	doupdate();
    }
    if(player_bingo>4&&comp_bingo>4)
    {
	wattron(playchance,COLOR_PAIR(3));
	mvwprintw(playchance,1,1,"                       ");
	mvwprintw(playchance,2,1,"      IT'S A DRAW!!     ");
	wattroff(playchance,COLOR_PAIR(3));
    }
    else if(comp_bingo>4)
    {
	wattron(playchance,COLOR_PAIR(3));
	mvwprintw(playchance,1,1,"                        ");
	mvwprintw(playchance,2,1,"	 COMPUTER WON!?!  ");
	wattroff(playchance,COLOR_PAIR(3));
    }
    else
    {    
	wattron(playchance,COLOR_PAIR(3));
	mvwprintw(playchance,1,1,"                        ");
	mvwprintw(playchance,2,1,"	 YOU WON!!  ");
	wattroff(playchance,COLOR_PAIR(3));
    }
    update_panels();
    doupdate();
    sleep(2);
    for(i=0;i<5;++i)
	for(j=0;j<5;++j)
	{
	    del_panel(pan[i][j]);
	    delwin(bingo[i][j]);
	}
    del_panel(chancepan);
    delwin(playchance);
    del_panel(bingcnt);
    delwin(bingocnt);
}
