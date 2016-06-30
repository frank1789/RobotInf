#ifndef __FUNCTIONCONTROL_H
#define __FUNCTIONCONTROL_H
#include "input_data.h"
#include "pid.h"

//valuta l'errore sul percoso 
int path_error (int path);

//verifica che il valore di al motore non superi 255
uint8_t speed_control(uint8_t motorSpeed);
  
#endif