#ifndef __PID_H
  #define __PID_H

  #include <Arduino.h>

float Kp=50;
float Ki=0;
float Kd=0;

int e=0;
int P=0;
int I=0;
int D=0;
int PIDvalue=0;
float previousError=0;
float previousI=0;

uint8_t calculatePID(int e);

#endif
