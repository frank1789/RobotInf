#include "functioncontrol.h"

/*FUNZIONE path_type
  in questa funzione si riceve in ingresso 
  gli interi restitutiti dai metodi dei line follewer
  viene inizializzata una varibile temporanea 
  che individua il tipo di percorso che si appresta ad 
  effetuare restituendo un valore intero.
  Il confronto dei valori ricevuti dai sensori viene 
  cosi confrontato:
  CASE                          DX, SX
  1 -> GO_FORWARD           ==  1, 2  verificato
  2 -> TURN_LEFT_SOFT       ==  1, 0
  3 -> TURN_LEFT_HARD       ==  3, 0
  4 -> TURN_LEFT_VERYHARD   ==  3, 1
  5 -> TURN_RIGHT_SOFT      ==  0, 2
  6 -> TURN_RIGHT_HARD      ==  0, 3
  7 -> TURN_RIGHT_VERYHARD  ==  2, 3
  8 -> NO_LINE              ==  3, 3  verificato
*/
int path_type(int sensorStateDX, int sensorStateSX){
  int tmp = 0;
  
  if(sensorStateDX == 1 && sensorStateSX == 2){
    tmp = 1; 
  }  //GO_FORWARD 

  else if(sensorStateDX == 3 && sensorStateSX == 2){
     tmp = 8;
  }//TURN_LEFT_VERY_SOFT

  else if(sensorStateDX == 1 && sensorStateSX == 0){
    tmp = 2;
  }  //TURN_LEFT_SOFT
  
  else if(sensorStateDX == 3 && sensorStateSX == 0){
    tmp = 3;
  }  //TURN_LEFT_HARD 
  
  else if(sensorStateDX == 3 &&  sensorStateSX == 1){
    tmp = 4;
  }  //TURN_LEFT_VERYHARD
    
  else if(sensorStateDX == 1 && sensorStateSX == 3){
    tmp = 9;
  }  //TURN_RIGHT_VERY_SOFT

  else if(sensorStateDX == 0 && sensorStateSX == 2){
    tmp = 5;
    }  //TURN_RIGHT_SOFT
  
  else if(sensorStateDX == 0 && sensorStateSX == 3){
    tmp = 6;
  }  //TURN_RIGHT_HARD 
  
  else if(sensorStateDX == 2 && sensorStateSX == 3){
    tmp = 7;
  }  //TURN_RIGHT_VERYHARD

  else if(sensorStateDX == 3 && sensorStateSX == 3){
    tmp = 10;
  }  //NO_LINE

   else if(sensorStateDX == 2 && sensorStateSX == 0){
    tmp = 8;
  }  //NO_LINE

   else if(sensorStateDX == 0 && sensorStateSX == 1){
    tmp = 9;
  }  //NO_LINE

   else if(sensorStateDX == 2 && sensorStateSX == 1){
    tmp = 4;
  }  //NO_LINE

   else if(sensorStateDX == 0 && sensorStateSX == 0){
    tmp = 11;
  }  //NO_LINE

   else if(sensorStateDX == 2 && sensorStateSX == 2){
    tmp = 3;
  }  //NO_LINE

   else if(sensorStateDX == 1 && sensorStateSX == 1){
    tmp = 3;
  }  //NO_LINE
  return tmp;
}

/*FUNZIONE LINEA SPEZZATA
  In questa funzione vien slavata l'ultima lettura della vairabile path
  il robot prosegue fino a quando non ritrova la linea, altrimenti....
  è da studiare in laboratorio
*/
int interrupt_line(int path){
  static int last_path_read = path;
    int last_path;
  if(last_path_read == last_path){
    //motorSpeed = motorSpeed / 2;
  }
  else exit;  
  return path;
}

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