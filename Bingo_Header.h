/*
 * This is the Header file for the bingo game.
 */

#include<stdio.h>
#include<pthread.h>
#include<ncurses.h>
#include<panel.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include"cdll.h"
#include<string.h>


#define right 7
#define width 5 
#define length 8
#define sx 10
#define sy 60
#define ADCAST (struct sockaddr*)
#define MY_ADDR "127.0.0.1"

typedef struct
{
    char com;	//Command
    int num;	//Number
    int bng;	//bingos number
    int opp;	//opponent
}data;		//For sending and receiving data

typedef struct
{
    pthread_mutex_t lock;	//For mutex locking cdll
    cdll l;			// Circular double linked list for storing player data
    int n;			//Number of players playing
}playerlist;

typedef struct
{
    int sd,status,size,flags,sec;
    void* data;
    pthread_t tmrt,recvt;
}recv_p;

	/************  Used as parameter inside timed recv function*********
	   sd		-	Socket discriptor.
	   status	-	Return of recv.
	   size		-	Size of data to send.
	   flags	-	recv function flags argument
	   sec		-	Number of seconds to wait.
	   data		-	Pointer of the data to send.
	   tmrt		-	Thread id of timer thread.
	   recvt	-	Thread id of the recv thread.
	*/

typedef struct
{
    playerlist pl;
    int x,y,p,q;
    WINDOW *bingo[5][5];
    int array[5][5];
    pthread_t gameid;
    pthread_mutex_t get_m,done_mutex;
    pthread_cond_t done;
}getkey_p;

	/*********  Used as parameter for get_key thread ************
	  pl		-	Contains the list of all players
	  x & y		-	For knowing current highlighted position in the grid.
	  p & q		-	For putting the selected number's position from the grid.
	  bingo		-	For creating the bingo grid.
	  pid		-	The thread id to cancel when the user quits.
	  get_m		-	Mutex for letting get_key know whether to accept a selected number or not.
	  done_mutex	-	To notify the game thread whether the data that was asked is available or not.
	  done		-	For sending signal from get_key when the data asked for is availabe.
	*/

typedef struct
{
    int sd;
    int plid;
	pthread_t tid;
    struct sockaddr_in ad;
    int array[5][5];
    int adl;
    int bngcnt;
}player;

	/********** Used as data for circular double linked list *********
	  sd		-	Socket discriptor for that player's client program.
	  plid		-	Player id.
	  tid		-	Confirmation thread's id. This thread will run right after accepting connection till game starts to remove the
	  			player from the list if the player leaves.
	  ad		-	Address of the player's client program.
	  array		-	That player's bingo grid.
	  adl		-	The player's client program's address length.
	  bngcnt	-	Player's Client program's bingo count.
	*/

typedef struct
{
    playerlist *pl;
	node* p;
	pthread_mutex_t *lock;
  	  WINDOW *w;
  	  PANEL *pan;
   	 int *n,status;
	 pthread_t sqt,acct;
}conf_p;
	/*
	   
	 */

typedef struct
{
    WINDOW *playchance,*bingocnt;
    PANEL *pan[5][5],*chancepan,*bingcnt;
    int sersd;
    getkey_p get;
    pthread_t getid;
}game_p;		//REQUREMENTS FOR RUNNING A GAME

typedef struct
{
    pthread_cond_t *c;
    pthread_mutex_t *m;
    pthread_t tmr,cwait;
    int sec,flag;
}cond_p;


int pthread_setconcurrency(int new_level);
void sleep(int);
void close(int);
uint32_t inet_addr(char*);
int read(int,void*,int);
int write(int,void*,int);

void print_array(WINDOW *bingo[5][5],int array[5][5],int x,int y);
void* timer(void*);
void* cond_wait(void*);
int timedwait_cond(pthread_cond_t*,pthread_mutex_t*,int);
void* recv_t(void* arg);
void* timer_2(void* arg);
int timed_recv(int sd,void* data,int size,int flags,int sec);
int cmp(void* d1,void* d2);
void disp(void* d);
void cpy(void* d,void* s);
void fill_bingo(int bingo[5][5]);
void search_strike(int bingo[5][5],int num,int *i,int *j);
int bingos(int bingo[5][5],int i,int j);
void bingodisp(WINDOW *bingocnt,int player_bingo);
int get_key(WINDOW *bingo[5][5],int *x,int *y,int array[5][5]);
void vs_comp(char **err);
void Print_MainMenu(WINDOW *main_menu,WINDOW *title,PANEL *pan[2], int highlight);
void JoinGameScreen(WINDOW *Joingame);
void start_server(char **err);
void* accept_t(void* arg);
void* client_game_t(void*);
void* recv_t(void* arg);
void* serv_game_t(void* arg);
void* startquit(void* arg);
void* get_key_t(void* arg);
void* confirm_t(void*);
void* cleanup_t(void*);
void connect_to_server(char **err);
void* client_game(void* arg);
void server_started_screen(WINDOW *w,PANEL *pan,struct sockaddr_in addr,int n);

