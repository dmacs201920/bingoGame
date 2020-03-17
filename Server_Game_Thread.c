#include"Bingo_Header.h"
int end_game_flag;
void* serv_game_t(void* arg)
{
	char* err=NULL;
	data d;
	int i,j,status,t1,t2;
	game_p *par=arg;
	node *Current_player=par->get.pl.l.h,*tr;

	pthread_mutex_lock(&par->get.get_m);
	int flag=0;

	while(Current_player!=Current_player->n)
	{
		if(Current_player==par->get.pl.l.h)
		{
			wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
			mvwprintw(par->playchance,1,1,"       YOU ARE PLAYING!!!     ");
			wattron(par->playchance,COLOR_PAIR(2)|A_BOLD); 
			update_panels();
			doupdate();
			pthread_mutex_unlock(&par->get.get_m);
			if(timedwait_cond(&par->get.done,&par->get.done_mutex,10)==0)
			{
				tr = Current_player;
				pthread_mutex_lock(&par->get.get_m);
				d.num=par->get.array[par->get.p][par->get.q];
				do
				{
					if(tr == par->get.pl.l.h)
					{
						par->get.array[par->get.p][par->get.q] = 0;
						if((((player*)tr->d)->bngcnt+=bingos(par->get.array,i,j))>4)
							flag=1;

					}
					else
					{
						search_strike(((player*)tr->d)->array,d.num,&i,&j);
						((player*)tr->d)->array[i][j] = 0;
						if((((player*)tr->d)->bngcnt+=bingos(((player*)tr->d)->array,i,j))>4)
							flag=1;
					}

					tr = tr->n;

				}while(tr!=Current_player);
				print_array(par->get.bingo,par->get.array,par->get.x,par->get.y);
				bingodisp(par->bingocnt,((player*)par->get.pl.l.h->d)->bngcnt);

			}
			else		//OF TIMED WAIT
			{
				pthread_mutex_lock(&par->get.get_m);
				d.num=0;
			}
			if(flag!=1)
			{
				tr=Current_player->n;
				d.com='y';
				d.opp=((player*)tr->d)->plid;
				d.bng=((player*)tr->d)->bngcnt;
				send(((player*)tr->d)->sd,&d,sizeof(data),0);
				d.com='n';
				for(tr=tr->n;tr!=Current_player->n;tr=tr->n)
					if(tr!=par->get.pl.l.h)
					{
						d.bng=((player*)tr->d)->bngcnt;
						send(((player*)tr->d)->sd,&d,sizeof(data),0);
					}
				Current_player = Current_player->n;
			}

			else
			{
				tr=Current_player->n;
				d.com='t';

				for(;tr!=Current_player->n;tr=tr->n)
					if(tr!=par->get.pl.l.h)
					{
						d.bng=((player*)tr->d)->bngcnt;
						send(((player*)tr->d)->sd,&d,sizeof(data),0);
					}

				if(((player*)par->get.pl.l.h->d)->bngcnt>4)
				{
					wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
					mvwprintw(par->playchance,1,1,"       YOU WON!!!!!        ");
					wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
				}
				else
				{
					wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
					mvwprintw(par->playchance,1,1,"       YOU LOST           ");
					wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
				}
				update_panels();
				doupdate();
				sleep(2);
				del_panel(par->chancepan);
				delwin(par->playchance);
				del_panel(par->bingcnt);
				delwin(par->bingocnt);

				for(t1=0;t1<5;++t1)
					for(t2=0;t2<5;++t2)
					{
						del_panel(par->pan[t1][t2]);
						delwin(par->get.bingo[t1][t2]);
					}

				pthread_cancel(par->getid);
				if(((player*)par->get.pl.l.h->d)->bngcnt>4)
					end_game_flag = 1;
				else
					end_game_flag = 2;

				pthread_exit(NULL);
			}//else close of flag!=1

		}//if(current_player!=head ) close

		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD);
		mvwprintw(par->playchance,1,1,"                                   ");
		mvwprintw(par->playchance,1,1,"        OPPONENT %d IS PLAYING     ",((player*)Current_player->d)->plid);
		wattron(par->playchance,COLOR_PAIR(2)|A_BOLD); 
		update_panels();
		doupdate();
		if((status=timed_recv(((player*)Current_player->d)->sd,&d,sizeof(data),0,10))!=sizeof(data))
		{
			if(status!=-3)
			{
				tr = Current_player->n;
				close(((player*)Current_player->d)->sd);
				--(par->get.pl.n);
				Current_player->n->p = Current_player->p;
				Current_player->p->n = Current_player->n;
				free(Current_player->d);
				free(Current_player);

				Current_player = tr;
				continue;
			}

			else
				d.num=0;

		}
		else
		{	
			tr = Current_player;
			do
			{
				if(tr == par->get.pl.l.h)
				{
					search_strike(par->get.array,d.num,&i,&j);
					par->get.array[i][j] = 0;
					if((((player*)tr->d)->bngcnt+=bingos(par->get.array,i,j))>4)
						flag=1;

				}
				else
				{
					search_strike(((player*)tr->d)->array,d.num,&i,&j);
					((player*)tr->d)->array[i][j] = 0;
					if((((player*)tr->d)->bngcnt+=bingos(((player*)tr->d)->array,i,j))>4)
						flag=1;
				}
			tr = tr->n;
			}while(tr!=Current_player);
			print_array(par->get.bingo,par->get.array,par->get.x,par->get.y);
			bingodisp(par->bingocnt,((player*)par->get.pl.l.h->d)->bngcnt);
		}

		if(flag!=1)
		{
			tr=Current_player->n;
			d.com='y';
			d.opp=((player*)tr->d)->plid;
			d.bng=((player*)tr->d)->bngcnt;

			if(tr!=par->get.pl.l.h)
				send(((player*)tr->d)->sd,&d,sizeof(data),0);

			tr=tr->n;
			d.com='n';
			for(;tr!=Current_player->n;tr=tr->n)
				if(tr!=par->get.pl.l.h)
				{
					d.bng=((player*)tr->d)->bngcnt;
					send(((player*)tr->d)->sd,&d,sizeof(data),0);
				}
			Current_player = Current_player->n;

		}
		else
		{
			tr=Current_player->n;
			d.com='t';
			for(;tr!=Current_player->n;tr=tr->n)
				if(tr!=par->get.pl.l.h)
				{
					d.bng=((player*)tr->d)->bngcnt;
					send(((player*)tr->d)->sd,&d,sizeof(data),0);
				}


			if(((player*)par->get.pl.l.h->d)->bngcnt>4)
			{
				wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
				mvwprintw(par->playchance,1,1,"       YOU WON!!!!!        ");
				wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
			}
			else
			{
				wattron(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK);
				mvwprintw(par->playchance,1,1,"       YOU LOST           ");
				wattroff(par->playchance,COLOR_PAIR(2)|A_BOLD|A_BLINK); 
			}
			update_panels();
			doupdate();
			sleep(2);
			del_panel(par->chancepan);
			delwin(par->playchance);
			del_panel(par->bingcnt);
			delwin(par->bingocnt);

			for(t1=0;t1<5;++t1)
				for(t2=0;t2<5;++t2)
				{
					del_panel(par->pan[t1][t2]);
					delwin(par->get.bingo[t1][t2]);
				}

			pthread_cancel(par->getid);
			if(((player*)par->get.pl.l.h->d)->bngcnt>4)
				end_game_flag = 1;
			else
				end_game_flag = 2;

			pthread_exit(NULL);



		}
	}
	tr = par->get.pl.l.h;

	err="No other player playing";
	pthread_cancel(par->getid);
	close(((player*)tr->d)->sd);
	tr=tr->n;
	for(;tr!=par->get.pl.l.h;tr=tr->n)
		close(((player*)tr->d)->sd);
	end_game_flag=-1;
	pthread_exit(err);
}
