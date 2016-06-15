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
  EXCEPTION3     	     ==  2 , 2	     O X O X         0     quando trova questo caso strano per ora va dritto
  EXCEPTION4           ==  1 , 1       X O X O         0     quando trova questo caso strano per ora va dritto


int path_error(int sensorStateDX, int sensorStateSX){
  int error = 0;
  
  if(sensorStateDX == 1 && sensorStateSX == 2){
    error = 0; 
  }  //GO_FORWARD 

  else if(sensorStateDX == 3 && sensorStateSX == 2){
     error = 1;
  }//TURN_LEFT_VERY_SOFT

  else if(sensorStateDX == 1 && sensorStateSX == 0){
    error = 2;
  }  //TURN_LEFT_SOFT
  
  else if(sensorStateDX == 3 && sensorStateSX == 0){
    error = 3;
  }  //TURN_LEFT_HARD 
  
  else if(sensorStateDX == 3 &&  sensorStateSX == 1){
    error = 4;
  }  //TURN_LEFT_VERYHARD
    
  else if(sensorStateDX == 1 && sensorStateSX == 3){
    error = -1;
  }  //TURN_RIGHT_VERY_SOFT

  else if(sensorStateDX == 0 && sensorStateSX == 2){
    error = -2;
    }  //TURN_RIGHT_SOFT
  
  else if(sensorStateDX == 0 && sensorStateSX == 3){
    error = -3;
  }  //TURN_RIGHT_HARD 
  
  else if(sensorStateDX == 2 && sensorStateSX == 3){
    error = -4;
  }  //TURN_RIGHT_VERYHARD

  else if(sensorStateDX == 3 && sensorStateSX == 3){
    error = 100;
  }  //NO_LINE

   else if(sensorStateDX == 2 && sensorStateSX == 0){
    error = 1;
  }  //EXCEPTION1

   else if(sensorStateDX == 0 && sensorStateSX == 1){
    error = -1;
  }  //EXCEPTION2 

   else if(sensorStateDX == 2 && sensorStateSX == 1){
    error = 0;
  }  //GO_FORWARD_bis

   else if(sensorStateDX == 0 && sensorStateSX == 0){
    error = 0;
  }  //CROSS

   else if(sensorStateDX == 2 && sensorStateSX == 2){
    error = 0;
  }  //EXCEPTION3

   else if(sensorStateDX == 1 && sensorStateSX == 1){
    error = 0;
  }  //EXCEPTION4 
  return error;
}
*/
int path_error(int path){
  int error;
  switch(path)
  {
    case 1 : {
      Serial.println("VAI DRITTO!!");
      error = 0;
      break;
    }
  
    case 2 : {
      Serial.println("Turning left SOFT");
      error = 2;
      break;
    }
    
    case 3 : {
      Serial.println("Turning left HARD");
      error = 3;
      break;
    }

    case 4 : {
      Serial.println("Turning left VERY HARD");
      error = 4;
      break;
    }

    case 5 : {
      Serial.println("Turning right SOFT");
      error = -1;
      break;
    }

    case 6 : {
      Serial.println("Turning right HARD");
      error = -3;
      break;
    }

    case 7 : {
      Serial.println("Turning right VERY HARD");
      error = -4;
      break;
    }

    case 8 : {
      Serial.println("Turning left VERY SOFT");
      error = 0;
      break;
    }

    case 9: {
      Serial.println("Turning right VERY SOFT");
      error = 0;
      break;
    }

    case 10: {
      Serial.println("case 10");
      error = 0;
      break;
    }

    case 11 : {
      Serial.println("case 11");
      error = 0;
      break;
    }

    case 12:  {
      Serial.println("case 12");
      error = 0;
      break;
    }

    case 13:{
      Serial.println("case 13");
      error = 0;
      break;
    }

    case 14:{
      Serial.println("case 14");
      error = 0;
      break;
    }

    case 15:{
      Serial.println("case 15");
      error =0 ;
      break;
    }

    case 16:{
      Serial.println("case 16");
      error = 0;
      break;
    }

    default:  break;
  }
  return error;
}

/*FUNZIONE speed
  verifica che le lavelocità assegnata ai motori non superi quella massima
  o minima consentita


uint8_t speed(uint8_t const motorSpeedMAX,
              uint8_t const motorSpeedMIN,
              uint8_t motorSpeed){
  if(motorSpeed >= motorSpeedMAX) return speed;
  else{ return }
  if (motorSpeed <= motorSpeedMIN) return speed;
  else{ return }

}
*/

