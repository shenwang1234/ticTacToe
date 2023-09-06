#include <stdio.h>
#include <ctype.h>
#include "tttMiniMax.h"
/*
To-DO
minor
1. handle space
2. Format print .clear screen, and center printf


major
1.ai
 1. minimax
 2. pruning
2.ui
3.algorithm. it doesnt take immediate win cuz score system

Try to break the game
- crash
- break rules

 
*/
int isValid(int positionNum, board* gameBoard);//check if posotion entered is available 
int getInput(board* gameBoard);//has to be integer
void pveStartGame();

int main(){
	pveStartGame();
}

//take a board and position as input. 
// return 1 if valid 
int isValid(int positionNum, board* gameBoard){
	if (positionNum>0 && positionNum<10){ //check if position is within boundaries
		if(gameBoard->boardPositions[positionNum]!=Player1 &&gameBoard->boardPositions[positionNum]!=Player2) return 1;//check if position is occupied
		else return -1;
	}else return -1;
}

//get input from cmd. check if input is valid.
//if it is return
//else ask user to input again 
int getInput(board* gameBoard){
	int position = 0;
	int statusOfScan = 0;
	printf("\n\tenter the position number of your choice: ");
	while(1){
		do{
			statusOfScan = scanf("%d",&position); //try getInput(), scanf ignores leading white space
			if(statusOfScan!=1){
				int c;
				while ((c = getchar()) != '\n' && c != EOF){} //clear buffer for scanf
	            printf("\n\tInvalid input. Please enter a number: ");
			}
		}while(statusOfScan!=1);
		if(isValid(position, gameBoard)!=1) {
			printf("\n\tposition unable. Please enter a number: ");
			continue;
		}else return position;
	}
}

//return 2 if player 2 won, 1 if player 1 won, -1 if n
void pveStartGame(){
	board* gameboard = initBoard();
	int position = 0;
	int gameOnGoing = 1;
	int isTie = 0;
	printf("\n\n\n\tGame Start!\n\n\n");
	printBoard(gameboard);
	while(gameOnGoing && !isTie){
		printf("\tplayer 1 go\n");
		int aiChoice = findNextMove(gameboard);
		move(gameboard, aiChoice);
		printBoard(gameboard);
		if(checkWin(gameboard)==10){
			printf("\n\n\tplayer 1 won!\n\n\n");
			gameOnGoing = 0;
			break;
		}
		if (gameboard->emptySpace==0){
			printf("\tTie!!\n");
			isTie=1;
			break;
		} 
		printf("\tplayer 2 go\n");
		position = getInput(gameboard);
		move(gameboard, position);
		printBoard(gameboard);
		if(checkWin(gameboard)==-10) {
			printf("\n\n\tplayer 2 won!\n\n\n");
			gameOnGoing = 0;
			break;
		}
	}
}