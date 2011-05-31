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
	char fileName[100] = {0};

  SDL_Init(SDL_INIT_VIDEO);
  
  sprintf(fileName,"sprites/wall_%d.jpg", BLOCK_SIZE);
  SDL_WM_SetIcon(IMG_Load(fileName), NULL);
  
  surfaces.screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("Find the exit bot!", NULL);
  
  surfaces.wall = IMG_Load(fileName);
  
  sprintf(fileName,"sprites/exit_%d.jpg", BLOCK_SIZE);
  surfaces.exit = IMG_Load("sprites/exit_20.jpg");
  
  sprintf(fileName,"sprites/bot_top_%d.gif", BLOCK_SIZE);
  surfaces.bot[TOP] = IMG_Load(fileName);
  
  sprintf(fileName,"sprites/bot_right_%d.gif", BLOCK_SIZE);
  surfaces.bot[RIGHT] = IMG_Load(fileName);
  
  sprintf(fileName,"sprites/bot_bottom_%d.gif", BLOCK_SIZE);
  surfaces.bot[BOTTOM] = IMG_Load(fileName);
  
  sprintf(fileName,"sprites/bot_left_%d.gif", BLOCK_SIZE);
  surfaces.bot[LEFT] = IMG_Load(fileName);
  
  sprintf(fileName,"sprites/footprint_top_%d.jpg", BLOCK_SIZE);
  surfaces.footprint[TOP] = IMG_Load(fileName);
  
  sprintf(fileName,"sprites/footprint_right_%d.jpg", BLOCK_SIZE);
  surfaces.footprint[RIGHT] = IMG_Load(fileName);
  
  sprintf(fileName,"sprites/footprint_bottom_%d.jpg", BLOCK_SIZE);
  surfaces.footprint[BOTTOM] = IMG_Load(fileName);
  
  sprintf(fileName,"sprites/footprint_left_%d.jpg", BLOCK_SIZE);
  surfaces.footprint[LEFT] = IMG_Load(fileName);
  
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
				
				switch (bot.footprints[j][i]) {
        		
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
