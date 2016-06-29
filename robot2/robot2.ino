#include "MeOrion.h"
#include <SoftwareSerial.h>
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

MeBluetooth bluetooth(PORT_5);

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
	bluetooth.begin(115200);
}

void loop()
{
	stateMachine.update();
	delay(2);
}

void idle () 
{
	Serial.println("Stato IDLE");
	motorDX.stop();
	motorSX.stop();
	Serial.println("motori fermi");

	if(bluetooth.available()) 
	{	

		char ch;
		ch = Serial.read();
		static unsigned long buf = 0;
		if(ch >= '0' && ch <= '9')
		{
			buf = buf * 10 + ch - '0';
		}

		else 
		{
			command_parsing(ch, buf);
			buf = 0;
		}
	}

	stateMachine.transitionTo(&Line_Follower);
}

void start() 
{
	delay(200);
	bluetooth.println("Ciao! Sono in attesa di un comando:");
	bluetooth.println("puoi usare:");
	bluetooth.println(" l -> per partire con il line follower");
	bluetooth.println(" d -> per girare a destra");	
	bluetooth.println(" a -> per girare a sinistra");
	bluetooth.println(" s -> per fermarti");
	stateMachine.transitionTo(&Idle);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void line_follower()
{
	Serial.println("Stato Line_Follower");
	//velocità base
	uint8_t motorSpeed = 100;
	//PD varibili 
	int last_error = 0;
	const uint8_t Kp =	8;
	const uint8_t Kd = 4;
	//lettura dal sensore a ultrasuoni
	float dist_obs = ultraSensor.distanceCm();
	//verifica costantemente se ci sono oggetti sul percorso e segue la linea se ci sono ostacoli torna in Idle
	if (check_obstacle (dist_obs) == true)
	{
		//lettura posizione dai sensori di linea
		int error = path_error(read_path(lineFinderDX.readSensors(), lineFinderSX.readSensors()));
		if (error >= -4 && error <= 4)
		{
			uint8_t correction = Kp * error + Kd * (error - last_error);
			last_error = error;
			motorDX.run(-motorSpeed - correction);
			motorSX.run( motorSpeed - correction);
		}

		else if (error == 5)
		{
			motorDX.run(motorSpeed);
			motorSX.run(motorSpeed);
		}	

		else if  (error == 6)
		{	
			stop();
			delay(200);
		 	motorDX.run(80);
		 	motorSX.run(10);
		// 	stateMachine.transitionTo(&Idle);
		}
	}
	
	else
	{
		stop();
		motorDX.run(motorSpeed);
		motorSX.run(motorSpeed);
	}
}

void stop(){
	Serial.println("Stato STOP");
	motorDX.stop();
	motorSX.stop();
}

void command_parsing(char ch, unsigned long val) 
{
	switch (ch) 
	{
		case 's': //stop
			bluetooth.println("success s");
			stateMachine.transitionTo(&Stop);
			// if(val > settings->min) 
			// {
			// 	settings->max = val;
			// }
			// PROMPT;
		break;

		// case 'i': //idle
		// 	Serial.println("success i");
		// 	// if(val < settings->max)
		// 	// {
		// 	// 	settings->min = val;
		// 	// }
		// 	// PROMPT;
		// break;

		case 'l': //start line follower
			bluetooth.println("success l");
			stateMachine.transitionTo(&Line_Follower);
			// settings->time_const = val;
			// PROMPT;
		break;

		case 'd': //destra
			bluetooth.println("success d");
			motorDX.run(-80);
			motorSX.run(40);
			stateMachine.transitionTo(&Line_Follower);
			// settings->blink_period = val;
			// PROMPT;
		break;

		case 'a': //sinistra
			bluetooth.println("success a");
			motorSX.run(80);
			motorDX.run(-40);
			stateMachine.transitionTo(&Line_Follower);
			// if(state_vars.stateBeforeIdle != &Idle)
			// {
			// 	state_vars.stateBeforeIdle = stateMachine.getCurrentState();
			// }
			// stateMachine.transitionTo(&Idle);
			// PROMPT;
		break;
	}
}