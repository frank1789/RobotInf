#ifndef __FUNCTIONCONTROL_H
  #define __FUNCTIONCONTROL_H

  #include <Arduino.h>

  int   path_type      (int sensorStateDX, int sensorStateSX);
  bool  check_obstacle (float dist_obs);
  int   feed_spiral    (int a, int motorSpeedMAX);
  int 	feed_spiral2   (int a, int motorSpeedMAX);
  int   interrupt_line (int path);
  bool  crossbreed     ();
  
#endif