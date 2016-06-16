#include "functioncontrol.h"

/*FUNZIONE path_error
  in questa funzione in ingresso vengono ricevuti
  due interi ricavati dai metodi dei line follewer
  e in uscita viene restituito un intero che individua la posizione del 
  robot rispetto alla linea da seguire (error = output - setpoint).
  
  Sulla base dei valori ricevuti dai sensori si ottengono i seguenti casi:

                                   (X=nero; O=bianco)
                          DX  SX        SX DX        Error
  GO_FORWARD           ==  1 , 2       O X X O         0  (line = black & background = white) 
  TURN_LEFT_VERY_SOFT  ==  3 , 2       O X O O         1
  TURN_LEFT_SOFT       ==  1 , 0       X X X O         2
  TURN_LEFT_HARD       ==  3 , 0       X X O O         3
  TURN_LEFT_VERYHARD   ==  3 , 1       X O O O         4
  TURN_RIGHT_VERY_SOFT ==  1 , 3       O O X O        -1
  TURN_RIGHT_SOFT      ==  0 , 2       O X X X        -2
  TURN_RIGHT_HARD      ==  0 , 3       O O X X        -3
  TURN_RIGHT_VERYHARD  ==  2 , 3       O O O X        -4
  NO_LINE              ==  3 , 3       O O O O        100    per ora con 100 sto ad indicare di andare in spirale
  EXCEPTION1           ==  2 , 0       X X O X         1 
  EXCEPTION2           ==  0 , 1       X O X X        -1  
  GO_FORWARD_bis       ==  2 , 1       X O O X         0    (line = white & background = black) 
  CROSS                ==  0 , 0       X X X X         0     per ora lo faccio andare dritto
  EXCEPTION3     	  	 ==  2 , 2	   	 O X O X         0     quando trova questo caso strano per ora va dritto
  EXCEPTION4           ==  1 , 1       X O X O         0     quando trova questo caso strano per ora va dritto
*/
  int path_error(int path){
  	int error;
  	switch(path)
  	{
  		case 1 : {
  			Serial.print("GO_FORWARD");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 0;
  			Serial.println(error);
  			break;
  		}

  		case 2 : {
  			Serial.print("Turning left SOFT");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 2;
  			Serial.println(error);
  			break;
  		}

  		case 3 : {
  			Serial.print("Turning left HARD");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 3;
  			Serial.println(error);
  			break;
  		}

  		case 4 : {
  			Serial.print("Turning left VERY HARD");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 4;
  			Serial.println(error);
  			break;
  		}

  		case 5 : {
  			Serial.print("Turning right SOFT");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = -1;
  			Serial.println(error);
  			break;
  		}

  		case 6 : {
  			Serial.print("Turning right HARD");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = -3;
  			Serial.println(error);
  			break;
  		}

  		case 7 : {
  			Serial.print("Turning right VERY HARD");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = -4;
  			Serial.println(error);
  			break;
  		}

  		case 8 : {
  			Serial.print("Turning left VERY SOFT");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 0;
  			Serial.println(error);
  			break;
  		}

  		case 9: {
  			Serial.print("Turning right VERY SOFT");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 0;
  			Serial.println(error);
  			break;
  		}

  		case 10: {
  			Serial.print("case 10");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 0;
  			Serial.println(error);
  			break;
  		}

  		case 11 : {
  			Serial.print("case 11");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 0;
  			Serial.println(error);
  			break;
  		}

  		case 12:  {
  			Serial.print("case 12");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 0;
  			Serial.println(error);
  			break;
  		}

  		case 13:{
  			Serial.print("case 13");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 0;
  			Serial.println(error);
  			break;
  		}

  		case 14:{
  			Serial.print("case 14");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 0;
  			Serial.println(error);
  			break;
  		}

  		case 15:{
  			Serial.print("case 15");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error =0 ;
  			Serial.println(error);
  			break;
  		}

  		case 16:{
  			Serial.print("case 16");
  			Serial.print(", ");
  			Serial.print(path);
  			Serial.print(", error: ");
  			error = 0;
  			Serial.println(error);
  			break;
  		}

  		default:  break;
  	}
  	return error;
  }

  uint8_t motorspeed(uint8_t motorSpeed){
  	if (motorSpeed >= 255) return 255;
  	else return	motorSpeed;
  }