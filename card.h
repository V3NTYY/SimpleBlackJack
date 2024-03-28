/// 
/// Header file for the Card class. This class handles card attributes.
///

#include <string>
#include <random>
using namespace std;

class Card {
public:

	/// Constructors
	Card(); //Default Constructor
	Card(int numType, int numCard); //Non-Default Constructor
	Card(Card& obj); //Copy constructor
	Card(Card&& obj) noexcept; //Move constructor
	~Card(); //Destructor

	// Operators
	bool operator==(const Card& obj);
	Card& operator=(const Card& obj);

	/// Mutators
	void setCardType(int CardType); //Sets card type
	void setCardNumber(int CardNumber); //Sets card number

	/// Accessors
	const int getCardType(); //Gets card type
	const int getCardNumber(); //Gets card number
	const string getCardName(); //Finds the name of current card

	/// Other helpful functions


private:
	int cardType; // cardType ranges from 1-4 (spades, hearts, diamonds, clubs)
	int cardNumber; // cardNumber ranges from 1-13, involves face cards (1=Ace, 11=Jack, 12=Queen, 13=King)
	string cardName = "";

};