#ifndef ROBOT_H
#define ROBOT_H
//#include "map.h"

/* Struc describing the robot */

struct Robot {

  char name;
  int posX;
  int posY;
  int moves;
  int speed;
  int direction; 
  int last_direction;
  int out;
  
};

typedef struct Robot Robot;

/* Prototypes */
Robot new_robot(char name, int speed);
Robot move_robot(Map map, Robot bot, Exit exit);

#endif
