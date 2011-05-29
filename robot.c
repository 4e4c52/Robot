#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/constants.h"
#include "headers/map.h"
#include "headers/robot.h"

Robot new_robot(char name, int speed) {

  Robot bot;
  
  bot.name = name;
  bot.speed = speed;
  bot.posX = ROBOT_DEFAULT_X;
  bot.posY = ROBOT_DEFAULT_Y;
  bot.moves = 0;
  bot.direction = 0;
  bot.last_direction = 3;
  bot.dont_go = 0;
  bot.out = 0;
  
  return bot;
  
}

Robot move_robot(Map map, Robot bot, Exit exit) {

  // Checking in which direction we should go...
  int horizontalMove = 0;
  int verticalMove = 0;
  
  // Horizontal
  if (bot.posX > exit.x) horizontalMove = LEFT;
  else horizontalMove = RIGHT;
  // Vertical
  if (bot.posY > exit.y) verticalMove = TOP;
  else verticalMove = BOTTOM;
  
  // Now verifying where we can move...
  int availableMoves[4] = {0};
  
  // Top
  if (map.map[bot.posY - bot.speed][bot.posX] != 'x' 
  && bot.m[bot.posY - bot.speed][bot.posX] != 1) availableMoves[TOP] = 1;
  // Right
  if (map.map[bot.posY][bot.posX + bot.speed] != 'x'
  && bot.m[bot.posY][bot.posX + bot.speed] != 1) availableMoves[RIGHT] = 1;
  // Bottom
  if (map.map[bot.posY + bot.speed][bot.posX] != 'x' 
  && bot.m[bot.posY + bot.speed][bot.posX] != 1) availableMoves[BOTTOM] = 1;
  // Left
  if (map.map[bot.posY][bot.posX - bot.speed] != 'x'
  && bot.m[bot.posY][bot.posX - bot.speed] != 1) availableMoves[LEFT] = 1;
  
  // Now chosing the best move...
  
  // Starting by the directions where we should go
  if (availableMoves[verticalMove] == 1) {
  
    switch (verticalMove) {
      case TOP:
        bot.posY--;
        bot.last_direction = TOP;
        break;
      case BOTTOM:
        bot.posY++;
        bot.last_direction = BOTTOM;
        break;
    }
  
  }
  
  if (availableMoves[horizontalMove] == 1) {
  
    switch (horizontalMove) {
      case RIGHT:
        bot.posX++;
        bot.last_direction = RIGHT;
        break;
      case LEFT:
        bot.posX--;
        bot.last_direction = LEFT;
    }
  
  }
  // Doing it randomly
  else {
  
    int randomMove = 0, search = 1;
  
    while (search) {
      
    	// Searching for a good move...
      randomMove = (rand() % 4);
      switch (randomMove) {
        case TOP:
          if (map.map[bot.posY - bot.speed][bot.posX] != 'x' 
          && bot.m[bot.posY - bot.speed][bot.posX] != 1) search = 0;
          break;
        case RIGHT:
          if (map.map[bot.posY][bot.posX + bot.speed] != 'x' 
          && bot.m[bot.posY][bot.posX + bot.speed] != 1) search = 0;
          break;
        case BOTTOM:
          if (map.map[bot.posY + bot.speed][bot.posX] != 'x' 
          && bot.m[bot.posY + bot.speed][bot.posX] != 1) search = 0;
          break;
        case LEFT:
          if (map.map[bot.posY][bot.posX - bot.speed] != 'x' 
          && bot.m[bot.posY][bot.posX - bot.speed] != 1) search = 0;
          break;
      }
      
    }
    
    // And doing it!
    switch (randomMove) {
      case TOP:
        bot.posY--;
        bot.last_direction = TOP;
        break;
      case RIGHT:
        bot.posX++;
        bot.last_direction = RIGHT;
        break;
      case BOTTOM:
        bot.posY++;
        bot.last_direction = BOTTOM;
        break;
      case LEFT:
        bot.posX--;
        bot.last_direction = LEFT;
        break;
    }
  
  }
  
  // Remembering the position
  bot.m[bot.posY][bot.posX] = 1;
  bot.moves++;
  
  if (map.map[bot.posY][bot.posX] == 'S') {
    bot.out = 1;
  }
  
  return bot;

}
