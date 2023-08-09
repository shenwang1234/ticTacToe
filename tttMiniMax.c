/*
1. private access modifer to prevent elements of board being accessed without a function


*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Player1 'x'
#define Player2 'o'

//coupled arrays. First array is current board positions, second is minimax backtracking scores.
typedef struct{
	//overhead of 1 per array since only 9 indexes are used 
	char boardPositions[10];
	int positionScore[10];
	int emptySpace;
}board; //if typedef not used then struct keyword has to be used when declaring board, since it is
//type struct, but using typedef, we define a type called board, instead of a struct type called 
//board

void printIntArray(int* array, int size);
int firstEmptySpot(board* gameBoard);
int miniMax(board* gameBoard);
void deepCopyBoard(board* copy, const board* original);
int* findArrayOfempties(board* gameBoard);
board** findChildren(board* gameBoard);
board* initBoard();
void printBoard(board* gameBoard);
void move(board* gameBoard, int position);
void freeBoardMem(board* gameBoard);
void printBoardList(board** list, int num);

board* initBoard() {
	board* gameBoard = (board*) malloc(sizeof(board)); //the (board*) before malloc is used to cast the appropriate 
													   //pointer type. Since malloc normally return void*
													   // we need to indicate it is board*, to avoid errors
	if(gameBoard == NULL){
		printf("memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	for( int i = 0; i<10; i++){
		gameBoard->boardPositions[i] = '0'+ i;
		gameBoard->positionScore[i] = 0;
	}
	gameBoard->emptySpace=9;
	return gameBoard;

}


void deepCopyBoard(board* copy, const board* original) {
    if (copy == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    memcpy(copy, original, sizeof(board));
}


void freeBoardMem(board* gameBoard) {
    free(gameBoard);
}


void move(board* gameBoard,int position){//i indicate player num 
	gameBoard->boardPositions[position] = (gameBoard->emptySpace % 2 == 0) ? Player2: Player1; 
	gameBoard->emptySpace--;
}

int* findArrayOfempties(board* gameBoard){
	int numOfempties = gameBoard->emptySpace;
	int* array = (int*) malloc(numOfempties*sizeof(int));
	int index = 0;
	for(int i= 1; i<10; i++){
		if (gameBoard->boardPositions[i]!=Player1 &&gameBoard->boardPositions[i]!=Player2){
			array[index++]=i;
		}
	}
	return array;
}

board** findChildren(board* parent){
	int* availablePoisition = findArrayOfempties(parent);
	int numOfChildren = parent->emptySpace;
	board** listOfChildren = (board**) malloc(numOfChildren*sizeof(board));
	for (int i = 0; i<numOfChildren;i++){
		board* child = initBoard();
		deepCopyBoard(child, parent);
		move(child, availablePoisition[i]);
		listOfChildren[i]=child;
	}
	return listOfChildren;
 
}


int compareLine(board* gameBoard, int a, int b, int c){
	if(gameBoard->boardPositions[a]==gameBoard->boardPositions[b] &&gameBoard->boardPositions[c]==gameBoard->boardPositions[b]){
		if(gameBoard->boardPositions[a]==Player1) return 10;
		else return -10;
	}
	else return 0;//no winner
}

int checkWin(board* gameBoard) {
    int score = 0;
    //check 8 straight lines
    if ((score = compareLine(gameBoard, 1, 2, 3)) != 0) return score;
    else if ((score = compareLine(gameBoard, 4, 5, 6)) != 0) return score;
    else if ((score = compareLine(gameBoard, 7, 8, 9)) != 0) return score;
    else if ((score = compareLine(gameBoard, 1, 4, 7)) != 0) return score;
    else if ((score = compareLine(gameBoard, 2, 5, 8)) != 0) return score;
    else if ((score = compareLine(gameBoard, 3, 6, 9)) != 0) return score;
    else if ((score = compareLine(gameBoard, 1, 5, 9)) != 0) return score;
    else if ((score = compareLine(gameBoard, 3, 5, 7)) != 0) return score;
    
    return 0;
}




int miniMax(board* gameBoard){ //depth is measured by empty spaces
	int score = 0;
	if (gameBoard->emptySpace == 0 || checkWin(gameBoard)!=0) {
		return checkWin(gameBoard);
		freeBoardMem(gameBoard);
	}
	if (gameBoard->emptySpace % 2 != 0){ // maximizing player, player 1, if odd
		int eval = 0;
		board** children = findChildren(gameBoard);
		for(int i = 0;i<gameBoard->emptySpace;i++){
			eval = miniMax(children[i]); //false since next move will be opponent
			score += eval;
		}
		return score;
	}

	else{				  // minimizing player player 2 
		int eval = 0;
		board** children = findChildren(gameBoard);
		for(int i = 0;i<gameBoard->emptySpace;i++){
			eval = miniMax(children[i]); //false since next move will be opponent
			score += eval;
		}
		return score;
	}
}

/*
problem
1. how is position passed? A: pass by pointer
2. how to find child A: find lowest index to choose +
3. scoring system, show to translate a score to an actual position 
4. how to translate a score to an actual step
*/
void printIntArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void printBoard(board* gameBoard){
	printf("\n\n\tTic Tac Toe\n\n");

    printf("\tPlayer 1 (X)  -  Player 2 (O)\n\n\n");


    printf("\t     |     |     \n");
    printf("\t  %c  |  %c  |  %c \n", gameBoard->boardPositions[1], gameBoard->boardPositions[2], gameBoard->boardPositions[3]);

    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");

    printf("\t  %c  |  %c  |  %c \n", gameBoard->boardPositions[4], gameBoard->boardPositions[5], gameBoard->boardPositions[6]);

    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");

    printf("\t  %c  |  %c  |  %c \n", gameBoard->boardPositions[7], gameBoard->boardPositions[8], gameBoard->boardPositions[9]);

    printf("\t     |     |     \n\n");
}

void printBoardList(board** list, int num){
	for(int i =0; i<num ;i++){
		printf("child %d",i);
		printBoard(list[i]);
	}
}

void main(){
	board* board1 = initBoard();
	move(board1, 2); //p1 need at least 5 round to win the game
	move(board1, 1);
	move(board1, 4);
	move(board1, 3);
	move(board1, 6);
	move(board1, 5);
	miniMax(board1);

}