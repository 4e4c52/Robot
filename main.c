#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/constants.h"
#include "headers/map.h"
#include "headers/robot.h"
#include "SDL/SDL.h"

int main(int argc, char* argv[]) {

  /* Vars */
  Map map;
  Robot bot;
  Exit exit;
  
  //printf("\n%dx%d\n", exit.y, exit.x);
  
  /* Reading the map */
  map = read_map();
  exit = find_map_exit(map);
  
  /* Creating the robot */
  bot = new_robot('R', 1);
  
  /* Showing the map */
  show_map(map, bot);
  
  /* Moving the bot! */
  while (bot.out == 0) {
  
    SDL_Delay(100);
    bot = move_robot(map, bot, exit);
    show_map(map, bot);
    
  }
  
  
  printf("\nThe bot found the exit after %d moves!\n\n", bot.moves);
    
  return 0;

}
