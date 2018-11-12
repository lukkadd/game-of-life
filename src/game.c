#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>
#include <panel.h>
#include <graphics.h>
#include <game.h>

char board[BOARD_WIDTH*BOARD_HEIGHT];
extern WINDOW *wmenu;
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
            case 'a':
                board[10*BOARD_WIDTH+10] = 'B';
                break;
            case 'c':
                mvwprintw(wmenu,6,1,"%d alives",checkNeighbors(board,1,1));
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
            if(difftime(time(0),start) > 1 - 0.1*timeScale){
                nextGeneration(board);
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