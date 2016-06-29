#ifndef __INPUT_DATA_H
#define __INPUT_DATA_H
#include <Arduino.h>

//controlla ostacoli sul percoso
bool check_obstacle(float dist_obs);

//restituisce il percoso leto dai linefollower
uint8_t read_path(uint8_t sensorStateDX, uint8_t sensorStateSX);

#endif