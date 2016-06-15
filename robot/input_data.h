#ifndef __INPUT_DATA_H
#define __INPUT_DATA_H
#include <Arduino.h>

//controlla ostacoli sul percoso
bool check_obstacle(float dist_obs);

//restituisce il percoso leto dai linefollower
int read_path(int sensorStateDX, int sensorStateSX);

#endif