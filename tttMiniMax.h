#ifndef BOARD_H
#define BOARD_H

#define Player1 'x'
#define Player2 'o'

typedef struct {
    char boardPositions[10];
    int emptySpace;
} board;

int checkWin(board* gameBoard);
int findNextMove(board* gameBoard);
void printIntArray(int* array, int size);
int miniMax(board* gameBoard, int initial);
void deepCopyBoard(board* copy, const board* original);
int* findArrayOfEmpties(board* gameBoard);
board** findChildren(board* gameBoard);
board* initBoard();
void printBoard(board* gameBoard);
void move(board* gameBoard, int position);
void freeBoardMem(board* gameBoard);
void printBoardList(board** list, int num);

#endif
