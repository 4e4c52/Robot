#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/constants.h"
#include "headers/map.h"
#include "headers/robot.h"

/*
 * Create a new robot
 *
 * @return Robot structure
 */
Robot new_robot(char name, int speed) {

  Robot bot;
  
  bot.name = name;
  bot.speed = speed;
  bot.posX = ROBOT_DEFAULT_X;
  bot.posY = ROBOT_DEFAULT_Y;
  bot.is_stuck = 0;
  bot.is_random = 0;
  bot.random_count = 0;
  bot.moves = 0;
  bot.direction = 0;
  bot.out = 0;
  
  return bot;
  
}

/*
 * Move the robot on the map
 * by calculating the availables moves
 * regarding the exit coordinates of the map
 *
 * @return Robot structure containing the updated position of the robot
 */
Robot move_robot(Map map, Robot bot, Exit exit) {

  // Checking in which direction we should go...
  int horizontalMove = 0;
  int verticalMove = 0;
  
  // Horizontal
  if (bot.posX == exit.x) horizontalMove = -1;
  else if (bot.posX > exit.x) horizontalMove = LEFT;
  else horizontalMove = RIGHT;
  // Vertical
  if (bot.posY == exit.y) verticalMove = -1;
  else if (bot.posY > exit.y) verticalMove = TOP;
  else verticalMove = BOTTOM;
  
  // Now verifying where we can move...
  int availableMoves[4] = {0};
  int is_stuck = 1;
  
  // Top
  if (
    map.map[bot.posY - bot.speed][bot.posX] != 'x' 
    && bot.m[bot.posY - bot.speed][bot.posX] != 1
    && !will_be_stuck(map, bot, TOP)
    //&& !is_corridor(map, bot, TOP)
  ) { availableMoves[TOP] = 1; is_stuck = 0; }
  // Right
  if (
    map.map[bot.posY][bot.posX + bot.speed] != 'x'
    && bot.m[bot.posY][bot.posX + bot.speed] != 1
    && !will_be_stuck(map, bot, RIGHT)
    //&& !is_corridor(map, bot, RIGHT)
  ) { availableMoves[RIGHT] = 1; is_stuck = 0; }
  // Bottom
  if (
    map.map[bot.posY + bot.speed][bot.posX] != 'x' 
    && bot.m[bot.posY + bot.speed][bot.posX] != 1
    && !will_be_stuck(map, bot, BOTTOM)
    //&& !is_corridor(map, bot, BOTTOM)
  ) { availableMoves[BOTTOM] = 1; is_stuck = 0; }
  // Left
  if (
    map.map[bot.posY][bot.posX - bot.speed] != 'x'
    && bot.m[bot.posY][bot.posX - bot.speed] != 1
    && !will_be_stuck(map, bot, LEFT)
    //&& !is_corridor(map, bot, LEFT)
  ) { availableMoves[LEFT] = 1; is_stuck = 0; }
  
  bot.is_stuck = is_stuck;
   
  // Now chosing the best move...
  
  // Starting by the directions where we should go
  if (horizontalMove != -1 && availableMoves[horizontalMove] == 1) {
  
    switch (horizontalMove) {
      case RIGHT:
        bot.posX++;
        bot.direction = RIGHT;
        break;
      case LEFT:
        bot.posX--;
        bot.direction = LEFT;
        break;
    }
  
  }
  else if (verticalMove != -1 && availableMoves[verticalMove] == 1) {
  
    switch (verticalMove) {
      case TOP:
        bot.posY--;
        bot.direction = TOP;
        break;
      case BOTTOM:
        bot.posY++;
        bot.direction = BOTTOM;
        break;
    }
  
  } 
  // Doing it randomly
  else {
  
    int randomMove = 0, search = 1, firstLap = 1;
  
    // Searching for a good move...
    while (search) {
      
      randomMove = (rand() % 4);
      if (firstLap && bot.random_count < ROBOT_MAX_RANDOM){
        randomMove = bot.direction;
        bot.random_count++;
      }
      else {
        bot.random_count = 0;
      }
      
      switch (randomMove) {
        case TOP:
          if (
            map.map[bot.posY - bot.speed][bot.posX] != 'x' 
            && bot.m[bot.posY - bot.speed][bot.posX] != 1
            && !will_be_stuck(map, bot, TOP)
            //&& !is_corridor(map, bot, TOP)
          ) { search = 0; bot.direction = TOP; }
          else if (
            map.map[bot.posY - bot.speed][bot.posX] != 'x' 
            //&& !will_be_stuck(map, bot, TOP)
            //&& !is_corridor(map, bot, TOP)
            && bot.is_stuck == 1
          ) { search = 0; bot.direction = TOP; }
          break;
        case RIGHT:
          if (
            map.map[bot.posY][bot.posX + bot.speed] != 'x' 
            && bot.m[bot.posY][bot.posX + bot.speed] != 1
            && !will_be_stuck(map, bot, RIGHT)
            //&& !is_corridor(map, bot, RIGHT)
          ) { search = 0; bot.direction = RIGHT; }
          else if (
            map.map[bot.posY][bot.posX + bot.speed] != 'x' 
            //&& !will_be_stuck(map, bot, RIGHT)
            //&& !is_corridor(map, bot, RIGHT)
            && bot.is_stuck == 1
          ) { search = 0; bot.direction = RIGHT; }
          break;
        case BOTTOM:
          if (
            map.map[bot.posY + bot.speed][bot.posX] != 'x' 
            && bot.m[bot.posY + bot.speed][bot.posX] != 1
            && !will_be_stuck(map, bot, BOTTOM)
            //&& !is_corridor(map, bot, BOTTOM)
          ) { search = 0; bot.direction = BOTTOM; }
          else if (
            map.map[bot.posY + bot.speed][bot.posX] != 'x' 
            //&& !will_be_stuck(map, bot, BOTTOM)
            //&& !is_corridor(map, bot, BOTTOM)
            && bot.is_stuck == 1
          ) { search = 0; bot.direction = BOTTOM; }
          break;
        case LEFT:
          if (
            map.map[bot.posY][bot.posX - bot.speed] != 'x' 
            && bot.m[bot.posY][bot.posX - bot.speed] != 1
            && !will_be_stuck(map, bot, LEFT)
            //&& !is_corridor(map, bot, LEFT)
          ) { search = 0; bot.direction = LEFT; }
          else if (
            map.map[bot.posY][bot.posX - bot.speed] != 'x' 
            //&& !will_be_stuck(map, bot, LEFT)
            //&& !is_corridor(map, bot, LEFT)
            && bot.is_stuck == 1
          ) { search = 0; bot.direction = LEFT; }
          break;
      }
      
      firstLap = 0;
      
    }
    
    // And doing it!
    switch (randomMove) {
      case TOP:
        bot.posY--;
        break;
      case RIGHT:
        bot.posX++;
        break;
      case BOTTOM:
        bot.posY++;
        break;
      case LEFT:
        bot.posX--;
        break;
    }
  
  }
  
  // Remembering the position
  bot.m[bot.posY][bot.posX] = 1;
  bot.footprints[bot.posY][bot.posX] = bot.direction;
  bot.moves++;
  printf("#moves: %d\n", bot.moves);
  
  // Is the bot out?
  if (map.map[bot.posY][bot.posX] == 'S') {
    bot.out = 1;
  }
  
  return bot;

}

