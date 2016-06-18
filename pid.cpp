#include "pid.h"

uint8_t PIDvalue(int e){
	uint8_t Kp =	50;
	uint8_t Ki =	 0;
	uint8_t Kd =	 0;

	uint8_t P =	0;
	uint8_t I =	0;
	uint8_t D = 0;
	uint8_t previousError = 0;
	uint8_t previousI = 0;

	P = e;
  I = I + e;
  D = e - previousError;
  previousError = e;
  
  return (Kp*P) + (Ki*I) + (Kd*D);
}

