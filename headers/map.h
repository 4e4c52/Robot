#ifndef MAP_H
#define MAP_H

/* Struct containing the map */

struct Map {

  int width;
  int height;
  char map[MAP_HEIGHT][MAP_WIDTH];
  
};

typedef struct Map Map;
struct Robot;

/* Struct containing the exit */

struct Exit {
  int x;
  int y;
};
typedef struct Exit Exit;

/* Prototypes */

Map read_map();
void show_map(Map map, struct Robot bot);
Exit find_map_exit(Map map);

#endif
