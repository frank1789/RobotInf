#include "functioncontrol.h"

/*FUNZIONE path_error
  in questa funzione in ingresso vengono ricevuti
  due interi ricavati dai metodi dei line follewer
  e in uscita viene restituito un intero che individua la posizione del 
  robot rispetto alla linea da seguire (error = output - setpoint).
  
  Sulla base dei valori ricevuti dai sensori si ottengono i seguenti casi:

                                   (X=nero; O=bianco)
                          DX  SX        SX  DX        Error
  GO_FORWARD           ==  1 , 2       O X  X O         0  (line = nero & background = bianco) 
  TURN_LEFT_VERY_SOFT  ==  3 , 2       O X  O O         1
  TURN_LEFT_SOFT       ==  1 , 0       X X  X O         2
  TURN_LEFT_HARD       ==  3 , 0       X X  O O         3
  TURN_LEFT_VERYHARD   ==  3 , 1       X O  O O         4
  TURN_RIGHT_VERY_SOFT ==  1 , 3       O O  X O        -1
  TURN_RIGHT_SOFT      ==  0 , 2       O X  X X        -2
  TURN_RIGHT_HARD      ==  0 , 3       O O  X X        -3
  TURN_RIGHT_VERYHARD  ==  2 , 3       O O  O X        -4
  NO_LINE              ==  3 , 3       O O  O O         5  
  EXCEPTION1           ==  2 , 0       X X  O X         0
  EXCEPTION2           ==  0 , 1       X O  X X         0 
  GO_FORWARD_bis       ==  2 , 1       X O  O X         0     
  CROSS                ==  0 , 0       X X  X X         6     
  EXCEPTION3     	  	 ==  2 , 2	   	 O X  O X         0     
  EXCEPTION4           ==  1 , 1       X O  X O         0     
*/
  
int path_error(int path){
  int error;
  switch(path){
    case 1:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = 0;
      //stampa sulla seriale per debugging
      Serial.print("GO_FORWARD");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }
    
    case 2:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = 1;
      //stampa sulla seriale per debugging
      Serial.print("TURN_LEFT_VERY_SOFT");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 3 :{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = 2;
      //stampa sulla seriale per debugging
      Serial.print("TURN_LEFT_SOFT ");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 4:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = 3;
      //stampa sulla seriale per debugging
      Serial.print("TURN_LEFT_HARD");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 5:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = 4;
      //stampa sulla seriale per debugging
      Serial.print("TURN_LEFT_VERYHARD");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 6:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = -1;
      //stampa sulla seriale per debugging
      Serial.print("TURN_RIGHT_VERY_SOFT");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 7:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = -2;
      //stampa sulla seriale per debugging
      Serial.print("TURN_RIGHT_SOFT");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 8:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = -3;
      //stampa sulla seriale per debugging
        Serial.print("TURN_RIGHT_HARD");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 9:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = -4;
      //stampa sulla seriale per debugging
      Serial.print("TURN_RIGHT_VERYHARD");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 10:{
      //attribusico l'errore
      error = 5;
      //stampa sulla seriale per debugging
      Serial.print("case 10");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 11:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = 0;
      //stampa sulla seriale per debugging
      Serial.print("case 11");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 12:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = 0;
      //stampa sulla seriale per debugging
      Serial.print("case 12");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 13:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = 0;
      //stampa sulla seriale per debugging
      Serial.print("case 13");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 14:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = 6;
      //stampa sulla seriale per debugging
      Serial.print("case 14");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 15:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = 0;
      //stampa sulla seriale per debugging
      Serial.print("case 15");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    case 16:{
      //attribusico l'errore da calcolare poi nella funzione PID
      error = 0;
      //stampa sulla seriale per debugging
      Serial.print("case 16");
      Serial.print(", ");
      Serial.print(path);
      Serial.print(", error: ");
      Serial.println(error);
      break;
    }

    default: exit; break;
  }
  return error;
}

uint8_t speed_control(uint8_t motorSpeed){
  if (motorSpeed >= 255) return 255;
  else return	motorSpeed;
}

bool crossbreed(){
  static bool direction = 1;
  
  if (direction == 1){
    direction = 0;
  }
  else{
    direction = 1;
  }
    return direction;
} 