#include "MeOrion.h"
#include "finite_state_machine.h"
#include "functioncontrol.h"

//velocità motore massime
#define motorSpeedMAX   140
#define motorSpeedMIN  -140

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
<<<<<<< Updated upstream
    stateMachine.update();
}

void idle ()
{
    Serial.println("Stato IDLE");
    motorDX.stop();
    motorSX.stop();
    Serial.println("motori fermi");

    stateMachine.transitionTo(&Line_Follower);
}

void start()
{
    stateMachine.transitionTo(&Idle);
=======
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
>>>>>>> Stashed changes
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

<<<<<<< Updated upstream
void line_follower()
{
    Serial.println("Stato Line_Follower");
    uint8_t motorSpeed = motorSpeedMAX;
    //lettura dal sensore a ultrasuoni
    float dist_obs = ultraSensor.distanceCm();
    static int last_error = 0;
    //verifica costantemente se ci sono oggetti sul percorso e segue la linea se ci sono ostacoli torna in Idle
    if (check_obstacle (dist_obs) == true)
    {
        //lettura posizione dai sensori di linea
        int error = path_error(read_path(lineFinderDX.readSensors(), lineFinderSX.readSensors()));
        if (error >= -4 && error <= 4)
        {
            int correction = 11 * error + 4 * (error - last_error);
            last_error = error;
            motorDX.run(-motorSpeed - correction);
            motorSX.run( motorSpeed - correction);
        }
        else if(error == 5 && last_error < 0 )        // caso DX
        {
            motorSX.run(motorSpeedMAX/1.5);
            motorDX.run(motorSpeedMAX/1.5);
        }
        else if(error == 5 && last_error >= 0 )         // caso SX
        {
            motorDX.run(motorSpeedMIN/1.5);
            motorSX.run(motorSpeedMIN/1.5);
        }
        else if (error == 6)
        {

            if(crossbreed() == 1)
            {
                motorDX.run( motorSpeed);
                motorSX.run(-motorSpeed);
            }
            else
            {
                motorDX.run(-motorSpeed);
                motorSX.run( motorSpeed);
            }
        }
    }   
    else
    {
        stop();
        last_error = 0;
        motorDX.run(-motorSpeed);
        motorSX.run(-motorSpeed);	
    }	
}

void stop()
{
    Serial.println("Stato STOP");
    motorDX.stop();
    motorSX.stop();
=======
void line_follower(){
  Serial.println("Stato Line_Follower");

  uint8_t motorSpeed = 120;

  //lettura dal sensore a ultrasuoni
  float dist_obs = ultraSensor.distanceCm();
  int last_error = 0;
  //verifica costantemente se ci sono oggetti sul percorso e segue la linea se ci sono ostacoli torna in Idle
  if (check_obstacle (dist_obs) == true){
    //lettura posizione dai sensori di linea
    int error = path_error(read_path(lineFinderDX.readSensors(), lineFinderSX.readSensors()));
    int correction= 10 * error + 6 * (error - last_error);
    last_error = error;
    motorDX.run(-motorSpeed - correction);
    motorSX.run( motorSpeed - correction);
  }
else{
  Serial.println("ostacoli sul percorso");
  stateMachine.transitionTo(&Idle);
	}
}

void stop(){
	Serial.println("Stato STOP");
  motorDX.stop();
  motorSX.stop();
>>>>>>> Stashed changes
}