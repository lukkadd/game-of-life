#include <curses.h>
#include <panel.h>
#include <game.h>
#include <graphics.h>

WINDOW *wsplash, *wmenu;
PANEL *psplash, *pmenu;

int initGraphics(void){
    /* curses initialization */
	initscr(); /* Start curses mode */
	cbreak(); /*Disable line buffering*/
	noecho(); /* Hide user input */
	curs_set(0); /* Hide the cursor */
	nodelay(stdscr,TRUE); /* return ERR if input is not given */
	keypad(stdscr,TRUE); /* allows for F* keys and mouse input */
	mousemask(ALL_MOUSE_EVENTS,NULL); /* enables mouse events */

	/*creating the program's visual structure*/
	box(stdscr,0,0);
	
	wmenu = newwin(8,20,15,59);
	box(wmenu,0,0);

	mvwaddstr(wmenu,1,5,"Commands");
	mvwaddstr(wmenu,3,2,"a: add cells");
	mvwaddstr(wmenu,4,2,"0..9: xSpeed");
	mvwaddstr(wmenu,5,2,"q: quit");
	pmenu = new_panel(wmenu);

	wsplash = newwin(5,25,0,28);
	wborder(wsplash,'|','|','-','-','+','+','+','+');
	mvwaddstr(wsplash,2,2,"Conway's Game of Life");
	psplash = new_panel(wsplash);

	update_panels();
	doupdate();
	
}

void renderBoard(char *gboard){
    for (int i = 0; i < BOARD_HEIGHT; i++){
        for(int j = 0; j < BOARD_WIDTH;j++){
            mvwaddch(stdscr,i+1,j+1,gboard[i*BOARD_WIDTH+j]);
        }
    }
}