/*
 * Check if the next move in the given direction
 * will stuck the robot
 *
 * @return int 0 = not stuck, 1 = stuck
 */
int will_be_stuck(Map map, Robot bot, int direction) {
	
	int stuck = 0;
	
	if (
	  map.map[bot.posY][bot.posX + 1] == 'S' 
	  || map.map[bot.posY + 1][bot.posX] == 'S'
	  || map.map[bot.posY][bot.posX + 1] == 'S'
	  || map.map[bot.posY - 1][bot.posX] == 'S'
	 ) return stuck;
	
	switch (direction) {
		
		case TOP:
			if (
			  (map.map[bot.posY - bot.speed - 1][bot.posX] == 'x' 
			  || bot.m[bot.posY - bot.speed - 1][bot.posX] == 1) 
			  && (map.map[bot.posY - bot.speed][bot.posX - bot.speed] == 'x' 
			  || bot.m[bot.posY - bot.speed][bot.posX - bot.speed] == 1) 
			  && (map.map[bot.posY - bot.speed][bot.posX + bot.speed] == 'x' 
			  || bot.m[bot.posY - bot.speed][bot.posX + bot.speed] == 1)
			) stuck = 1;
			break;
			
		case RIGHT:
			if (
			  (map.map[bot.posY][bot.posX + bot.speed + 1] == 'x' 
			  || bot.m[bot.posY][bot.posX + bot.speed + 1] == 1) 
			  && (map.map[bot.posY - 1][bot.posX + bot.speed] == 'x' 
			  || bot.m[bot.posY - 1][bot.posX + bot.speed] == 1) 
			  && (map.map[bot.posY + 1][bot.posX + bot.speed] == 'x' 
			  || bot.m[bot.posY + 1][bot.posX + bot.speed] == 1)
			) stuck = 1;
			break;
			
		case BOTTOM:
			if (
			  (map.map[bot.posY + bot.speed + 1][bot.posX] == 'x' 
			  || bot.m[bot.posY + bot.speed + 1][bot.posX] == 1) 
			  && (map.map[bot.posY + bot.speed][bot.posX - bot.speed] == 'x' 
			  || bot.m[bot.posY + bot.speed][bot.posX - bot.speed] == 1) 
			  && (map.map[bot.posY + bot.speed][bot.posX + bot.speed] == 'x' 
			  || bot.m[bot.posY + bot.speed][bot.posX + bot.speed] == 1)
			) stuck = 1;
			break;
			
		case LEFT:
			if (
			  (map.map[bot.posY][bot.posX - bot.speed - 1] == 'x' 
			  || bot.m[bot.posY][bot.posX - bot.speed - 1] == 1) 
			  && (map.map[bot.posY - 1][bot.posX - bot.speed] == 'x' 
			  || bot.m[bot.posY - 1][bot.posX - bot.speed] == 1) 
			  && (map.map[bot.posY + 1][bot.posX - bot.speed] == 'x' 
			  || bot.m[bot.posY + 1][bot.posX - bot.speed] == 1)
			) stuck = 1;
			break;
		
	}
	
	return stuck;
	
}

