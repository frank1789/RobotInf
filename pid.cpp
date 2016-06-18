#include "pid.h"

uint8_t PIDvalue(int e){
	uint8_t Kp =	50;
	uint8_t Ki =	 0;
	uint8_t Kd =	 0;

	static uint8_t P = 0,
				   I = 0,
	 			   D = 0,
				   previousError = 0,
				   previousI = 0;
	
	P = e;
	I = I + e;
	D = e - previousError;
	previousError = e;
  
  return (Kp*P) + (Ki*I) + (Kd*D);
}

