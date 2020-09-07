cc=gcc
cflags=-g -c
oflag=-g -o
lflags=-lpanel -lncurses -lpthread
nbingo:mkbingo.o Server_started_screen.o Accept_Thread.o cdll.o Bingo_Main.o Fill_Bingo.o Get_Key.o Print_Main_Menu.o VS_Comp.o Bingos.o Search_and_Strike.o BingoDisp.o Client_Game_Thread.o Get_Key_Thread.o Connect_To_Server.o Print_Array.o Cond.o Recv_Thread.o Server_Game_Thread.o Start_Quit_Thread.o Start_Server.o Confirm_Thread.o How_To_Play.o About.o
	$(cc) $(oflag) $@ $^ $(lflags)
mkbingo.o:mkbingo.c Bingo_Header.h
	$(cc) $(cflags) $<  $(lflags)
Server_started_screen.o:Server_started_screen.c Bingo_Header.h
	$(cc) $(cflags) $<  $(lflags)
How_To_Play.o:How_To_Play.c Bingo_Header.h
	$(cc) $(cflags) $<  $(lflags)
About.o:About.c Bingo_Header.h
	$(cc) $(cflags) $<  $(lflags)
Accept_Thread.o:Accept_Thread.c Bingo_Header.h
	$(cc) $(cflags) $<  $(lflags)
Server_Game_Thread.o: Server_Game_Thread.c Bingo_Header.h
	$(cc) $(cflags) $<  $(lflags)
Start_Quit_Thread.o:Start_Quit_Thread.c Bingo_Header.h
	$(cc) $(cflags) $<  $(lflags)
Start_Server.o:Start_Server.c Bingo_Header.h
	$(cc) $(cflags) $<  $(lflags)
Confirm_Thread.o:Confirm_Thread.c Bingo_Header.h
	$(cc) $(cflags) $<  $(lflags)
Cond.o : Cond.c Bingo_Header.h
	$(cc) $(cflags) $<  $(lflags)
Print_Array.o : Print_Array.c Bingo_Header.h
	$(cc) $(cflags) $<  $(lflags)
Client_Game_Thread.o : Client_Game_Thread.c Bingo_Header.h
	$(cc) $(cflags) $< $(lflags)
Get_Key_Thread.o : Get_Key_Thread.c Bingo_Header.h	
	$(cc) $(cflags) $< $(lflags)
Connect_To_Server.o : Connect_To_Server.c Bingo_Header.h
	$(cc) $(cflags) $< $(lflags)
cdll.o: cdll.c Bingo_Header.h
	$(cc) $(cflags) $< 
Bingo_Main.o: Bingo_Main.c Bingo_Header.h
	$(cc) $(cflags) $< $(lflags)
Fill_Bingo.o: Fill_Bingo.c Bingo_Header.h
	$(cc) $(cflags) $< $(lflags)
Get_Key.o: Get_Key.c Bingo_Header.h
	$(cc) $(cflags) $< $(lflags)
Print_Main_Menu.o: Print_Main_Menu.c Bingo_Header.h
	$(cc) $(cflags) $< $(lflags)
VS_Comp.o: VS_Comp.c Bingo_Header.h
	$(cc) $(cflags) $< $(lflags)
Bingos.o: Bingos.c Bingo_Header.h
	$(cc) $(cflags) $< $(lflags)
Search_and_Strike.o: Search_and_Strike.c Bingo_Header.h
	$(cc) $(cflags) $< $(lflags)
BingoDisp.o: BingoDisp.c Bingo_Header.h
	$(cc) $(cflags) $< $(lflags)
Recv_Thread.o : Recv_Thread.c Bingo_Header.h
	$(cc) $(cflags) $< $(lflags)
clean:
	rm -f  mkbingo.o cdll.o Bingo_Main.o Fill_Bingo.o Get_Key.o Print_Main_Menu.o VS_Comp.o Bingos.o Search_and_Strike.o BingoDisp.o Client_Game_Thread.o Get_Key_Thread.o Connect_To_Server.o Print_Array.o Cond.o Recv_Thread.o Server_Game_Thread.o Start_Quit_Thread.o Start_Server.o Confirm_Thread.o Accept_Thread.o nbingo Server_started_screen.o How_To_Play.o About.o
