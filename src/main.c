#include <stdio.h>
#include <curses.h>
#include <panel.h>

WINDOW *wsplash, *wmenu, *wboard;
PANEL *psplash, *pmenu, *pboard;

int main (int argc, char argv[]){

	char a;
	/* curses initialization */
	initscr(); /* Start curses mode */
	raw(); /* Disable line buffering */
	noecho(); /* Hide user input */
	curs_set(0); /* Hide the cursor */

	/*creating the program's visual structure*/
	box(stdscr,0,0);

	wboard = newwin(22,78,1,1);
	pboard = new_panel(wboard);
	
	wmenu = newwin(6,20,17,59);
	box(wmenu,0,0);
	mvwaddstr(wmenu,1,1,"Click to add cells");

	mvwaddstr(wmenu,2,1,"0: 0xSpeed");
	mvwaddstr(wmenu,3,1,"|");
	mvwaddstr(wmenu,4,1,"9: 9xSpeed");
	pmenu = new_panel(wmenu);

	wsplash = newwin(5,25,0,28);
	wborder(wsplash,'|','|','-','-','+','+','+','+');
	mvwaddstr(wsplash,2,2,"Conway's Game of Life");
	psplash = new_panel(wsplash);

	update_panels();
	doupdate();
	
	getch();
	endwin();
	return 0;
}
