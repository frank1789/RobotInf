#include "input_data.h"

/*FUNZIONE check_obstacle
  controlla la presenza di ostacoli davanti il sensore a ultrasuoni
  restituendo TRUE in caso non ci siano ninete o se si trova ad una distanza maggiore
  di 5 cm altrimenti restituisce False
*/
  
bool check_obstacle(float dist_obs){
  bool check {false}; 
  Serial.print("distanza: ");
  Serial.print(dist_obs);
  Serial.println(" cm");
  if (dist_obs >= 5.00 || dist_obs == 0.00) check = true;
  else check = false;
  return check;
}

/*FUNZIONE read_path
  in questa funzione in ingresso vengono ricevuti
  due interi ricavati dai metodi dei line follewer
  e in uscita viene restituito un intero che individua la posizione del 
  robot rispetto alla linea da seguire (error = output - setpoint).
  Sulla base dei valori ricevuti dai sensori si ottengono i seguenti casi:

                                   (X=nero; O=bianco)
                          DX  SX        SX DX        
  GO_FORWARD           ==  1 , 2       O X X O
  TURN_LEFT_VERY_SOFT  ==  3 , 2       O X O O
  TURN_LEFT_SOFT       ==  1 , 0       X X X O
  TURN_LEFT_HARD       ==  3 , 0       X X O O
  TURN_LEFT_VERYHARD   ==  3 , 1       X O O O
  TURN_RIGHT_VERY_SOFT ==  1 , 3       O O X O
  TURN_RIGHT_SOFT      ==  0 , 2       O X X X
  TURN_RIGHT_HARD      ==  0 , 3       O O X X
  TURN_RIGHT_VERYHARD  ==  2 , 3       O O O X
  NO_LINE              ==  3 , 3       O O O O
  EXCEPTION1           ==  2 , 0       X X O X
  EXCEPTION2           ==  0 , 1       X O X X
  GO_FORWARD_bis       ==  2 , 1       X O O X          
  CROSS                ==  0 , 0       X X X X    
  EXCEPTION3     	     ==  2 , 2	     O X O X
  EXCEPTION4           ==  1 , 1       X O X O
*/

int read_path(int sensorStateDX, int sensorStateSX){
  int input_path = 0;
  
  if(sensorStateDX == 1 && sensorStateSX == 2){
  	input_path = 1;
  	Serial.print("sensor input, ");
  	Serial.println(input_path);
  }  //GO_FORWARD 

  else if(sensorStateDX == 3 && sensorStateSX == 2){
  	input_path = 2;
  	Serial.print("sensor input, ");
  	Serial.println(input_path);
  }//TURN_LEFT_VERY_SOFT

  else if(sensorStateDX == 1 && sensorStateSX == 0){
  	input_path = 3;
  	Serial.print("sensor input, ");
  	Serial.println(input_path);
  }  //TURN_LEFT_SOFT
  
  else if(sensorStateDX == 3 && sensorStateSX == 0){
    input_path = 4;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //TURN_LEFT_HARD 
  
  else if(sensorStateDX == 3 &&  sensorStateSX == 1){
    input_path = 5;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //TURN_LEFT_VERYHARD
    
  else if(sensorStateDX == 1 && sensorStateSX == 3){
    input_path = 6;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //TURN_RIGHT_VERY_SOFT

  else if(sensorStateDX == 0 && sensorStateSX == 2){
    input_path = 7;
    Serial.print("sensor input, ");
    Serial.println(input_path);
    }  //TURN_RIGHT_SOFT
  
  else if(sensorStateDX == 0 && sensorStateSX == 3){
    input_path = 8;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //TURN_RIGHT_HARD 
  
  else if(sensorStateDX == 2 && sensorStateSX == 3){
    input_path = 9;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //TURN_RIGHT_VERYHARD

  else if(sensorStateDX == 3 && sensorStateSX == 3){
    input_path = 10;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //NO_LINE

   else if(sensorStateDX == 2 && sensorStateSX == 0){
    input_path = 11;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //EXCEPTION1

   else if(sensorStateDX == 0 && sensorStateSX == 1){
    input_path = 12;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //EXCEPTION2 

   else if(sensorStateDX == 2 && sensorStateSX == 1){
    input_path = 13;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //GO_FORWARD_bis

   else if(sensorStateDX == 0 && sensorStateSX == 0){
    input_path = 14;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //CROSS

   else if(sensorStateDX == 2 && sensorStateSX == 2){
    input_path = 15;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //EXCEPTION3

   else if(sensorStateDX == 1 && sensorStateSX == 1){
    input_path = 16;
    Serial.print("sensor input, ");
    Serial.println(input_path);
  }  //EXCEPTION4 
  return input_path;
}