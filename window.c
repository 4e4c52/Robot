#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "headers/constants.h"
#include "headers/map.h"
#include "headers/robot.h"
#include "headers/window.h"

/*
 * Load the SDL components
 * and perform some initialization
 *
 * @return SDL_surfaces pointer to the screen
 */
Surfaces load_surfaces(void) {
	
	Surfaces surfaces;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_WM_SetIcon(IMG_Load("sprites/exit_20.jpg"), NULL);
  surfaces.screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("Find the exit bot!", NULL);
  
  surfaces.wall = IMG_Load("sprites/wall_20.jpg");
  surfaces.exit = IMG_Load("sprites/exit_20.jpg");
  surfaces.bot[TOP] = IMG_Load("sprites/bot_top_20.gif");
  surfaces.bot[RIGHT] = IMG_Load("sprites/bot_right_20.gif");
  surfaces.bot[BOTTOM] = IMG_Load("sprites/bot_bottom_20.gif");
  surfaces.bot[LEFT] = IMG_Load("sprites/bot_left_20.gif");
  surfaces.footprint[TOP] = IMG_Load("sprites/footprint_top_20.jpg");
  surfaces.footprint[RIGHT] = IMG_Load("sprites/footprint_right_20.jpg");
  surfaces.footprint[BOTTOM] = IMG_Load("sprites/footprint_bottom_20.jpg");
  surfaces.footprint[LEFT] = IMG_Load("sprites/footprint_left_20.jpg");
  
  return surfaces;
  
}

void refresh_screen(Map map, Robot bot, Surfaces surfaces) {
	
	int i = 0, j = 0;
	
	/* Cleaning the screen */
  SDL_FillRect(surfaces.screen, NULL, SDL_MapRGB(surfaces.screen->format, 255, 255, 255));
  
  /* Showing the objects on the screen */
  for (i = 0 ; i < MAP_HEIGHT ; i++) {
    
  	for (j = 0 ; j < MAP_WIDTH ; j++) {
        
  		surfaces.position.x = i * BLOCK_SIZE;
      surfaces.position.y = j * BLOCK_SIZE;
        
      if (map.map[j][i] == 'x') {
      	SDL_BlitSurface(surfaces.wall, NULL, surfaces.screen, &surfaces.position);
      }
      else if (map.map[j][i] == 'S') {
      	SDL_BlitSurface(surfaces.exit, NULL, surfaces.screen, &surfaces.position);
      }
      else if (bot.posX == i && bot.posY == j) {
        	
      	switch (bot.direction) {
        		
        	case TOP:
        		SDL_BlitSurface(surfaces.bot[TOP], NULL, surfaces.screen, &surfaces.position);
        		break;
        		
        	case RIGHT:
        		SDL_BlitSurface(surfaces.bot[RIGHT], NULL, surfaces.screen, &surfaces.position);
        		break;
        			
        	case BOTTOM:
        		SDL_BlitSurface(surfaces.bot[BOTTOM], NULL, surfaces.screen, &surfaces.position);
        		break;
        			
        	case LEFT:
        		SDL_BlitSurface(surfaces.bot[LEFT], NULL, surfaces.screen, &surfaces.position);
        		break;	
        		
        }
        	
			}
			else if (bot.m[j][i] == 1) {
				
				switch (bot.mf[j][i]) {
        		
        	case TOP:
        		SDL_BlitSurface(surfaces.footprint[TOP], NULL, surfaces.screen, &surfaces.position);
        		break;
        		
        	case RIGHT:
        		SDL_BlitSurface(surfaces.footprint[RIGHT], NULL, surfaces.screen, &surfaces.position);
        		break;
        			
        	case BOTTOM:
        		SDL_BlitSurface(surfaces.footprint[BOTTOM], NULL, surfaces.screen, &surfaces.position);
        		break;
        			
        	case LEFT:
        		SDL_BlitSurface(surfaces.footprint[LEFT], NULL, surfaces.screen, &surfaces.position);
        		break;	
        		
        }
				
			}
      
		}
	    
	}
  
  /* Refreshing the screen */
	SDL_Flip(surfaces.screen);
	
}

void house_keeping(Surfaces surfaces) {
	
	int i = 0;
	
	SDL_FreeSurface(surfaces.wall);
	SDL_FreeSurface(surfaces.exit);
	
	for (i = 0; i < 4; i++) {
		SDL_FreeSurface(surfaces.bot[i]);
	}
	
	SDL_Quit();
	
}
