#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL/SDL.h>
#include "headers/constants.h"
#include "headers/map.h"
#include "headers/robot.h"
#include "headers/window.h"

int main(int argc, char* argv[]) {
  
  /* Initializing the random generator */
  srand(time(NULL));
  
	#ifdef SDL_ENABLED
  
  Surfaces surfaces;
  Map map;
  Robot bot;
  Exit exit;
  
  surfaces = load_surfaces();
  map = read_map();
  bot = new_robot('O', 1);
  exit = find_map_exit(map);
  
  refresh_screen(map, bot, surfaces);
  
  while (bot.out == 0) {
  	
  	SDL_Delay(TIME_BTW_MOVES);
    bot = move_robot(map, bot, exit);
  	refresh_screen(map, bot, surfaces);
    
  }
  
  house_keeping(surfaces);
  
  printf("\nThe bot found the exit after %d moves!\n\n", bot.moves);
  
	#endif
  
  #ifndef SDL_ENABLED
  
  /* Vars */
  Map map;
  Robot bot;
  Exit exit;
  
  /* Reading the map */
  map = read_map();
  exit = find_map_exit(map);
  
  /* Creating the robot */
  bot = new_robot('O', 1);
  
  /* Showing the map */
  show_map(map, bot);
  
  /* Moving the bot! */
  while (bot.out == 0) {
  
    SDL_Delay(TIME_BTW_MOVES);
    bot = move_robot(map, bot, exit);
    show_map(map, bot);
    
  }  
  
  printf("\nThe bot found the exit after %d moves!\n\n", bot.moves);
  
  #endif
    
  return EXIT_SUCCESS;

}
