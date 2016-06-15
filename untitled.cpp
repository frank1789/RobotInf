int   feed_spiral    (int a, int motorSpeedMAX);
  int 	feed_spiral2   (int a, int motorSpeedMAX);
  int   interrupt_line (int path);
  bool  crossbreed     ();



  














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