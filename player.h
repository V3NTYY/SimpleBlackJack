/// 
/// Header file for the Player class. This class handles the actions a player can take on their turn during blackjack,
/// Actions involve hitting, staying, handling discards and bet amounts.
///

#include <string>
#include <random>
#include "card.h"
using namespace std;

class Player {
public:
	
	static const int MaxPlayerHandSize = 2;
	static const int CardDeckSize = 52; //SHOULD NEVER BE ABOVE 52!!!

	/// Constructors
	Player(); //Constructor
	Player(const Player& obj); //Copy constructor
	~Player(); //Destructor

	/// Operators

	/// Mutators
	void syncDiscard(Card (&globalCards)[CardDeckSize], int & globalCardCounter);
	/*
	* Syncs the local discard pile of the player with the selected discard pile
	* Call this everytime changes happen to the discard pile or hand
	*/

	void drawCard(); // Draws a card and sets it to the first index of the players hand
	void shiftHand(); // Shifts the entire hand up by one element
	void discardLastCard(); // Discards the last card in a players hand. If the discard counter would reach > 50 cards, the player object is completely reset.
	void normalDraw(Card (&obj)[CardDeckSize], int &objCounter); // Draw cards, shift them and automatically discard the last. Use this when the player has a full, normal hand
	void resetAll(); //Resets all cards, the local discard pile and the discardCounter to 0
	void resetAll(Card (& obj)[CardDeckSize], int &inputDiscardCounter); //Uses the resetAll method but on another discard pile


	/// Accessors
	void printHand(); // Prints and displays the current active hand of the user.
	Card getCard(int index); // Returns access to a specific card in the hand.
	bool isHandFresh(); // Checks the players hand to see if it has been just reset or is fresh.

	/// Other helpful functions
	void debugDiscard(Card globalDiscard[]); // Programmer-side method for viewing a specific discard pile.
	void debugDiscard(); // Programmer-side method for viewing the local discard pile.
	void setCard(int cardtype, int cardnumber, int index); // Programmer-side method for setting a specific card to a specific index in the local hand.
	void setCard(int cardtype, int cardnumber, int index, Card (&cards)[52]); // Override for setCard that applies to global or other card arrays.

private:
	bool containsCard(Card arr[], int size, Card target); // Method used to check if anywhere in an array a card/element exits, useful for syncing two card arrays.
	Card hand[MaxPlayerHandSize];
	Card localDiscard[CardDeckSize];
	int discardCounter;
	bool currentCardDupe;
	bool justReset;

};