#include <string>
#include "card.h"
using namespace std;

///
/// Constructors, overloaders
///
Card::Card() //Default constructor
{
	cardType = 1;
	cardNumber = 1;
}

Card::Card(int numType, int numCard) //Non-Default constructor
{
	cardType = numType;
	cardNumber = numCard;
}

Card::Card(Card& obj) //Copy constructor
{
	cardType = obj.getCardType();
	cardNumber = obj.getCardNumber();
}

Card::Card(Card&& obj) noexcept { //Move constructor
	cardType = move(obj.cardType);
	cardNumber = move(obj.cardNumber);
	cardName = move(obj.cardName);
}

Card::~Card() {} //Destructor

bool Card::operator==(const Card& obj) //Overloading == operator
{
	if (cardType == obj.cardType && cardNumber == obj.cardNumber)
	{
		return true;
	}
	else {
		return false;
	}
}

Card& Card::operator=(const Card& obj) //Overloading the = operator
{
	if (this != &obj) {
		cardType = obj.cardType;
		cardNumber = obj.cardNumber;
		cardName = obj.cardName;
	}
	return *this;
}

///
/// Setters
///
void Card::setCardType(int CardType)
{
	cardType = CardType;
}
void Card::setCardNumber(int CardNumber)
{
	cardNumber = CardNumber;
}

///
/// Getters
///
const int Card::getCardType() //Returns the numerical index of card type
{
	return cardType;
}
const int Card::getCardNumber() //Returns the numerical index of card number
{
	return cardNumber;
}

const string Card::getCardName() //This method uses several switch statements to splice a string that returns the name of a card
{
	cardName = "";

	switch (cardNumber) {
	case 0:
		cardName = cardName + "INVALID_CARD_NUMBER of ";
		break;
	case 1:
		cardName = cardName + "Ace of ";
		break;
	case 2:
		cardName = cardName + "2 of ";
		break;
	case 3:
		cardName = cardName + "3 of ";
		break;
	case 4:
		cardName = cardName + "4 of ";
		break;
	case 5:
		cardName = cardName + "5 of ";
		break;
	case 6:
		cardName = cardName + "6 of ";
		break;
	case 7:
		cardName = cardName + "7 of ";
		break;
	case 8:
		cardName = cardName + "8 of ";
		break;
	case 9:
		cardName = cardName + "9 of ";
		break;
	case 10:
		cardName = cardName + "10 of ";
		break;
	case 11:
		cardName = cardName + "Jack of ";
		break;
	case 12:
		cardName = cardName + "Queen of ";
		break;
	case 13:
		cardName = cardName + "King of ";
		break;
	}

	switch (cardType) {
	case 0:
		cardName = cardName + "INVALID_CARD_TYPE";
		break;
	case 1:
		cardName = cardName + "Spades";
		break;
	case 2:
		cardName = cardName + "Hearts";
		break;
	case 3:
		cardName = cardName + "Diamonds";
		break;
	case 4:
		cardName = cardName + "Clubs";
		break;
	}

	return cardName;
}

///
/// Other useful functions
///