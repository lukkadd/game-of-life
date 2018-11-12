#include <stdio.h>
#include <curses.h>
#include <panel.h>
#include <graphics.h>
#include <game.h>

int main (int argc, char argv[]){

	initGraphics();
	initGame();

	runGame();

	endwin();
	return 0;
}
