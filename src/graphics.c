#include <curses.h>
#include <panel.h>
#include <game.h>
#include <graphics.h>

WINDOW *wsplash, *wmenu, *wboard;
PANEL *psplash, *pmenu, *pboard;

int initGraphics(void){
    /* curses initialization */
	initscr(); /* Start curses mode */
	cbreak(); /*Disable line buffering*/
	noecho(); /* Hide user input */
	curs_set(0); /* Hide the cursor */
	keypad(stdscr,TRUE);
	nodelay(stdscr,TRUE);

	/*creating the program's visual structure*/
	box(stdscr,0,0);

	wboard = newwin(22,78,1,1);
	pboard = new_panel(wboard);
	
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
            mvwaddch(wboard,i,j,gboard[i*BOARD_WIDTH+j]);
        }
    }
}