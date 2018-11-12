#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <panel.h>
#include <graphics.h>
#include <game.h>

char board[BOARD_WIDTH*BOARD_HEIGHT];
int timeScale = 0;
int gameRunning = 1;

void runGame(void){
    clock_t start = clock();
    clock_t now;
    float diff;

    while(gameRunning){
        
        handleInput(); /* check for user input */

        renderBoard(board); /* render board with user input */
        /* show updated panels */
        update_panels(); 
        doupdate();

        /* check for fixed timestep */
        if(timeScale){
            now = clock();
            diff = ((float)(now - start) / CLOCKS_PER_SEC ) * 1000;   
            if(diff > 1000/timeScale){
                nextGeneration(board);
                start = now;
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
    char nboard[BOARD_HEIGHT*BOARD_WIDTH];
    int alives;
    for(int y = 0; y < BOARD_HEIGHT; y++){
        for(int x = 0; x < BOARD_WIDTH; x++){
            alives = checkNeighbors(board,x,y);
            
            if(board[y*BOARD_WIDTH + x] == '0'){
                if(alives < 2){
                    nboard[y*BOARD_WIDTH + x] = '.';
                }else if(alives < 4){
                    nboard[y*BOARD_WIDTH + x] = '0';
                }else{
                    nboard[y*BOARD_WIDTH + x] = '.';
                }
            }else if(alives == 3){
                nboard[y*BOARD_WIDTH + x] = '0';
            }else{
                nboard[y*BOARD_WIDTH + x] = '.';
            }
        }
    }

    for(int i = 0; i < BOARD_HEIGHT*BOARD_WIDTH; i++){
        board[i] = nboard[i];
    }
}

int checkNeighbors(char *board, int x, int y){
    int alives = 0;
    int sx = x-1, sy = y-1, ex = x+1, ey = y+1;
    
    if(x-1 < 0){
        sx = x;
    }else if(x+1>BOARD_WIDTH-1){
        ex = x;
    }

    if(y-1 < 0){
        sy = y;
    }else if(y+1>BOARD_HEIGHT-1){
        ey = y;
    }

    for(int i = sy; i < ey+1; i++){
        for(int j = sx; j < ex+1; j++){
            if(!(i == y && j == x) && board[i*BOARD_WIDTH + j] == '0'){
                alives++;
            }
        }
    }
    return alives;
}

void handleInput(void){
    int input = wgetch(stdscr);
    MEVENT event;
        switch(input){
            case KEY_MOUSE:
                if(getmouse(&event) == OK){
                    if(event.bstate & BUTTON1_CLICKED){
                        board[BOARD_WIDTH*(event.y - 1) + (event.x - 1)] = '0';
                    }else if(event.bstate & BUTTON1_DOUBLE_CLICKED){
                        board[BOARD_WIDTH*(event.y - 1) + (event.x - 1)] = '.';    
                    }
                }
                break;
            case '0':
                timeScale = 0;
                break;
            case '1':
                timeScale = 1;
                break;
            case '2':
                timeScale = 2;
                break;
            case '3':
                timeScale = 3;
                break;
            case '4':
                timeScale = 4;
                break;
            case '5':
                timeScale = 5;
                break;
            case '6':
                timeScale = 6;
                break;
            case '7':
                timeScale = 7;
                break;
            case '8':
                timeScale = 8;
                break;
            case '9':
                timeScale = 9;
                break;
            case 'q':
                gameRunning = 0;
                break;
        }
}