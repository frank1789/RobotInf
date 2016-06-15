#include "MeOrion.h"
#include "finite_state_machine.h"
#include "functioncontrol.h"
#include "pid.h"

MeLineFollower lineFinderDX(PORT_3); /* Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield. */
MeLineFollower lineFinderSX(PORT_4);

MeUltrasonicSensor ultraSensor(PORT_6); //Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield.

MeDCMotor motorDX(M1);  // value: between -255 and 255.
MeDCMotor motorSX(M2);  // value: between -255 and 255.

//dichiarazione state functions
  void idle();
  void start();
  void line_follower();
  void stop();

//dichirazione degli stati
  State Init(0, stop, start, NULL);
  State Idle(1, idle);
  State Line_Follower(2, line_follower);
  State Stop(3, stop, idle, NULL);

//immplementatizone macchina a stati finiti
  FiniteStateMachine stateMachine = FiniteStateMachine(&Init);

//velocità motore massime
  uint8_t const motorSpeedMAX =  255;
  uint8_t const motorSpeedMIN = -255;

void setup()
{
  Serial.begin(115200);  
}

void loop()
{
  stateMachine.update();
  delay(200);
}
/*
//Funzione risoluzione percorso
void solve_path(int path){
  switch(path)
  {
    case 1 : {
      Serial.println("VAI DRITTO!!");
      motorDX.run(-motorSpeed);
      motorSX.run( motorSpeed);
      
      break;
    }
    
    case 2 : {
      Serial.println("Turning left SOFT");
      motorDX.run(-motorSpeed - (motorSpeed * 0.30));
      motorSX.run( motorSpeed - (motorSpeed * 0.30));
      
      
    }
    
    case 3 : {
      Serial.println("Turning left HARD");
      motorDX.run(-motorSpeed - (motorSpeed * 0.40));
      motorSX.run( motorSpeed - (motorSpeed * 0.40));
      
      break;
    }
    
    case 4 : {
      Serial.println("Turning left VERY HARD");
      motorDX.run(-motorSpeed - (motorSpeed * 0.50));
      motorSX.run( motorSpeed - (motorSpeed * 0.50));
      
      break;
    }

    case 5 : {
      Serial.println("Turning right SOFT");
      motorDX.run(-motorSpeed + (motorSpeed * 0.30));
      motorSX.run( motorSpeed + (motorSpeed * 0.30));
      
      break;
    }
    
    case 6 : {
      Serial.println("Turning right HARD");
      motorDX.run(-motorSpeed + (motorSpeed * 0.40));
      motorSX.run( motorSpeed + (motorSpeed * 0.40));
      
      break;
    }
    
    case 7 : {
      Serial.println("Turning right VERY HARD");
      motorDX.run(-motorSpeed + (motorSpeed * 0.50));
      motorSX.run( motorSpeed + (motorSpeed * 0.50));
      
      break;
    }

    case 8 : {
      Serial.println("Turning left VERY SOFT");
      motorDX.run(-motorSpeed - (motorSpeed * 0.20));
      motorSX.run( motorSpeed - (motorSpeed * 0.20));

      
    }break;
     
    case 9: {
      Serial.println("Turning right VERY SOFT");
      motorDX.run(-motorSpeed + (motorSpeed * 0.20));
      motorSX.run( motorSpeed + (motorSpeed * 0.20));
  		
	}break;

	 case 10: {
    motorDX.stop();
    motorSX.stop();
    
    }break;
    
    case 11 : {
    	delay(1000);
    	if(path == 11){
    		Serial.println("non trovo il percorso, deve partire la ricerca a spirale");
			//fuori dalla linea, ne cerca una con movimento a spirale
			Serial.println("sto cercando il percorso");
			motorDX.run(-feed_spiral(110, motorSpeedMAX));
			motorSX.run(feed_spiral2(20, motorSpeedMAX)); //aumento solo questa velocità per generare il movimeto a spirale
		}else stateMachine.transitionTo(&Idle);
		
    }break;

    default: stateMachine.transitionTo(&Stop); break;
  }
}
*/
void idle () {
  Serial.println("Stato IDLE");
  motorDX.stop();
  motorSX.stop();
  Serial.println("motori fermi");

  stateMachine.transitionTo(&Line_Follower);
}

void start() {
	stateMachine.transitionTo(&Idle);
}

void line_follower(){
  Serial.println("Stato Line_Follower");

  uint8_t motorSpeed = 40;
  
  //lettura posizione dai sensori di linea
  int sensorStateDX = lineFinderDX.readSensors();
  int sensorStateSX = lineFinderSX.readSensors();
  
  //lettura dal sensore a ultrasuoni
  float dist_obs = ultraSensor.distanceCm();

  //verifica costantemente se ci sono oggetti sul percorso e segue la linea se ci sono ostacoli torna in Idle
  if (check_obstacle (dist_obs) == true){
    int path  = read_path(sensorStateDX, sensorStateSX);
    int error = path_error(path);
    motorDX.run(-motorSpeed - calculatePID(error));
    motorDX.run( motorSpeed - calculatePID(error));
  }
  else {
    Serial.println("ostacoli sul percorso");
    stateMachine.transitionTo(&Idle);
  }
}

void stop(){
	Serial.println("Stato STOP");
  motorDX.stop();
  motorSX.stop();
}
