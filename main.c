#include "main.h"

int main() {
    Boards Boards;
    Cursor cursor;
    cursor.x = 0;
    cursor.y = 0;
    initGame(&Boards);
    printResult(&Boards, &cursor, play(&Boards, &cursor)); //0 = progress, -1 = loose, 1 = win, 2 = quit
    system("pause");
    return 0;
}

void initGame(Boards *boards) {
    // Init boards
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            boards->board[i][j] = EMPTY;
            boards->userBoard[i][j] = EMPTY;
        }
    }
    // Place bombs
    for (int i = 0; i < BOMB_COUNT; i++) {
        int x = rand() % BOARD_SIZE;
        int y = rand() % BOARD_SIZE;
        if (boards->board[x][y] == BOMB) {
            i--;
        } else {
            boards->board[x][y] = BOMB;
        }
    }

    // Place numbers
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (boards->board[i][j] != BOMB) {
                int count = 0;
                for (int k = -1; k <= 1; k++) {
                    for (int l = -1; l <= 1; l++) {
                        if (i + k >= 0 && i + k < BOARD_SIZE && j + l >= 0 && j + l < BOARD_SIZE) {
                            if (boards->board[i + k][j + l] == BOMB) {
                                count++;
                            }
                        }
                    }
                }
                if (count == 0) {
                    boards->board[i][j] = EMPTY;
                } else {
                    boards->board[i][j] = count + '0';
                }
            }
        }
    }
}

void printBoard(Boards *boards, Cursor *cursor, int resultBoard) {
    system("cls");
    printf("Utilisez les fleches pour vous deplacer, espace pour decouvrir une case et entrer pour poser un drapeau.\n");
    printf("Vous avez %d bombes a trouver.\n", BOMB_COUNT);
    printf("\n");

    //if resultBoard == 0 -> print userBoard and cursor else print board and no cursor
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (resultBoard == 0) {
                if (cursor->x == i && cursor->y == j) {
                    printf("%c ", CURSOR);
                } else {
                    printf("%c ", boards->userBoard[i][j]);
                }
            } else {
                if (resultBoard == 1 && boards->board[i][j] == EMPTY) {
                    printf("%c ", DISCOVERED);
                } else {
                    printf("%c ", boards->board[i][j]);
                }
            }
        }
        printf("\n");
    }
}

int play(Boards *boards, Cursor *cursor) {
    int result = 0; //0 = progress, -1 = loose, 1 = win, 2 = quit
    while (result == 0) {
        printBoard(boards, cursor, 0);
        int key = getch();
        switch (key) {
            case KEY_UP:
                if (cursor->x > 0) {
                    cursor->x--;
                }
                break;
            case KEY_DOWN:
                if (cursor->x < BOARD_SIZE - 1) {
                    cursor->x++;
                }
                break;
            case KEY_LEFT:
                if (cursor->y > 0) {
                    cursor->y--;
                }
                break;
            case KEY_RIGHT:
                if (cursor->y < BOARD_SIZE - 1) {
                    cursor->y++;
                }
                break;
            case KEY_SPACE:
                if (boards->board[cursor->x][cursor->y] == BOMB) {
                    boards->userBoard[cursor->x][cursor->y] = BOMB;
                    result = -1;
                } else {
                    boards->userBoard[cursor->x][cursor->y] = boards->board[cursor->x][cursor->y];
                    if (boards->userBoard[cursor->x][cursor->y] == EMPTY) {
                        //Discover all empty cases around
                        for (int i = -1; i <= 1; i++) {
                            for (int j = -1; j <= 1; j++) {
                                if (cursor->x + i >= 0 && cursor->x + i < BOARD_SIZE && cursor->y + j >= 0 &&
                                    cursor->y + j < BOARD_SIZE) {
                                    if (boards->userBoard[cursor->x + i][cursor->y + j] == EMPTY) {
                                        boards->userBoard[cursor->x + i][cursor->y + j] = DISCOVERED;
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            case KEY_ENTER:
                if (boards->userBoard[cursor->x][cursor->y] == EMPTY) {
                    boards->userBoard[cursor->x][cursor->y] = FLAG;
                } else if (boards->userBoard[cursor->x][cursor->y] == FLAG) {
                    boards->userBoard[cursor->x][cursor->y] = EMPTY;
                }
                break;
            default:
                break;
        }
    }
    return result;
}

void printResult(Boards *boards, Cursor *cursor, int result) {
    system("cls");
    switch (result) {
        case -1:
            printf("Vous avez perdu !\n");
            printf("Voici la solution :\n");
            printBoard(boards, cursor, 1);
            break;
        case 1:
            printf("Bravo, vous avez gagne !\n");
            break;
        case 2:
            printf("Vous avez quitte la partie !\n");
            break;
        default:
            printf("Erreur !\n");
            break;
    }
}