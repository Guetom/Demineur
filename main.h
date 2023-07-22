#ifndef DEMINEUR_MAIN_H
#define DEMINEUR_MAIN_H

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_SPACE 32
#define KEY_ENTER 13

#define BOARD_SIZE 10
#define BOMB_COUNT 10

#define BOMB 'X'
#define FLAG '#'
#define EMPTY '.'
#define DISCOVERED ' '
#define CURSOR '~'

typedef struct {
    int x;
    int y;
} Cursor;

typedef struct{
    char board[BOARD_SIZE][BOARD_SIZE];
    char userBoard[BOARD_SIZE][BOARD_SIZE];
} Boards;

void initGame(Boards *game);
void printBoard(Boards *game, Cursor *cursor, int resultBoard); //0 = userBoard, 1 = resultBoard
int play(Boards *game, Cursor *cursor);
void printResult(Boards *game, Cursor *cursor, int result);

#endif //DEMINEUR_MAIN_H
