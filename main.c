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
  
  /* Common Vars */
  Map map;
  Robot bot;
  Exit exit;
  
  /* Common Initializations */
  srand(time(NULL));
  map = read_map();
  exit = find_map_exit(map);
  bot = new_robot('O', 1);
  
  /* SDL Enabled */
	#ifdef SDL_ENABLED
  
  printf("\nNow looking for an exit to escape this shit...\nWatch me through the window!\n");
  
  int keep_running = 1;
  Surfaces surfaces;
  surfaces = load_surfaces();
  
  while (keep_running) {
    
    flush_robot_memory(bot);
    refresh_screen(map, bot, surfaces);
  
    while (bot.out == 0 && keep_running == 1) {
  	
  	  keep_running = manage_events(surfaces);  
      bot = move_robot(map, bot, exit);
  	  refresh_screen(map, bot, surfaces);
    
    }
    
    refresh_screen(map, bot, surfaces);
  
    keep_running = manage_controls(surfaces);
    
  }
  
  house_keeping(surfaces);
  
	#endif
  
  /* Terminal mod (SDL Disabled) */
  #ifndef SDL_ENABLED
  
  printf("\nNow looking for an exit to escape this shit...\n");
  
  flush_robot_memory(bot);
  show_map(map, bot);
  
  while (bot.out == 0) {
  
    SDL_Delay(TIME_BTW_MOVES);
    bot = move_robot(map, bot, exit);
    printf("\nPerformed %d moves...\n", bot.moves);
    show_map(map, bot);
    
  }  
  
  #endif
  
  /* Last message in the terminal */
  if (bot.out == 1) {
    printf("\nThe bot found the exit after %d moves!\n\n", bot.moves);
  }
  else {
    printf("\nSorry you had to stop the bot...\n\n");
  }
    
  return EXIT_SUCCESS;

}
