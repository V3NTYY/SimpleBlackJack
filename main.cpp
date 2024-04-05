#include <iostream>
#include <iomanip>
#include "player.h"
using namespace std;

// Test comment.

/// HELLO! Sorry if those code is messy, it is old code from when I first started programming. Feel free to browse :)

	//////////////////// VARIABLE DECLARATION ////////////////////

bool inGame = 0;
char hitOrStay = 0;
int choice = 0;
const int MaxCardSize = Player::CardDeckSize;
const int MaxHandSize = Player::MaxPlayerHandSize;
Card globalCards[MaxCardSize]; // Card array that holds all of the cards.
int globalCardCounter = 0; // Keep track of the amount of cards currently in play.

Player player1;
int playerCounter;
Player dealer;
int dealerCounter;

vector<Card> playerCheckedCards(1);
vector<Card> dealerCheckedCards(1);

	//////////////////// END OF SECTION ////////////////////



	//////////////////// METHODS ////////////////////
void ClearScreen() //Clears console
{
	system("CLS");
}

bool containsCard(vector<Card> v, Card target) //Checks to see if a vector contains a card
{
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == target) {
			return true;
		}
	}
	return false;
}

void printVector(vector<Card> v) //Prints out the contents of a card vector
{
	for (int k = 0; k < v.size(); k++)
	{
		if (!(v[k].getCardNumber() == 0 && v[k].getCardType() == 0))
		{
			cout << v[k].getCardName() << endl;
		}
	}
}

void printBothHands() //Prints out the hand of both the dealer and player in blackjack
{
	cout << "Dealer's Hand\n";
	cout << "-------------------------\n";
	printVector(dealerCheckedCards);
	cout << "-------------------------\n\n\n\n";
	cout << "-------------------------\n";
	cout << "Your Hand\n";
	cout << "-------------------------\n";
	printVector(playerCheckedCards);
	cout << "-------------------------\n";
}

void resetCheckedCards()
{
	playerCheckedCards.clear();
	dealerCheckedCards.clear();
	playerCounter = 0;
	dealerCounter = 0;
}

void calculateHand(bool isFresh)
{
	int modifier = 0;
	int aceCheck = 1;

	for (int k = 0; k < MaxHandSize; k++)
	{
		if (!containsCard(playerCheckedCards, player1.getCard(k))) //If we haven't checked this card, add it to our point total.
		{
			modifier = player1.getCard(k).getCardNumber();

			if (modifier > 10) //If we draw a face card, we need to adjust its cardNumber value to represent its blackjack value.
			{
				modifier = 10;
			}

			if (modifier == 1) //If we draw an ace the user gets to choose if it is a 1 or an 11.
			{
				if (isFresh)
				{
					cout << "Your Hand\n";
					player1.printHand();
				}
				if ((playerCounter + modifier) >= 21)
				{
					modifier = 1;
				}
				else {
					cout << "You drew an ace! Are you declaring it as a 1 or an 11? (Enter 1 or 11):\n";
					cin >> aceCheck;
					ClearScreen();
					if (aceCheck == 1)
					{
						modifier = 1;
					}
					if (aceCheck == 11)
					{
						modifier = 11;
					}
					else {
						cin.ignore();
						cin.clear();
						modifier = 1;
					}
				}
			}

			playerCounter = playerCounter + modifier;
			playerCheckedCards.emplace_back(player1.getCard(k)); //Make sure we mark the card as checked.
			modifier = 0; //Reset the modifier
		}
	}

	for (int j = 0; j < MaxHandSize; j++)
	{
		if (!containsCard(dealerCheckedCards, dealer.getCard(j)))
		{
			modifier = dealer.getCard(j).getCardNumber();

			if (modifier > 10) //If we draw a face card, we need to adjust its cardNumber value to represent its blackjack value.
			{
				modifier = 10;
			}

			if (modifier == 1) //If we draw an ace the dealer will evaluate the best option
			{
				if ((dealerCounter + modifier) > 21)
				{
					modifier = 1;
				}
				else {
					modifier = 11;
				}
			}

			dealerCounter = dealerCounter + modifier;
			dealerCheckedCards.emplace_back(dealer.getCard(j));
		}
	}
}

void syncAllCards() //Syncs all player hands/cards, call this everytime any player draws a card or their hand changes.
{
	player1.syncDiscard(globalCards, globalCardCounter);
	dealer.syncDiscard(globalCards, globalCardCounter);
	player1.syncDiscard(globalCards, globalCardCounter);
	dealer.syncDiscard(globalCards, globalCardCounter);
}

	//////////////////// END OF SECTION ////////////////////

void MainMenu(int &choice) //Main menu
{
	retry:
	cout << "Welcome to BLACKJACK 1.0, please select a following option:\n";
	cout << "(1) Play a game of Blackjack\n";
	cout << "(2) Read on how to play Blackjack\n";
	cout << "(3) Exit BLACKJACK 1.0\n";
	cin >> choice;
	
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		ClearScreen();
		goto retry;
	}

	if (choice != 1 && choice != 2 && choice != 3)
	{
		ClearScreen();
		goto retry;
	}
}

