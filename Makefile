# rules
.PHONY: clean, mrproper

# implicit rules
.SUFFIXES:

# vars
CC = gcc

all: robot

robot: main.o robot.o map.o window.o
	$(CC) -Wall -g -lSDL -lSDL_image main.o robot.o map.o window.o -o ../robot
    
main.o: main.c headers/constants.h headers/robot.h headers/map.h
	$(CC) -Wall -g -c main.c -o main.o
	
robot.o: robot.c headers/constants.h headers/robot.h headers/map.h
	$(CC) -Wall -g -c robot.c -o robot.o
	
map.o:  map.c headers/constants.h headers/map.h
	$(CC) -Wall -g -c map.c -o map.o
	
window.o:  window.c headers/constants.h headers/window.h
	$(CC) -Wall -g -c window.c -o window.o
    
# clean
clean:
	rm -rf *.o
 
# mrproper
mrproper: clean
	rm -rf ../robot
