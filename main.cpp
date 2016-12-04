#include <iostream>
#include <time.h>
#include "UnoGame.h"
#include "UnoPlayer.h"
using namespace std;

int main() {
	srand((unsigned int)time(NULL));
	int numPlayers, startingHandSize;
	char yn = 'y';
	cout << "Welcome to UNO! \nPlease enter the number of players: ";
	cin >> numPlayers;

	cout << "Please enter the starting hand size: ";
	cin >> startingHandSize;
	cout << endl;

	UnoGame game(numPlayers, startingHandSize);


	while (!game.play()) {
		cout << "Continue? Y/N: ";
		cin >> yn;
		cout << endl;

		if (yn == 'n' || yn == 'N')
			break;
	}


}