# rules
.PHONY: clean, mrproper

# implicit rules
.SUFFIXES:

# vars
CC = gcc `sdl-config --cflags --libs`
CFLAGS = -Wall -g -c
SDL = -lSDL -lSDL_image -lSDL_ttf

all: robot

robot: main.o robot.o map.o window.o
	$(CC)  -Wall -g $(SDL) main.o robot.o map.o window.o -o ../robot
    
main.o: main.c headers/constants.h headers/robot.h headers/map.h
	$(CC) $(CFLAGS) main.c -o main.o
	
robot.o: robot.c headers/constants.h headers/robot.h headers/map.h
	$(CC) $(CFLAGS) robot.c -o robot.o
	
map.o:  map.c headers/constants.h headers/map.h
	$(CC) $(CFLAGS) map.c -o map.o
	
window.o:  window.c headers/constants.h headers/window.h
	$(CC) $(CFLAGS) window.c -o window.o
    
# clean
clean:
	rm -rf *.o
 
# mrproper
mrproper: clean
	rm -rf ../robot
