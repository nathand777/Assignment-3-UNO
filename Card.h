/*
Name:				Nathan Dimla
Date:				December 7, 2016
Description:		This header is a modified Card header from lab 9. It contains an Uno card instead
					for the use of this assignment.
*/
#pragma once
#include <iostream>

// User defined Suit and Denomination types (user-defined integers) 
enum Suit { RED = 1, YELLOW = 2, BLUE = 3, GREEN = 4 };
enum Denomination { N1 = 1, N2 = 2, N3 = 3, N4 = 4, N5 = 5};


class Card
{
public:
	Card(Suit suit = RED, Denomination denomination = N5); // constructor with some default values
	~Card(); // destructor
	inline Suit getSuit(void) const { return m_suit; }
	inline Denomination getDenomination(void) const { return m_denomination; }
	char toCharSuit(void); // returns a char that "describes" card's suit
	char toCharDenomination(void); // returns a char that "describes" card's denomination

private:
	 Suit m_suit; // private storage of suit
	 Denomination m_denomination; // private storage of denomination
	 friend std::ostream& operator<<(std::ostream& os, const Card &c);
};

// global operator functions comparing denominations of two cards
// The cards a and b are passed by reference
inline bool operator<(const Card& a, const Card& b) {
	if (a.getSuit() == b.getSuit()) return (a.getDenomination()<b.getDenomination());
	else                            return (a.getSuit()<b.getSuit());
}
inline bool operator>(const Card& a, const Card& b) {
	if (a.getSuit() == b.getSuit()) return (a.getDenomination()>b.getDenomination());
	else                            return (a.getSuit()>b.getSuit());
}

// checks equality of suits and denominations for two cards
inline bool operator==(Card& a, Card& b) { return (a.getDenomination() == b.getDenomination() && a.getSuit() == b.getSuit()); }

Card::Card(Suit suit, Denomination denomination)
	: m_suit(suit)
	, m_denomination(denomination)
{
}

// destructor
Card::~Card()
{
}

//get char from suit
char Card::toCharSuit()
{
	if (m_suit == RED)   return 'R';
	else if (m_suit == YELLOW)    return 'Y';
	else if (m_suit == BLUE)   return 'B';
	else                       return 'G';
}

//get char from denom
char Card::toCharDenomination()
{
	if (m_denomination == N1)	return '1';
	else if (m_denomination == N2)	return '2';
	else if (m_denomination == N3)	return '3';
	else if (m_denomination == N4)	return '4';
	else                            return '5';
}

//operator overload for printing out
std::ostream& operator<<(std::ostream& os, const Card &c) {
	int suit = c.getSuit();
	int demo = c.getDenomination();

	switch (suit) {
	case 1:
		os << "Red-";
		break;
	case 2:
		os << "Yellow-";
		break;
	case 3:
		os << "Blue-";
		break;
	default:
		os << "Green-";
	}
	os << demo;
	return os;
}