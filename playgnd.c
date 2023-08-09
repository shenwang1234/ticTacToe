#include <stdio.h>
#include <windows.h>
#include <ctype.h>
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

Try to break the game
- crash
- break rules

 
*/
#define Player1 'x'
#define Player2 'o'


int checkWin();
int isValid(int positionNum);//check if posotion entered is available 
int getInput();//has to be integer
void printBoard();
int allFilled();
int compareLine(int a, int b, int c);
void pvpStartGame();

char board[10] = {'0','1','2','3','4','5','6','7','8','9'};

int main(){

	//pvpStartGame();

}

int allFilled(){
	for (int i = 1; i<10;i++){
		if(isdigit(board[i])){
			printf("digit\n");
			return 0;

		} 
	}
	return 1;
}
int isValid(int positionNum){
	if (positionNum>0 && positionNum<10){
		if(board[positionNum]!=Player1 &&board[positionNum]!=Player2) return 1;
		else return -1;
	}else return -1;
}
int getInput(){
	int position = 0;
	int statusOfScan = 0;
	while(1){
		do{
			printf("\t");
			statusOfScan = scanf("%d",&position); //try getInput(), scanf ignores leading white space
			if(statusOfScan!=1){
				int c;
				while ((c = getchar()) != '\n' && c != EOF){} //clear buffer for scanf
	            printf("Invalid input. Please enter a number: ");
		}
		}while(statusOfScan!=1);
			if(isValid(position)!=1) {
				printf("position unable. Please enter a number: ");
				continue;
			}else return position;
	}
	

}

//return 2 if player 2 won, 1 if player 1 won, -1 if not the same
int compareLine(int a, int b, int c){
	if(board[a]==board[b] &&board[c]==board[b]){
		return 1;
	}
	else return 0;
}


void pvpStartGame(){
	int position = 0;
	int gameOnGoing = 1;
	int isTie = 0;
	printf("\n\n\n\tGame Start!\n\n\n");
	printf("\tenter the position number of your choice\n");
	printBoard();
	while(gameOnGoing && !isTie){
		printf("\tplayer 1 go\n");
		position = getInput();
		board[position]=Player1;
		printBoard();
		if(checkWin()==1){
			printf("\n\n\tplayer 1 won!\n\n\n");
			gameOnGoing = 0;
			break;
		}
		if ((isTie = allFilled())){
			printf("\tTie!!\n");
			break;
		} 
		printf("\tplayer 2 go\n");
		position = getInput();
		board[position]=Player2;
		printBoard();
		if(checkWin()==1) {
			printf("\n\n\tplayer 2 won!\n\n\n");
			gameOnGoing = 0;
			break;
		}
	}
}

int checkWin(){
	if(compareLine(1,2,3)>0) return 1;
	else if (compareLine(4,5,6)>0) return 1;
	else if (compareLine(7,8,9)>0) return 1;
	else if (compareLine(1,4,7)>0) return 1;
	else if (compareLine(2,5,8)>0) return 1;
	else if (compareLine(3,6,9)>0) return 1;
	else if (compareLine(1,5,9)>0) return 1;
	else if (compareLine(3,5,7)>0) return 1;
	else return -1;
}


void printBoard(){
	printf("\n\n\tTic Tac Toe\n\n");

    printf("\tPlayer 1 (X)  -  Player 2 (O)\n\n\n");


    printf("\t     |     |     \n");
    printf("\t  %c  |  %c  |  %c \n", board[1], board[2], board[3]);

    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");

    printf("\t  %c  |  %c  |  %c \n", board[4], board[5], board[6]);

    printf("\t_____|_____|_____\n");
    printf("\t     |     |     \n");

    printf("\t  %c  |  %c  |  %c \n", board[7], board[8], board[9]);

    printf("\t     |     |     \n\n");
}
	