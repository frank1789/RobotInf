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
State Idle(1, message, idle ,NULL);
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
}

void idle ()
{
	Serial.println("Stato IDLE");
	motorDX.stop();
	motorSX.stop();
	Serial.println("motori fermi");
	if(Serial.available()) 
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
}

void start()
{
	stateMachine.transitionTo(&Idle);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
			stop();
			last_error = 0;
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
}

void command_parsing(char ch, unsigned long val) 
{
	switch (ch) 
	{
		case 's': //stop
			Serial.println("success s");
			stateMachine.transitionTo(&Stop);
			// if(val > settings->min) 
			// {
			// 	settings->max = val;
			// }
			// PROMPT;
		break;

		case 'l': //start line follower
			Serial.println("success l");
			stateMachine.transitionTo(&Line_Follower);
			// settings->time_const = val;
			// PROMPT;
		break;

		case 'd': //destra
			Serial.println("success d");
			motorSX.run(motorSpeedMAX/1.5);
			motorDX.run(motorSpeedMAX/1.5);
			stateMachine.transitionTo(&Line_Follower);
			// settings->blink_period = val;
			// PROMPT;
		break;

		case 'a': //sinistra
			Serial.println("success a");
			motorDX.run(motorSpeedMIN/1.5);
			motorSX.run(motorSpeedMIN/1.5);
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