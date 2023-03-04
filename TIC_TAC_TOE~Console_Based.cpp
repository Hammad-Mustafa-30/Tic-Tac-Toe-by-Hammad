#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string>
#include <unistd.h>

using namespace std;

void display(char Board[]){
	cout<<"Welcome to \n\t\tTic Tac Toe\n";
	cout<<"\n\n\t     |     |     "<<endl;
	cout<<"\t  "<<Board[7]<<"  |  "<<Board[8]<<"  |  "<<Board[9]<<"  "<<endl;
	cout<<"\t_____|_____|_____"<<endl;
	cout<<"\t     |     |     "<<endl;
	cout<<"\t  "<<Board[4]<<"  |  "<<Board[5]<<"  |  "<<Board[6]<<"  "<<endl;
	cout<<"\t_____|_____|_____"<<endl;
	cout<<"\t     |     |     "<<endl;
	cout<<"\t  "<<Board[1]<<"  |  "<<Board[2]<<"  |  "<<Board[3]<<"  "<<endl;
	cout<<"\t     |     |     \n\n\n";
}

char playerLetter(){
	cout<<"Welcome to \n\t\tTic Tac Toe\n\n";
	cout<<"What do you want to play as?(X/ O)\n";
	char ai;
	ai = getch();
	while (ai != 'x' && ai != 'X' && ai != 'o' && ai != 'O'){
		cout<<"Please enter either X or O\n";
		ai = getch();
	}
	if (ai == 'x'){
		ai = 'X';
	}
	if (ai == 'o'){
		ai = 'O';
	}
	return ai;
}

int playerMove(char Board[]){
	char m;
	cout<<"\nEnter your move. (1 - 9)\n";
	m = getch();
	string amv = "0123456789";
	while (true){
		bool ai = true;
		for (int i = 1; i < 10; i++){
			if (m == amv[i]){
				ai = false;
				if (Board[i] == ' '){
					return i;
				}
				else{
					cout<<"Move not available.\nEnter again:\n";
					m = getch();
					break;
				}
			} 
		}
		if (ai){
			cout<<"Invalid move. Enter again:\n";
			m = getch();
		}
	}	
}

bool Winner(char b[], char l){
	if (b[7] == l && b[8] == l && b[9] == l){
		return true;
	}
	else if (b[4] == l && b[5] == l && b[6] == l){
		return true;
	}
	else if (b[1] == l && b[2] == l && b[3] == l){
		return true;
	}
	else if (b[7] == l && b[4] == l && b[1] == l){
		return true;
	}
	else if (b[2] == l && b[8] == l && b[5] == l){
		return true;
	}
	else if (b[3] == l && b[6] == l && b[9] == l){
		return true;
	}
	else if (b[1] == l && b[5] == l && b[9] == l){
		return true;
	}
	else if (b[7] == l && b[5] == l && b[3] == l){
		return true;
	}
	return false;
}

bool playAgain(){
	cout<<"\nDo yo want to play again?(Y/ N)\n";
	char ai;
	ai = getch();
	if (ai == 'Y' || ai == 'y'){
		return true;
	}
	return false;
}

bool emptyB(char board[]){
	for (int i = 1; i < 10; i++){
		if (board[i] == ' '){
			return false;
		}
	}
	return true;
}

int randAImove(char board[], int amv[]){
	srand(time(0));
	int ai[4];
	int AI = 0;
	for (int i = 1; i < 10; i++){
		for (int j = 0; j < 4; j++){
			if (amv[j] == i){
				if (board[i] == ' '){
					ai[AI] = i;
					AI++;
				}
			}
		}
	}
	
	if (AI == 0){
		return AI;
	}
	
	int k = rand() % AI;
	return ai[k];
}

int AI(char board[], char cl, char pl){
	
	char duplex[10];
	
	for (int i = 1; i < 10; i++){
		if (board[i] == ' '){
			for (int j = 0; j < 10; j++){
				duplex[j] = board[j];
			}
			duplex[i] = cl;
			if (Winner(duplex, cl)){
				return i;
			}
		}
	}
	
	for (int i = 1; i < 10; i++){
		if (board[i] == ' '){
			for (int j = 0; j < 10; j++){
				duplex[j] = board[j];
			}
			duplex[i] = pl;
			if (Winner(duplex, pl)){
				return i;
			}
		}
	}
	
	int ai[4] = {1, 3, 7, 9};
	int move = randAImove(board, ai);
	if (move != 0){
		return move;
	}
	
	if (board[5] == ' '){
		return 5;
	}
	
	int AI[4] = {1, 4, 6, 8};
	move = randAImove(board, AI);
	return move;
}

char First(){
	srand(time(0));
	int ai = rand() % 2;
	if (ai == 0){
		cout<<"Computer will go first. Press any key to continue\n";
		getch();
		return 'C';
	}
	else {
		cout<<"Player will go first. Press any key to continue\n";
		getch();
		return 'P';
	}
}

int main(){
	srand(time(0));
	char board[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	char pl;
	pl = playerLetter();
	char cl;
	if (pl == 'X'){
		cl = 'O';
	}
	else {
		cl = 'X';
	}
	char turn = First();
	int move = 0;
	bool OPGamePlay = true;
	while (true){
		srand(time(0));
		system("cls");
		if (turn == 'P'){
			display(board);
			if (move != 0){
				cout<<"Computer chose "<<move<<".\n";
			}
			move = playerMove(board);
			board[move] = pl;
			if (Winner(board, pl)){
				system("cls");
				display(board);
				cout<<"Hooray! You have won the game!\n";
				OPGamePlay = false;
			}
			else if(emptyB(board)){
				system("cls");
				display(board);
				cout<<"The game is a tie!\n";
				OPGamePlay = false;
			}
			else{
				turn = 'C';
			}
		}
		else{
			display(board);
			move = AI(board, cl, pl);
			sleep(1);
			cout<<"Computer chose "<<move<<".\n";
			sleep(1);
			
			board[move] = cl;
			if (Winner(board, cl)){
				system("cls");
				display(board);
				cout<<"The computer has beaten you. You loose\n";
				OPGamePlay = false;
			}
			else if(emptyB(board)){
				system("cls");
				display(board);
				cout<<"The game is a tie!\n";
				OPGamePlay = false;
			}
			else{
				turn = 'P';
			}
		}
		if (!OPGamePlay){
			if (playAgain()){
				system("cls");
				for (int i = 0; i < 10; i++){
					board[i] = ' ';
				}
				
				pl = playerLetter();
				if (pl == 'X'){
					cl = 'O';
				}
				else {
					cl = 'X';
				}
				turn = First();
				move = 0;
				OPGamePlay = true;
			}
			else{
				cout<<"\nThanks for playing.\n\n\n\tGame by ~Hammad\n\n\n";
				break;
			}
		}
	}
}
