#ifndef WINDOW_H
#define WINDOW_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "map.h"
#include "robot.h"

/* Struct containing the surfaces */

struct Surfaces {

  SDL_Surface *screen;
  SDL_Surface *bot[4];
  SDL_Surface *wall;
  SDL_Surface *exit;
  SDL_Surface *footprint[4];
  SDL_Rect position;
  SDL_Event event;  
  
};

typedef struct Surfaces Surfaces;

/* Prototypes */

Surfaces load_surfaces(void);
void refresh_screen(Map map, Robot bot, Surfaces surfaces);
void house_keeping(Surfaces surfaces);

#endif
