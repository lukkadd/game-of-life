#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <panel.h>
#include <graphics.h>
#include <game.h>

char board[BOARD_WIDTH*BOARD_HEIGHT];

void runGame(void){
    int input;  
    int gameRunning = 1;
    int timeScale = 0;
    MEVENT event;
    time_t start = time(0);

    while(gameRunning){
        input = wgetch(stdscr);
        switch(input){
            case KEY_MOUSE:
                if(getmouse(&event) == OK){
                    board[BOARD_WIDTH*(event.y - 1) + (event.x - 1)] = '0';
                }
                break;
            case '1':
                timeScale = 1;
                break;
            case '9':
                timeScale = 9;
                break;
            case 'q':
                gameRunning = 0;
                break;
        }
        renderBoard(board);
        update_panels();
        doupdate();

        if(timeScale){
            if(difftime(time(0),start) > 10 - timeScale){
                board[810] = 'B';
                start = time(0);
            }
        }
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

void nextGeneration(char *board){
    
}