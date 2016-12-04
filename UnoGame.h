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
	UnoPlayer *players;
	unsigned int _numPlayers;
	unsigned int _handSize;

	void createBag();
	void createFaceDownDeck();

public:

};