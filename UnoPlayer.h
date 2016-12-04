#pragma once
#include <iostream>
#include <time.h>
#include <memory>
#include "string.h"
#include "OrderedList.h"
#include "Card.h"
#include "Bag.h"
#include "List.h"
#include "Queue.h"
#include "Stack.h"

class UnoPlayer {
	std::string _name;
	unsigned int _numCards = 0;
	OrderedList<std::shared_ptr<Card>, IsLessDeref> hand;

public:
	UnoPlayer();
	~UnoPlayer() {}; //nothing to do here

	std::string getName() { return _name; }
	unsigned int getNumCards() { return _numCards; }
	unsigned int checkCard(std::shared_ptr<Card> checkThis);
	void getACard(std::shared_ptr<Card> card);
	void printCardsInHand();
	std::shared_ptr<Card> getCardAt(unsigned int n) { return hand.retrieve(n); }
	std::shared_ptr<Card> playCard(unsigned int n) { _numCards--; return hand.remove(n); }
};

UnoPlayer::UnoPlayer() {
	//have user enter name
	std::cout << "Please enter a name: ";
	std::cin >> _name;
	std::cout << std::endl;
}

//add one card to player hand
void UnoPlayer::getACard(std::shared_ptr<Card> card) {
	hand.insert(card);
	_numCards++;
}

//print current cards in hand
void UnoPlayer::printCardsInHand() {
	std::cout << _name << "'s Cards: " << std::endl;
	for (unsigned int i = 1; i <= _numCards; i++)
		std::cout << *(hand.retrieve(i)) << std::endl;
	std::cout << std::endl;
}

unsigned int UnoPlayer::checkCard(std::shared_ptr<Card> checkThis) {
	for (unsigned int i = 1; i <= _numCards; i++) {
		//check if denom is the same
		if (hand.retrieve(i)->getDenomination() == checkThis->getDenomination())
			return i;
		//check if suit is the same
		if (hand.retrieve(i)->getSuit() == checkThis->getSuit())
			return i;
	}
	
	return -1; //return -1 if no card is matched
}
