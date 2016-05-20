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
*/

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

/*FUNZIONE LINEA SPEZZATA
  In questa funzione vien slavata l'ultima lettura della vairabile e
  il robot prosegue fino a quando non ritrova la linea, altrimenti....
  è da studiare in laboratorio
*/

/*
int interrupt_line(int e){
  static int last_path_read = e;
    int last_path;
  if(last_path_read == last_path){
    //motorSpeed = motorSpeed / 2;
  }
  else exit;  
  return e;
}
*/

/*FUNZIONE AVANZAMENTO A SPIRALE
  Con questa funzione si ricerca la linea da seguire
  facendo compiere al robot via via una spirale 
  viene incrementata la velocità da passare al motore.
  ATTENZIONE QUESTA FUNZIONE VA FORNITA AD UN SOLO MOTORE
   ALTRIMENTI RUOTERA SUL PROPRIO ASSE...CIRCA
*/
int feed_spiral(int a, int motorSpeedMAX){
 	int count = 5;
    int velocity;
	if(velocity < motorSpeedMAX){ 
    	velocity = a + count ;
    	Serial.println(velocity);
   		}
  	Serial.println("Movimento a spirale");

	return velocity;
}

int feed_spiral2(int a, int motorSpeedMAX){
 	int count = 5;
 	static int velocity {0};
	if(velocity < motorSpeedMAX){ 
		
    	velocity = a + count ;
    	Serial.println(velocity);
   		}
  	Serial.println("Movimento a spirale");

	return velocity;
}


/*FUNZIONE PER IL SUPERAMENTO DEGLI INCROCI
  Nella funzione crossbreed il robot decide quale
  direzione prendere in base alla sceta precedente 
  fatta in modo da esplorarea turno tutte le possibili 
  vie. Facendo variare la variabile booleana
*/

bool crossbreed(){
  static bool direction;
  bool choice_dir = 1;
  choice_dir = direction;
  if (direction == 1){
    choice_dir = 0;
  }
  else{
    choice_dir = 1;
  }
    return direction;
}  

bool check_obstacle(float dist_obs){
  bool check {false}; 
  Serial.print("distanza: ");
  Serial.print(dist_obs);
  Serial.println(" cm");
  if (dist_obs >= 5.00 || dist_obs == 0.00) check = true;
  else check = false;
  return check;
}
