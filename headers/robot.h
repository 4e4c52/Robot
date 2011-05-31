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
  int random_count;
  char m[MAP_HEIGHT][MAP_WIDTH];
  int out;
  
  /* SDL vars */
  char footprints[MAP_HEIGHT][MAP_WIDTH];
  int is_random;
  int vertical;
  int horizontal;
  
};

typedef struct Robot Robot;

/* Prototypes */
Robot new_robot(char name, int speed);
Robot move_robot(Map map, Robot bot, Exit exit);
int will_be_stuck(Map map, Robot bot, int direction);
void flush_robot_memory(Robot bot);

#endif
