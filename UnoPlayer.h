/*
Name:				Nathan Dimla
Date:				December 7, 2016
Description:		This header file contains the Player object. It has functions to add cards to hand, 
					have the user place a card, and check the user's hand for a matching card
*/
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
	std::string _name; //name of player
	unsigned int _numCards = 0; //number of cards
	OrderedList<std::shared_ptr<Card>, IsLessDeref> hand; //OL container to hold hand of user (with IsLessDeref functor)
	static int count;//static member variable to count number of players

public:
	UnoPlayer();
	~UnoPlayer() {}; //nothing to do here

	std::string getName() { return _name; } //return player name
	unsigned int getNumCards() { return _numCards; } //return number of cards in hand
	unsigned int checkCard(std::shared_ptr<Card> checkThis); //check hand for card that matches
	void getACard(std::shared_ptr<Card> card);//add card to hand
	void printCardsInHand(); //print hand
	std::shared_ptr<Card> getCardAt(unsigned int n) { return hand.retrieve(n); } //look at card at specific location in hand
	std::shared_ptr<Card> playCard(unsigned int n) { _numCards--; return hand.remove(n); } //have player play a card
};

int UnoPlayer::count = 0;//initialize count to 0

UnoPlayer::UnoPlayer() {
	//have user enter name
	std::cout << "Please enter a name for player "  << count + 1 << ": ";
	std::cin >> _name;
	std::cout << std::endl;
	count++;//increase counter
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
