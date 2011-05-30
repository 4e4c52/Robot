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
  int is_stuck;
  char m[MAP_HEIGHT][MAP_WIDTH];
  char mf[MAP_HEIGHT][MAP_WIDTH];
  int out;
  
};

typedef struct Robot Robot;

/* Prototypes */
Robot new_robot(char name, int speed);
Robot move_robot(Map map, Robot bot, Exit exit);
int will_be_stuck(Map map, Robot bot, int direction);
int is_corridor(Map map, Robot bot, int direction);

#endif
