#pragma once
#include <iostream>
#include <string>
#include "Card.h"
#include "OrderedList.h"
#include "Bag.h"
#include "Queue.h"
#include "Stack.h"
#include "UnoPlayer.h"
#include <memory>

//default values
#define NUM_OF_PLAYERS 3
#define NUM_OF_CARDS 7

class UnoGame {

	Queue<std::shared_ptr<Card>> faceDownDeck;
	Stack<std::shared_ptr<Card>> faceUpDeck;
	UnoPlayer *playersInGame;
	unsigned int _numPlayers;//number of players in game
	unsigned int _handSize;//starting handsize for players


	void createFaceDownDeck(Bag<std::shared_ptr<Card>> &cardBag);

public:
	UnoGame(unsigned int players, unsigned int numCards);
	~UnoGame();

	bool play(); //turn function that will return true once someone wins
};

UnoGame::UnoGame(unsigned int players = NUM_OF_PLAYERS, unsigned int handSize = NUM_OF_CARDS) {
	_numPlayers = players;
	_handSize = handSize;
	playersInGame = new UnoPlayer[_numPlayers]; //container to hold players
	
	for (int i = 0; i < _numPlayers; i++)
		std::cout << "Player " << playersInGame[i].getName() << " has entered the game!\n";

	//create bag
	Bag<std::shared_ptr<Card>> cards(40);
	Suit s[] = { RED, YELLOW, BLUE, GREEN };
	Denomination d[] = { N1, N2, N3, N4, N5 };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 5; j++) {
			cards.add(std::make_shared<Card>(s[i], d[j]));
			cards.add(std::make_shared<Card>(s[i], d[j]));
		}
	}

	//create face down deck
	createFaceDownDeck(cards);

	//deal cards to players
	for (unsigned int i = 0; i < _numPlayers; i++) {
		for (unsigned int j = 0; j < 7; j++)
			playersInGame[i].getACard(faceDownDeck.dequeue());
	}

	faceUpDeck.push(faceDownDeck.dequeue()); //place first card on deck
	std::cout << "Start \n";

}

UnoGame::~UnoGame() {
	delete[] playersInGame;
	playersInGame = NULL;
}

void UnoGame::createFaceDownDeck(Bag<std::shared_ptr<Card>> &cardBag) {
	int size = cardBag.currentSize();
	for (int i = 0; i < size; i++) {
		faceDownDeck.enqueue(cardBag.getOne());
	}
}

bool UnoGame::play() {
	std::cout << "Top card: " << *(faceUpDeck.peek()) << std::endl;
	bool win = false;
	unsigned int check;

	for (int i = 0; i < _numPlayers && !win; i++) {
		check = playersInGame[i].checkCard(faceUpDeck.peek());
		if (check > 0) {
			std::cout << "Player " << playersInGame[i].getName() << "has found a match and  placed down " << *(playersInGame[i].getCardAt(check)) << std::endl;
			faceUpDeck.push(playersInGame[i].playCard(check));
		}

		else {//take card from pile
			playersInGame[i].getACard(faceDownDeck.dequeue());
			std::cout << "Player " << playersInGame[i].getName() << " could not find a match and pulled a card from the deck" << std::endl;
		}

		if (faceDownDeck.isEmpty()) { //if pile is empty
			i--; //decrement count so loop begins at same player
			std::shared_ptr<Card> temp = faceUpDeck.pop(); //hold top card
			while (!faceUpDeck.isEmpty())
				faceDownDeck.enqueue(faceUpDeck.pop()); //transfer cards from faceup pile to facedown
			faceUpDeck.push(temp); //place top card back
			std::cout << "Deck has been repopulated" << std::endl;
			}

		//check if player has won
		if (playersInGame[i].getNumCards() == 1)
			std::cout << "Player " << playersInGame[i].getName() << " has 1 card left!\n";

		if (playersInGame[i].getNumCards() == 0) {
			std::cout << "Player " << playersInGame[i].getName() << " has placed their last card and won!\n";
			win = true;
		}
	}

	if (!win) {
		for (int i = 0; i < _numPlayers; i++)
			playersInGame[i].printCardsInHand();
	}

	return win;
}
