# bingoGame.3bsc
A novice implementation of bingo game.
Requiements:
	ncureses (atleast version 6.1)
	pthreads
	sockets
Tested on Ubuntu 16.04
instructions.md AVAILABLE

____________________________________________________________________________________________________________________________________________
By:

Name:			Reg. No.:

Sai Vignesh S.		173244
Sai Aravind S.V.	173243

Of 3rd year Bsc. Maths Honours class of batch 2019-2020 of Sri Sathya Sai Institute Of Higher Learrning, Brindavan Campus.
______________________________________________________________________________________________________________________________________________



	BBBBBBBBBBBBBBB		IIIIIIIIIIIIIIIII	NNNN           NN	 GGGGGGGGGGGGGGGGGGG		 OOOOOOOOOOOOOOOO
	BBBBBBBBBBBBBBBB		II		NN NN          NN	GGGGGGGGGGGGGGGGGGGGG		OOOOOOOOOOOOOOOOOO
	BB		BB		II		NN  NN         NN	GGOp				OO		OO
	BB		BB		II		NN   NN        NN	GG				OO		OO
	BB		BB		II		NN    NN       NN	GG				OO		OO
	BB		BB		II		NN     NN      NN	GG				OO		OO
	BBBBBBBBBBBBBBBB		II		NN      NN     NN	GG				OO		OO
	BBBBBBBBBBBBBBBB		II		NN       NN    NN	GG	    GGGGGGGGG		OO		OO
	BB		BB		II		NN        NN   NN	GG	    GGGGGGGGG		OO		OO
	BB		BB		II		NN         NN  NN	GG          GG	   GG		OO		OO
	BB		BB		II		NN          NN NN	GG	    GG	   GG		OO		OO
	BB		BB		II		NN           NNNN	GG	    GG	   GG		OO		OO
	BBBBBBBBBBBBBBBBBB		II		NN	      NNN	GGGGGGGGGGGGGG	   GG		OOOOOOOOOOOOOOOOOO
	BBBBBBBBBBBBBBBB	IIIIIIIIIIIIIIIII	NN	       NN	 GGGGGGGGGGGGG	   G		 OOOOOOOOOOOOOOOO






This game works only on the same computer. Different user's will have to use remote login to play this game on multiple computers.
Each game consists of 2 to 5 persons. Mutiple servers can run at the same time. Both server and client are in the same executable.


							Files And Usage:


Ncurses was done by Vignesh.
Socket was done by Aravind.
Pthreads was done by both.



Accept_Thread.c	:	Done by both.
		Contains : accept_t
	For accepting connections on serverside.
	This function uses circular double linked list to store all the player details.
	
BingoDisp.c:	Done by both.
	Contains : bingodisp
	For Displaying the word BINGO as it should appear on screen.

Bingo_Header.h:
	Header File
 
Bingo_Main.c:	Done by Vignesh.
	Contains : main
	Manages the main menu of the bingo game and calls other functions when required.
	
Bingos.c:	Done by both.
	Contains : bingos
	Calculates the number of rows, coloumns and diagonals striked completely.

cdll.c:		Done by Aravind.
	Circular Double Linked List. Details in cdll.c and cdll.h.

cdll.h:	
	Header file for Circular Double Linked List.

Client_Game_Thread.c:	Done by Both.
	Contains: client_game_t
	Manages the client side of the game.

Cond.c:		Done by Aravind.
	Contains: cond_wait, timer, timedwait_cond.
	timedwait_cond is and implementaion for adding time limit to pthread_cond_wait.

Confirm_Thread.c:	Done by both.
	Contains: confirm_t
	This is used in accept_t after accepting a connection.
	This thread will call recv() function on that client's socket and will wait to know whether
	it exits before the game starts.

Connect_To_Server.c:	Done by both.
	Contains: connect_to_server
	This is used to initialize all the variables required for client_game_t
	and wait for the game to end.

Fill_Bingo.c:	Done by both.
	Contains:	cmp1, disp1, cpy1, fill_bingo
	cmp1, disp1, cpy1 are for cdll initialization.
	fill_bingo fills a matrix of size 5*5 with numbers from 1 to 25 uniquely.

Get_Key.c:	Done by Vignesh.
	Contains:	get_key.
	This function manages the UI of the game while playing vs_computer mode.

Get_Key_Thread.c:	Done by Both.
	Contains: get_key_t
	This thread manages the UI of the game while playing as a client or server.

Print_Array.c:	Done by Both.
	Contains: print_array
	prints the bingo array on the screen.

Print_Main_Menu.c: Done by Vignesh.
	Contains: Print_MainMenu
	Prints the main menu on the screen.

Recv_Thread.c: Done by Aravind.
	Contains : recv_t, timer_2, timed_recv
	Implementaion of waiting for recv for a finite amount of time.

Search_and_Strike.c: Done by Both.
	Conatins: search_strike
	Searches for the given number in a given matrix and returns it's position.

Server_Game_Thread.c: Done by Both.
	Contains: serv_game_t
	The server side of the game.

Server_started_screen.c: Done by Vignesh.
	Contains: server_started_screen
	Prints the server side lobby screen which comes when server is
	waiting for connections.
 
Start_Quit_Thread.c: Done by Both.
	Contains: startquit
	Waits for user to press 'q' or '\n', to know whether to start the game or quit it.
	Used on server side.

Start_Server.c: Done by Both.
	Contains: cpy, cmp, start_server
	cpy and cmp are for cdll.
	start_server initializes variables for server game thread.
	Calls accept_t and startquit, waits for connections and then starts the game.
	Waits for the game to end.
	
VS_Comp.c: Done by both.
	Contains: vs_comp
	For playing with computer.