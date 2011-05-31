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
  
  /* Vars */
  Map map;
  Robot bot;
  Exit exit;
  int keep_window = 1, retry = 1;
  
  map = read_map();
  bot = new_robot('O', 1);
  exit = find_map_exit(map);
  
	#ifdef SDL_ENABLED
  
  Surfaces surfaces;
  
  surfaces = load_surfaces();
  
  while(retry) {
  
    refresh_screen(map, bot, surfaces);
  
    while (bot.out == 0) {
  	
  	  SDL_Delay(TIME_BTW_MOVES);
      bot = move_robot(map, bot, exit);
  	  refresh_screen(map, bot, surfaces);
    
    }
  
    /* Waiting loop */
    while (keep_window) {
  
      SDL_WaitEvent(&surfaces.event);
      printf ("event:%d\n",surfaces.event.type);fflush(stdout);
      switch (surfaces.event.type) {
    
        case SDL_QUIT:
          keep_window = 0;
          retry = 0;
          break;
            
        case SDL_KEYDOWN:
          switch(surfaces.event.key.keysym.sym) {
            case SDLK_ESCAPE:
              keep_window = 0;
              retry = 0;
              break;
            case SDLK_r:
              retry = 1;
              break;
          }
        break;
      
      }
    
    }
    
  }
  
  /* Cleaning all surfaces */
  house_keeping(surfaces);
  
	#endif
  
  #ifndef SDL_ENABLED
  
  /* Showing the map */
  show_map(map, bot);
  
  /* Moving the bot! */
  while (bot.out == 0) {
  
    SDL_Delay(TIME_BTW_MOVES);
    bot = move_robot(map, bot, exit);
    show_map(map, bot);
    
  }  
  
  #endif
  
  printf("\nThe bot found the exit after %d moves!\n\n", bot.moves);
    
  return EXIT_SUCCESS;

}