/*
 * Flush the robot memory
 *
 * @return void
 */
void flush_robot_memory(Robot bot) {

  int i = 0, j = 0;
  
  for (i = 0; i < MAP_HEIGHT; i++) {
  
    for (j = 0; j < MAP_WIDTH; j++) {
    
      bot.m[i][j] = 0 ;
      
    }
    
  }
  
  bot.out = 0;
  bot.moves = 0;

}

/*
 * Check if the next move in the given direction
 * will engage the bot in a corridor
 *
 * @return int 0 = not a corridor, 1 = corridor
 * @deprecated
 */
int is_corridor(Map map, Robot bot, int direction) {
	
	int corridor = 0;
	
	switch (direction) {
		
		case TOP:
			if ( 
			(bot.m[bot.posY - bot.speed][bot.posX - bot.speed] == 1 
			&& bot.m[bot.posY - bot.speed][bot.posX + bot.speed] == 1)
			|| (bot.m[bot.posY - bot.speed - 1][bot.posX - bot.speed] == 1 
			&& bot.m[bot.posY - bot.speed - 1][bot.posX + bot.speed] == 1)
			) corridor = 1;
			break;
			
		case RIGHT:
			if (
			(bot.m[bot.posY - 1][bot.posX + bot.speed] == 1 
		  && bot.m[bot.posY + 1][bot.posX + bot.speed] == 1)
		  || (bot.m[bot.posY - 1][bot.posX + bot.speed + 1] == 1
		  && bot.m[bot.posY + 1][bot.posX + bot.speed + 1] == 1)
		  ) corridor = 1;
			break;
			
		case BOTTOM:
			if ( 
			(bot.m[bot.posY + bot.speed][bot.posX - bot.speed] == 1 
			&& bot.m[bot.posY + bot.speed][bot.posX + bot.speed] == 1) 
			|| (bot.m[bot.posY + bot.speed + 1][bot.posX - bot.speed] == 1 
			&& bot.m[bot.posY + bot.speed + 1][bot.posX + bot.speed] == 1)
			) corridor = 1;
			break;
			
		case LEFT:
			if (
			(bot.m[bot.posY - 1][bot.posX - bot.speed] == 1
		  && bot.m[bot.posY + 1][bot.posX - bot.speed] == 1) 
		  || (bot.m[bot.posY - 1][bot.posX - bot.speed - 1] == 1 
		  && bot.m[bot.posY + 1][bot.posX - bot.speed - 1] == 1)
		  ) corridor = 1;
			break;
		
	}
	
	return corridor;
	
}
