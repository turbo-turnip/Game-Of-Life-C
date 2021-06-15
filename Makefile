# makefile for implementation of conway's game of life in C/SDL2

CC=gcc
FLAGS=-Wall -g
OUT=main
IN=main.c
PERMS=a+x
GRAPHICS_FRAMEWORK=SDL2
FONT_RENDERING=SDL2_ttf

all: compile build
compile: clean
	$(CC) $(FLAGS) -o $(OUT) $(IN) -framework $(GRAPHICS_FRAMEWORK) -framework $(FONT_RENDERING)
clean:
	rm -rf *.exe *.o Icon
	rm -rf $(OUT) $(OUT).dSYM
build:
	chmod $(PERMS) $(OUT)
exec:
	./$(OUT)
