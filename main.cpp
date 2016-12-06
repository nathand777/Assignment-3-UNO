/*
Name:				Nathan Dimla
Date:				December 7, 2016
Description:		Cpp with main to initialize game and run loop.
*/
#include <iostream>
#include <time.h>
#include "UnoGame.h"
#include "UnoPlayer.h"
using namespace std;

int main() {
	srand((unsigned int)time(NULL)); //get seed for Bag
	int numPlayers, startingHandSize;
	char yn = 'y';

	//enter number of players
	cout << "Welcome to UNO! \nPlease enter the number of players: ";
	cin >> numPlayers;

	//enter hand size to start with
	cout << "Please enter the starting hand size: ";
	cin >> startingHandSize;
	cout << endl;

	UnoGame game(numPlayers, startingHandSize); //create game

	//loop until a player wins
	while (!game.play()) {
		cout << "Continue? Y/N: "; //ask user if they wish to continue (just pauses the loop for user to read output)
		cin >> yn;
		cout << endl;

		if (yn == 'n' || yn == 'N')
			break;
	}
	cout << endl;
}