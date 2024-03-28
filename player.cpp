#include <string>
#include "player.h"
#include <iostream>
using namespace std;

///
/// Constructors and overloaders
///
Player::Player() //Default constructor
{
	currentCardDupe = true;
	justReset = false;
	for (int k = 0; k < MaxPlayerHandSize; k++)
	{
		hand[k].setCardNumber(0);
		hand[k].setCardType(0);
	}

	for (int k = 0; k < CardDeckSize; k++)
	{
		localDiscard[k].setCardNumber(0);
		localDiscard[k].setCardType(0);
	}

	discardCounter = 0;
}
Player::Player(const Player& obj) //Copy constructor
{
	currentCardDupe = obj.currentCardDupe;
	justReset = obj.justReset;
	for (int k = 0; k < MaxPlayerHandSize; k++)
		hand[k] = obj.hand[k];

	for (int k = 0; k < CardDeckSize; k++)
		localDiscard[k] = obj.localDiscard[k];

	discardCounter = obj.discardCounter;

	// Hello
}
Player::~Player() {} //Destructor



///
/// Mutators
///
void Player::syncDiscard(Card (&globalCards)[CardDeckSize], int & globalCardCounter)
{
	if (justReset) //If our local discard just reset, then the global needs to reset as well
	{
		resetAll(globalCards, globalCardCounter);
		justReset = false;
	}

	for (int k = 0; k < CardDeckSize; k++)
	{

		for (int j = 0; j < MaxPlayerHandSize; j++)
		{
			if (!containsCard(localDiscard, CardDeckSize, hand[j])) //Check to make sure our discard pile automatically includes cards already in our hand
			{
				localDiscard[discardCounter].setCardNumber(hand[j].getCardNumber());
				localDiscard[discardCounter].setCardType(hand[j].getCardType());
				discardCounter++;
			}
		}

		if (!containsCard(localDiscard, CardDeckSize, globalCards[k])) //Check if our localDiscard is out of sync, if so sync them!
		{
			localDiscard[discardCounter].setCardNumber(globalCards[k].getCardNumber());
			localDiscard[discardCounter].setCardType(globalCards[k].getCardType());
			discardCounter++;
		}

		if (!containsCard(globalCards, CardDeckSize, localDiscard[k])) //Check if our globalCards is out of sync, if so sync them!
		{
			globalCards[globalCardCounter].setCardNumber(localDiscard[k].getCardNumber());
			globalCards[globalCardCounter].setCardType(localDiscard[k].getCardType());
			globalCardCounter++;
		}
	}
}

void Player::drawCard()
{
	currentCardDupe = true;

	random_device rd; //Creating a random seed
	mt19937 gen(rd()); //Calling mt19937 random engine with rd seed
	uniform_int_distribution<int> typeDist(1, 4);
	uniform_int_distribution<int> numberDist(1, 13);

	while (currentCardDupe == true)
	{
		setCard(typeDist(gen), numberDist(gen), 0);

		currentCardDupe = false;

		if (hand[0] == hand[1]) //Checks to make sure we didn't draw a card that we already have
		{
			currentCardDupe = true;
		}

		for (int k = 0; k < CardDeckSize; k++) //Checks to ensure we didn't draw a card that we already discarded
		{
			if (localDiscard[k] == hand[0])
			{
				currentCardDupe = true;
			}
		}
	}
}

void Player::shiftHand()
{
	for (int k = (MaxPlayerHandSize - 1); k >= 0; k--) //Shift cards out of hand to the right
	{
		if ((k + 1) < MaxPlayerHandSize)
		{
			hand[k + 1] = hand[k];
		}
	}
}

void Player::discardLastCard()
{

	for (int k = 0; k < MaxPlayerHandSize; k++)
	{
		if (!(containsCard(localDiscard, CardDeckSize, hand[k]))
			&& hand[MaxPlayerHandSize - 1].getCardNumber() != 0 
			&& hand[MaxPlayerHandSize - 1].getCardType() != 0)
		{
			localDiscard[discardCounter] = hand[MaxPlayerHandSize - 1];
			discardCounter++;
		}
	}

	if (discardCounter >= (CardDeckSize - 1)) // Since the card arrays are size 52, they index from (0-51) so we call the reset when the counter reaches 51/the max index.
	{
		justReset = true;
		resetAll();
	}
}

