TO CREATE THE EXECUTABLE OF THE GAME:
  MAKEFILE IS AVAILABLE SO JUST TYPE make TO COMPILE THE CODE
  nbingo EXE FILE IS CREATED
  
  TO CREATE THE DUMMY SERVER:
    TYPE make -f makeserver
    GIVES THE OUTPUT EXE ser
    
  ALL THE EXE'S SHOULD RUN ON THE SAME SYSTEM
  
  TO PLAY THE GAME:
      OPEN ./nbingo IN TWO SEPERATE TERMINALS
      ONE MUST OPEN START A SERVER
      (OR DUMMY SERVER CAN BE USED)
      ANOTHER SHOULD OPEN CONNECT TO SERVER AND ENTER THE PORT NUMBER OF THE SERVER OPENED
      
      CLIENT WILL SHOW WAITING FOR SERVER
      ON SERVER SIDE PRESS ENTER WHEN PLAYERS JOINED BECOMES >1
      PRESSING ENTER STARTS THE GAME AND ITS THE SERVER'S CHANCE TO PLAY FIRST
      INPUT IS TIMED SO PRESS ENTER ON ANY NUMBER YOU WANT TO STRIKE WITHIN 10 SEC
      THIS WILL SEND THE STRIKED NUM TO THE CLIENTS AND GIVES THE CHANCE TO THE NEXT PLAYER(CLIENT IN ORDER) TO PLAY
      THE CLIENT HAS TO NOW STRIKE A NUMBER IN THE SAME WAY
      NUMBERS CAN BE NAVIGATED USING THE KEYBOARD AND THE STRIKEN NUMBER WILL BE DISPLAYED WITH A COLOURED 'X' MARK IN THE RESPECTIVE
      BOX
      
      TO USE DUMMY SERVER:
          THE SERVER WILL ASK FOR A CHARACTER(y,n or t), NUMBER(FROM 1 TO 25 i.e NUMBER TO STRIKE)
          ,BINGOS(THE NUMBER OF ROWS,COLS OR DIAGONALS COMPLETELY STRIKEN),AND OPPONENT PLAYING(GIVE SOME INTEGER, IT DOSENT MATTER)
          
      y - MEANS THE CLIENT IS NEXT TO PLAY.
      THIS CHANGES THE CLIENT SIDE TITLE TO "YOU ARE PLAYING"
      n - MEANS THE CLIENT IS NOT TO PLAY NOW.
      SOME OTHER CLIENT(OR SERVER) HAS TO PLAY
      t - TERMINATE THE GAME AND CLOSE CONNECTION 
      