#include "MeOrion.h"
#include <SoftwareSerial.h>
#include "finite_state_machine.h"
#include "automatic.h"

//velocità motore massime
#define motorSpeedMAX   140
#define motorSpeedMIN  -140

MeLineFollower lineFinderDX(PORT_3); /* Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield. */
MeLineFollower lineFinderSX(PORT_4);

MeUltrasonicSensor ultraSensor(PORT_6); //Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield.

MeDCMotor motorDX(PORT_1);  // value: between -255 and 255.
MeDCMotor motorSX(PORT_2);  // value: between -255 and 255.

MeBluetooth bluetooth(PORT_5);

//dichiarazione state functions
void idle();
void start();
void message();
void line_follower();
void stop();

//dichirazione degli stati
State Init(0, stop, start, NULL);
State Idle(1, message, idle ,NULL);
State Line_Follower(2, line_follower);
State Stop(3, stop, start, NULL);

//implementatizone macchina a stati finiti
FiniteStateMachine stateMachine = FiniteStateMachine(&Init);

void setup()
{
	Serial.begin(115200);
	bluetooth.begin(115200);
	bluetooth.println("Bluetooth start!");
	message();
}

void loop()
{
	stateMachine.update();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void idle () 
{
	//Serial.println("Stato IDLE");
	stop();
	//Serial.println("motori fermi");
	if(bluetooth.available()) 
	{	
		char ch;
		ch = Serial.read();
		//static unsigned long buf = 0;
		//if(ch >= '0' && ch <= '9')
		//{
		//	buf = buf * 10 + ch - '0';
		//}

		//else 
		//{
			command_parsing(ch, 0);
		//	buf = 0;
		//}
	}
}

void start() 
{
	stateMachine.transitionTo(&Idle);
}

Automatic asimov = Automatic();

void line_follower()
{
	//Serial.println("Stato Line_Follower");
	//velocità base
	uint8_t motorSpeed = motorSpeedMAX;
	//PD varibili 
	static int last_error = 0;
	//lettura dai sensori
	asimov.setInputSensor(ultraSensor.distanceCm());
	/*	verifica costantemente se ci sono oggetti sul percorso e 
	 *	segue la linea se ci sono ostacoli torna inverte il senso di 
	 *	marcia
	*/
	if (asimov.getCheckObstacle() == true)
	{
		asimov.setInputLine(lineFinderDX.readSensors(),
                            lineFinderSX.readSensors());
		//analisi percorso
		if (asimov.getPathError() >= -4 && asimov.getPathError() <= 4)
		{
			int correction = 11 * asimov.getPathError() + 4 * (asimov.getPathError() - last_error);
			last_error = asimov.getPathError();
			motorDX.run(-motorSpeed - correction);
			motorSX.run( motorSpeed - correction);
		}
		else if(asimov.getPathError() == 5 && last_error < 0 )        // caso DX
		{
			motorSX.run(motorSpeedMAX/1.5);
			motorDX.run(motorSpeedMAX/1.5);
		}
		else if(asimov.getPathError() == 5 && last_error >= 0 )         // caso SX
		{
			motorDX.run(motorSpeedMIN/1.5);
			motorSX.run(motorSpeedMIN/1.5);
		}
		else if (asimov.getPathError() == 6 && (last_error < 0 || last_error > 0))
		{
			stop();
			stateMachine.transitionTo(&Idle);
		}
	}   
	else // presenza ostacoli
	{
		stop();
		last_error = 0;
		motorDX.run(-motorSpeed);
		motorSX.run(-motorSpeed);	
	}	
}

void stop()
{
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
		break;

		case 'w': //start line follower
			Serial.println("success w");
			motorDX.run(-motorSpeedMAX);
			motorSX.run( motorSpeedMAX);
		break;

		case 'd': //destra
			//Serial.println("success d");
			motorSX.run(motorSpeedMAX/1.5);
			motorDX.run(motorSpeedMAX/1.5);
			//stateMachine.transitionTo(&Line_Follower);
		break;

		case 'a': //sinistra
			//Serial.println("success a");
			motorDX.run(motorSpeedMIN/1.5);
			motorSX.run(motorSpeedMIN/1.5);
			//stateMachine.transitionTo(&Line_Follower);
		break;
	}
	delay(250);
	stateMachine.transitionTo(&Line_Follower);
}

void message()
{
	bluetooth.print("Ciao! Sono in attesa di un comando");
	bluetooth.println("puoi usare:");
	bluetooth.println(" w -> per partire");
	bluetooth.println(" d -> per girare a destra");    
	bluetooth.println(" a -> per girare a sinistra");
	bluetooth.println(" s -> per fermarti");
}
