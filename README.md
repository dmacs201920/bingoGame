# bingoGame.3bsc
A novice implementation of bingo game.
Requiements:
	ncureses
	pthreads
	sockets

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

Accept_Thread.c	:
	For accepting connections on serverside.
BingoDisp.c:
	For Displaying the word BINGO as it should appear.
Bingo_Header.h:
	Header File 
Bingo_Main.c
Bingos.c
cdll.c
cdll.h
Client_Game_Thread.c
Cond.c
Confirm_Thread.c
Connect_To_Server.c
Fill_Bingo.c
Get_Key.c
Get_Key_Thread.c
Print_Array.c
Print_Main_Menu.c
Recv_Thread.c
Search_and_Strike.c
Server_Game_Thread.c
Server_started_screen.c
Start_Quit_Thread.c
Start_Server.c
VS_Comp.c