void Player::normalDraw(Card(&obj)[CardDeckSize], int& objCounter)
{
	discardLastCard();
	if (justReset == false)
	{
		shiftHand();
		drawCard();
	}
}

void Player::resetAll()
{
	discardCounter = 0;
	for (int k = 0; k < MaxPlayerHandSize; k++)
	{
		hand[k].setCardNumber(0);
		hand[k].setCardType(0);
	}

	for (int j = 0; j < CardDeckSize; j++)
	{
		localDiscard[j].setCardNumber(0);
		localDiscard[j].setCardType(0);
	}

	justReset = true;
}

void Player::resetAll(Card(&obj)[CardDeckSize], int &inputDiscardCounter)
{
	inputDiscardCounter = 0;
	for (int k = 0; k < CardDeckSize; k++)
	{
		obj[k].setCardNumber(0);
		obj[k].setCardType(0);
	}

	justReset = true;
}


///
/// Accessors
///
void Player::printHand()
{
	if (isHandFresh()) // Avoids printing anything if the hand is empty or 'fresh' (no cards)
	{
		return;
	}

	cout << "----------------------------------------\n";
	for (int k = 0; k < MaxPlayerHandSize; k++)
	{
		cout << hand[k].getCardName() << endl;
	}
	cout << "----------------------------------------\n";
}

Card Player::getCard(int index)
{
	return hand[index];
}

bool Player::isHandFresh()
{
	for (int k = 0; k < MaxPlayerHandSize; k++)
	{
		if (hand[k].getCardNumber() == 0 && hand[k].getCardType() == 0)
		{
			return true;
		}

		if (justReset)
		{
			return true;
		}
	}

	return false;
}



///
/// Other helpful functions
///
void Player::debugDiscard(Card globalDiscard[])
{
	cout << "debugging SELECTED discard pile...\n";
	for (int k = 0; k < CardDeckSize; k++)
	{
		if (!(globalDiscard[k].getCardNumber() == 0 && globalDiscard[k].getCardType() == 0)) {
			cout << "[" << k << "]" << globalDiscard[k].getCardName() << endl;
		}
	}
}

void Player::debugDiscard()
{
	cout << "debugging LOCAL discard pile...\n";
	for (int k = 0; k < CardDeckSize; k++)
	{
		if (!(localDiscard[k].getCardNumber() == 0 && localDiscard[k].getCardType() == 0)) {
			cout << "[" << k << "]" << localDiscard[k].getCardName() << endl;
		}
	}
}

void Player::setCard(int cardtype, int cardnumber, int index)
{
	if (cardtype < 1 || cardtype > 4)
	{
		cout << "\ncardtype is not in range.\n";
	}

	else if (cardnumber < 1 || cardnumber > 13)
	{
		cout << "\ncardnumber is not in range.\n";
	}

	else if (index < 0 || index > MaxPlayerHandSize - 1)
	{
		cout << "\nindex is not in range.\n";
	}

	else 
	{
		hand[index].setCardType(cardtype);
		hand[index].setCardNumber(cardnumber);
	}

}

void Player::setCard(int cardtype, int cardnumber, int index, Card (&cards)[52])
{
	if (cardtype < 1 || cardtype > 4)
	{
		cout << "\ncardtype is not in range.\n";
	}

	else if (cardnumber < 1 || cardnumber > 13)
	{
		cout << "\ncardnumber is not in range.\n";
	}

	else if (index < 0 || index > (CardDeckSize - 1))
	{
		cout << "\nindex is not in range.\n";
	}

	else
	{
		cards[index].setCardType(cardtype);
		cards[index].setCardNumber(cardnumber);
	}

}

bool Player::containsCard(Card arr[], int size, Card target)
{
	for (int i = 0; i < size; i++) {
		if (arr[i] == target) {
			return true;
		}
	}
	return false;
}

