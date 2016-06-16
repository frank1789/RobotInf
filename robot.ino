#include "MeOrion.h"

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "finite_state_machine.h"
#include "functioncontrol.h"
#include "pid.h"

MeLineFollower lineFinderDX(PORT_3); /* Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield. */
MeLineFollower lineFinderSX(PORT_4);

MeUltrasonicSensor ultraSensor(PORT_6); //Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield.

MeDCMotor motorDX(PORT_1);  // value: between -255 and 255.
MeDCMotor motorSX(PORT_2);  // value: between -255 and 255.

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
  delay(2);
}

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
    motorSpeed = motorSpeed - calculatePID(error);
    motorDX.run(-motorspeed(motorSpeed));
    motorSX.run( motorspeed(motorSpeed));
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