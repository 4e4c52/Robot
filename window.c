#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
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
  TTF_Init();
  
  SDL_WM_SetIcon(IMG_Load("sprites/wall_34.jpg"), NULL);
  
  surfaces.screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  SDL_WM_SetCaption("Find the exit bot!", NULL);
  
  sprintf(fileName,"sprites/wall_%d.jpg", BLOCK_SIZE);
  surfaces.wall = IMG_Load(fileName);
  
  sprintf(fileName,"sprites/exit_%d.jpg", BLOCK_SIZE);
  surfaces.exit = IMG_Load(fileName);
  
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
  
  surfaces.font = TTF_OpenFont("fonts/monospace.ttf", 15);
  
  SDL_Color font_color = {0, 0, 0};
  TTF_SetFontStyle(surfaces.font, TTF_STYLE_BOLD);
  surfaces.moves = TTF_RenderText_Blended(surfaces.font, "Moves: 0", font_color);
  surfaces.random = TTF_RenderText_Blended(surfaces.font, "Random: NO", font_color);
  surfaces.vertical = TTF_RenderText_Blended(surfaces.font, "Vertical: NONE", font_color);
  surfaces.horizontal = TTF_RenderText_Blended(surfaces.font, "Horizontal: NONE", font_color);
  surfaces.found = TTF_RenderText_Blended(surfaces.font, "Exit: SEARCHING", font_color);

  return surfaces;
  
}

void refresh_screen(Map map, Robot bot, Surfaces surfaces) {
	
	int i = 0, j = 0;
	
	/* Cleaning the screen */
  SDL_FillRect(surfaces.screen, NULL, SDL_MapRGB(surfaces.screen->format, 255, 255, 255));
  
  /* Showing the objects on the screen */
  for (i = 0 ; i < MAP_HEIGHT ; i++) {
    
  	for (j = 0; j < MAP_WIDTH; j++) {
        
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
	
	/* Showing the text under the sidebar */
	// TODO: SDL_FreeSurface(surfaces.moves);
	
	char movesText[20] = "";
	SDL_Color font_color = {0, 0, 0};
	
	TTF_SetFontStyle(surfaces.font, TTF_STYLE_BOLD);
	
	sprintf(movesText, "Moves: %d", bot.moves);	
	surfaces.moves = TTF_RenderText_Blended(surfaces.font, movesText, font_color);
	
	if (bot.is_random == 1) surfaces.random = TTF_RenderText_Blended(surfaces.font, "Random: YES", font_color);
	else surfaces.random = TTF_RenderText_Blended(surfaces.font, "Random: NO", font_color);
	
	if (bot.vertical == -1) surfaces.vertical = TTF_RenderText_Blended(surfaces.font, "Vertical: NONE", font_color);
	else if (bot.vertical == TOP) surfaces.vertical = TTF_RenderText_Blended(surfaces.font, "Vertical: TOP", font_color);
	else surfaces.vertical = TTF_RenderText_Blended(surfaces.font, "Vertical: BOTTOM", font_color);
	
	if (bot.horizontal == -1) surfaces.horizontal = TTF_RenderText_Blended(surfaces.font, "Horizontal: NONE", font_color);
	else if (bot.horizontal == RIGHT) surfaces.horizontal = TTF_RenderText_Blended(surfaces.font, "Horizontal: RIGHT", font_color);
	else surfaces.horizontal = TTF_RenderText_Blended(surfaces.font, "Horizontal: LEFT", font_color);
	
	if (bot.out == 1) surfaces.found = TTF_RenderText_Blended(surfaces.font, "Exit: FOUND!", font_color);
	
	surfaces.position.x = (WINDOW_WIDTH - SIDEBAR_WIDTH + SIDEBAR_PADDING);
	surfaces.position.y = SIDEBAR_PADDING;
	SDL_BlitSurface(surfaces.moves, NULL, surfaces.screen, &surfaces.position);
	
	surfaces.position.x = (WINDOW_WIDTH - SIDEBAR_WIDTH + SIDEBAR_PADDING);
	surfaces.position.y = (SIDEBAR_PADDING * 2);
	SDL_BlitSurface(surfaces.random, NULL, surfaces.screen, &surfaces.position);
	
	surfaces.position.x = (WINDOW_WIDTH - SIDEBAR_WIDTH + SIDEBAR_PADDING);
	surfaces.position.y = (SIDEBAR_PADDING * 3);
	SDL_BlitSurface(surfaces.horizontal, NULL, surfaces.screen, &surfaces.position);
	
	surfaces.position.x = (WINDOW_WIDTH - SIDEBAR_WIDTH + SIDEBAR_PADDING);
	surfaces.position.y = (SIDEBAR_PADDING * 4);
	SDL_BlitSurface(surfaces.vertical, NULL, surfaces.screen, &surfaces.position);
	
	surfaces.position.x = (WINDOW_WIDTH - SIDEBAR_WIDTH + SIDEBAR_PADDING);
	surfaces.position.y = (SIDEBAR_PADDING * 6);
	SDL_BlitSurface(surfaces.found, NULL, surfaces.screen, &surfaces.position);
  
  /* Refreshing the screen */
	SDL_Flip(surfaces.screen);
	
}

/*
 * Manage the events while the bot
 * is searching the exit
 *
 * @return 0 if the programe must top
 * or 1 otherwise
 */
int manage_events(Surfaces surfaces) {

  int must_continue = 1;

  SDL_Delay(TIME_BTW_MOVES);
  while (SDL_PollEvent(&surfaces.event)) {
  
    if (surfaces.event.type == SDL_KEYDOWN && surfaces.event.key.keysym.sym == SDLK_ESCAPE) {
      must_continue = 0;
    }
    
  }
  
  return must_continue;
  
}

int manage_controls(Surfaces surfaces) {
  
  int must_continue = 1;
  
  SDL_WaitEvent(&surfaces.event);   
  if (surfaces.event.type == SDL_QUIT) must_continue = 0;  
  else if (surfaces.event.type == SDL_KEYDOWN) {
    if (surfaces.event.key.keysym.sym == SDLK_ESCAPE) must_continue = 0;
    else if (surfaces.event.key.keysym.sym == SDLK_UP) must_continue = 0;
  }
  
  return must_continue;
  
}

void house_keeping(Surfaces surfaces) {
	
	int i = 0;
	
	TTF_CloseFont(surfaces.font);
	TTF_Quit();
	
	SDL_FreeSurface(surfaces.wall);
	SDL_FreeSurface(surfaces.exit);
	SDL_FreeSurface(surfaces.moves);
	
	for (i = 0; i < 4; i++) {
		SDL_FreeSurface(surfaces.bot[i]);
	}
	
	SDL_Quit();
	
}
