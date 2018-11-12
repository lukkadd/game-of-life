#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <panel.h>
#include <graphics.h>
#include <game.h>

char board[BOARD_WIDTH*BOARD_HEIGHT];

extern WINDOW *wboard;

void runGame(void){
    int y = 10, x = 40;
    wmove(wboard,y,x);
    int input;  
    int gameRunning = 1;
    MEVENT event;

    while(gameRunning){
        input = wgetch(wboard);
        switch(input){
            case 'a':
                board[BOARD_WIDTH*10 + 10] = 'O';
                break;
            case 'q':
                gameRunning = 0;
                break;
        }
        renderBoard(board);
        update_panels();
        doupdate();
    }

}

int initGame(void){
    
    /*building an empty board*/
    clearBoard();

    /*rendering it to the virtual screen*/
    renderBoard(board);

    /*printing it to the real screen*/
    update_panels();
    doupdate();
}

void clearBoard(void){
    for(int i = 0; i < BOARD_WIDTH*BOARD_HEIGHT;i++){
        board[i] = '.';
    }
}