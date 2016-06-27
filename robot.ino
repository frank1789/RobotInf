#include "MeOrion.h"
#include "finite_state_machine.h"
#include "functioncontrol.h"

//velocità motore massime
#define motorSpeedMAX   255
#define motorSpeedMIN  -255

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

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  stateMachine.update();
  delay(20);
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void line_follower()
{
    Serial.println("Stato Line_Follower");

    uint8_t motorSpeed = 80;

    //lettura dal sensore a ultrasuoni
    float dist_obs = ultraSensor.distanceCm();

    //verifica costantemente se ci sono oggetti sul percorso e segue la linea se ci sono ostacoli torna in Idle
    if(check_obstacle (dist_obs) == true){
    //lettura posizione dai sensori di linea
    //int error = path_error(read_path(lineFinderDX.readSensors(), lineFinderSX.readSensors()));
    //motorDX.run(- motorSpeed);
    //motorSX.run(  motorSpeed);
        switch(read_path(lineFinderDX.readSensors(), lineFinderSX.readSensors()))
        {
            {
                case 1 : 
                Serial.println("GO_FORWARD");
                motorDX.run(-motorSpeed);
                motorSX.run( motorSpeed);
                break;

                case 2 : 
                Serial.println("TURN_LEFT_VERY_SOFT");
                motorDX.run(-motorSpeed - (motorSpeed * 0.20));
                motorSX.run( motorSpeed - (motorSpeed * 0.20));
                break;

                case 3 : 
                Serial.println("TURN_LEFT_SOFT");
                motorDX.run(-motorSpeed - (motorSpeed * 0.30));
                motorSX.run( motorSpeed - (motorSpeed * 0.30));

                break;

                case 4 : 
                Serial.println("TURN_LEFT_HARD");
                motorDX.run(-motorSpeed - (motorSpeed * 0.40));
                motorSX.run( motorSpeed - (motorSpeed * 0.40));

                break;

                case 5 : 
                Serial.println("TURN_LEFT_VERYHARD");
                motorDX.run(-motorSpeed + (motorSpeed * 0.50));
                motorSX.run( motorSpeed + (motorSpeed * 0.50));

                break;

                case 6 : 
                Serial.println("TURN_RIGHT_VERY_SOFT");
                motorDX.run(-motorSpeed + (motorSpeed * 0.20));
                motorSX.run( motorSpeed + (motorSpeed * 0.20));

                break;

                case 7 : 
                Serial.println("TURN_RIGHT_SOFT");
                motorDX.run(-motorSpeed + (motorSpeed * 0.30));
                motorSX.run( motorSpeed + (motorSpeed * 0.30));

                break;

                case 8 : 
                Serial.println("TURN_RIGHT_HARD");
                motorDX.run(-motorSpeed - (motorSpeed * 0.40));
                motorSX.run( motorSpeed - (motorSpeed * 0.40));
                break;

                case 9:
                Serial.println("TURN_RIGHT_VERYHARD");
                motorDX.run(-motorSpeed + (motorSpeed * 0.50));
                motorSX.run( motorSpeed + (motorSpeed * 0.50));
                break;

                case 10:
                Serial.println("NO_LINE");
                motorDX.stop();
                motorSX.stop();
                break;

                case 11:
                break;

                case 12:
                break;

                case 13:
                break;

                case 14:
                break;

                case 15:
                break;

                case 16:
                break;

                default: 
                break;
            }
        }
    else
    {
    Serial.println("ostacoli sul percorso");
    stateMachine.transitionTo(&Idle);
    }
}

void stop()
{
	Serial.println("Stato STOP");
  motorDX.stop();
  motorSX.stop();
}
