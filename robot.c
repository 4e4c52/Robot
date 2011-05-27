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
  bot.last_direction = 0;
  bot.out = 0;
  
  return bot;
  
}

Robot move_robot(Map map, Robot bot, Exit exit) {

  // Going to the right if needed and possible...
  if (bot.posX < (exit.x - 1) && map.map[bot.posY][bot.posX + 1] != 'x' && bot.last_direction != LEFT) {
    // Move right
    bot.posX++;
  } 
  // Going to the bottom if needed and possible...
  else if (bot.posY < (exit.y - 1) && map.map[bot.posY + 1][bot.posX] != 'x' && bot.last_direction != TOP) {
   // Going down
   bot.posY++;
  }
  // Going to the left if needed and possible...
  else if (bot.posX > (exit.x - 1) && map.map[bot.posY][bot.posX - 1] != 'x' && bot.last_direction != RIGHT) {
    // Move left
    bot.posX--;
  }  
  // Going to the top if needed and possible...
  else if (bot.posY > (exit.y - 1) && map.map[bot.posY - 1][bot.posX] != 'x' && bot.last_direction != BOTTOM) {
    // Going up
    bot.posY--;
  }
  else {
  
    // Going to the right if possible...
    if (map.map[bot.posY][bot.posX + 1] != 'x' && bot.last_direction != LEFT) {
      // Move right
      bot.posX++;
      bot.last_direction = RIGHT;
    } 
    // Going to the bottom if possible...
    else if (map.map[bot.posY + 1][bot.posX] != 'x' && bot.last_direction != TOP) {
      // Going down
      bot.posY++;
      bot.last_direction = BOTTOM;
    }
    // Going to the left if possible...
    else if (map.map[bot.posY][bot.posX - 1] != 'x' && bot.last_direction != RIGHT) {
      // Move left
      bot.posX--;
      bot.last_direction = LEFT;
    }  
    // Going to the top if possible...
    else if (map.map[bot.posY - 1][bot.posX] != 'x' && bot.last_direction != BOTTOM) {
      // Going up
      bot.posY--;
      bot.last_direction = TOP;
    }
    
  }
  
  bot.moves++;
  
  if (map.map[bot.posY][bot.posX] == 'S') {
    bot.out = 1;
  }
  
  return bot;

}