int main()
{
	//////////////////// USER SELECTION ////////////////////

	Start:
	while (inGame == false)
	{
		MainMenu(choice);
		ClearScreen();
		switch(choice)
		{
		case 1:
			ClearScreen();
			inGame = true;
			break;
		case 2:
			cout << "////////////////////////////////////////////////////////////////////////////////////////\n";
			cout << "To play Blackjack, the goal is to simply be the first one to reach a card/hand value of 21.\n";
			cout << "You start with a randomly drawn hand of 2 cards, you compete with the dealer.\n";
			cout << "On your turn, you can choose to either hit or stay which will determine if you draw a card or not.\n";
			cout << "If you hit, you draw a card; if the card makes you exceed over 21, then you bust and lose.\n";
			cout << "If you stay, you let the dealer hit as many times as they please until they bust or are satisifed.\n";
			cout << "Face cards or the odd cards are also worth 10 points each.\n";
			cout << "Whichever one of you reaches 21 the closest is the winner, good luck!\n";
			cout << "////////////////////////////////////////////////////////////////////////////////////////\n\n";
			break;
		case 3:
			ClearScreen();
			exit(0);
		}
	}

	//////////////////// GAME SETUP / PLAY ////////////////////

	while (inGame)
	{
		player1.resetAll();
		player1.resetAll(globalCards, globalCardCounter);
		dealer.resetAll();
		dealer.resetAll(globalCards, globalCardCounter);
		syncAllCards();

		displayPoint:

		if (player1.isHandFresh())
		{
			player1.normalDraw(globalCards, globalCardCounter);
			player1.normalDraw(globalCards, globalCardCounter);
			calculateHand(true);
			syncAllCards();
		}

		if (dealer.isHandFresh())
		{
			dealer.normalDraw(globalCards, globalCardCounter);
			dealer.normalDraw(globalCards, globalCardCounter);
			calculateHand(true);
			syncAllCards();
		}

		printBothHands();

		if (playerCounter < 21) {
			cout << endl << "Would you like to Hit or Stay? (H/S):\n";
			cin >> hitOrStay;
		}
		if (playerCounter == 21) {
			hitOrStay = 's';
		}

		if (hitOrStay == 'h' || hitOrStay == 'H')
		{
			player1.normalDraw(globalCards, globalCardCounter);
			ClearScreen();
			calculateHand(false);
			syncAllCards();
			if (playerCounter > 21)
			{
				cout << "You drew a " << player1.getCard(0).getCardName() << " and busted! Game over.\n";
				resetCheckedCards();
				inGame = false;
				goto Start;
			}
			goto displayPoint;
		}

		if (hitOrStay == 's' || hitOrStay == 'S')
		{
			bool keepDrawing = true;
			while (keepDrawing)
			{
				if (dealerCounter >= 17 || dealerCounter > playerCounter) //The dealers strategy is to keep drawing until he hits 17 or above!
				{
					keepDrawing = false;
					break;
				}
				dealer.normalDraw(globalCards, globalCardCounter);
				calculateHand(false);
				syncAllCards();
			}
			if (dealerCounter == 21 && playerCounter == 21) //Did the dealer reach 21? Tie
			{
				ClearScreen();
				printBothHands();
				cout << "You have tied with the dealer! Good playing!\n";
				resetCheckedCards();
				inGame = false;
				goto Start;
			}
			if (dealerCounter == 21 && playerCounter < 21) //Did the dealer reach 21 and the player didn't? Dealer victory
			{
				ClearScreen();
				printBothHands();
				cout << "You have lost! The dealer hit 21, good try though!\n";
				resetCheckedCards();
				inGame = false;
				goto Start;
			}
			if (playerCounter == 21 && dealerCounter < 21) //Did the player hit 21 and the dealer didn't? Player victory
			{
				ClearScreen();
				printBothHands();
				cout << "You hit 21 while the dealer had to stand, Victory! Good Job!\n";
				resetCheckedCards();
				inGame = false;
				goto Start;
			}
			if (dealerCounter > 21) //Did the dealer bust? Player victory
			{
				ClearScreen();
				printBothHands();
				cout << "You won! The dealer busted by " << (dealerCounter - 21) << " point(s). Good job!\n";
				resetCheckedCards();
				inGame = false;
				goto Start;
			}
			if (dealerCounter > playerCounter) //Did the dealer get closer to 21? Dealer victory
			{
				ClearScreen();
				printBothHands();
				cout << "Oh no, you lost! The dealer was closer to 21 than you were, nice try!\n";
				resetCheckedCards();
				inGame = false;
				goto Start;
			}
			if (playerCounter > dealerCounter) //Did the player get closer to 21? Player victory
			{
				ClearScreen();
				printBothHands();
				cout << "You won! Neither of you hit 21 however you were closer. Good job!\n";
				resetCheckedCards();
				inGame = false;
				goto Start;
			}
		}

		else {
			ClearScreen();
			cout << "Please enter a valid input!!!\n\n\n";
			goto displayPoint;
		}
	}

	return 0;
}