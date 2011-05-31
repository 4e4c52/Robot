#ifndef CONSTANTS_H
#define CONSTANTS_H

/* Program constants */
#define TIME_BTW_MOVES 150

/* Map constants */
#define MAP_WIDTH 50
#define MAP_HEIGHT 50

/* Robot constants */
#define ROBOT_DEFAULT_X 1
#define ROBOT_DEFAULT_Y 1
#define ROBOT_MAX_RANDOM 4

enum Directions { TOP, RIGHT, BOTTOM, LEFT};
typedef enum Directions Directions;

/* SDL constants */
#define SDL_ENABLED // Comment this line to use the console
#define BLOCK_SIZE 20 // 20px OR 34px
#define SIDEBAR_WIDTH 250
#define SIDEBAR_PADDING 20
#define WINDOW_WIDTH (BLOCK_SIZE * MAP_WIDTH) + SIDEBAR_WIDTH
#define WINDOW_HEIGHT BLOCK_SIZE * MAP_HEIGHT

enum Objects { EMPTY, FOOTPRINT, WALL, BOT, EXIT };
typedef enum Objects Objects;

#endif
