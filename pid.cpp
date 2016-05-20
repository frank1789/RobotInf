#include "pid.h"

uint8_t calculatePID(int e)
{
  P = e;
  I = I + e;
  D = e-previousError;
  PIDvalue = (Kp*P) + (Ki*I) + (Kd*D);
  previousError = e;
  
  return PIDvalue;
}

