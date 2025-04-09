#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <random> 

using namespace std;


enum CardValue {
    JOKER_VALUE = 0,
    ACE = 1,    // Special value for Ace
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    TEN = 10,
    JACK = 11,   
    QUEEN = 12,  
    KING = 13, 
};

enum Suit {
    HEART = 1,
    DIAMOND = 2,
    SPADE = 3, 
    CLUBS = 4,
    JOKER_CARD = 5
};

//Ace will be 1 so when we see that value we know to it can eiter be 1 or 10
//Joker will be 0
//Standard deck of cards has 2 jokers as well, i'll include them for games like cansata and rummy
struct Card{
    CardValue value; 
    Suit suit; 
};

class Deck{
    private: 
        //vector of cards for the whole deck 
        vector<Card> card_deck; 
    public: 
        Deck(bool _addJokers = false){
            //Make the jokers
            if(_addJokers){
                Card joker1 = {JOKER_VALUE, JOKER_CARD};
                Card joker2 = {JOKER_VALUE, JOKER_CARD};
                card_deck.push_back(joker1);
                card_deck.push_back(joker2);
            }

            for(int suit = 1; suit <= 4; suit++){
                for(int value = 1; value <= 13; value++){
                    CardValue currentCardValue = static_cast<CardValue>(value);
                    Suit currentSuit = static_cast<Suit>(suit); 
                    Card currentCard = {currentCardValue, currentSuit};
                    card_deck.push_back(currentCard);
                }
            }
            return;
        }

        string getCardName(CardValue value){
            switch(value) {
                case JOKER_VALUE: return "JOKER";
                case ACE:   return "ACE";
                case TWO:   return "TWO";
                case THREE: return "THREE";
                case FOUR:  return "FOUR";
                case FIVE:  return "FIVE";
                case SIX:   return "SIX";
                case SEVEN: return "SEVEN";
                case EIGHT: return "EIGHT";
                case NINE:  return "NINE";
                case TEN:   return "TEN";
                case JACK:  return "JACK";
                case QUEEN: return "QUEEN";
                case KING:  return "KING";
                default: return "UNKNOWN";
            }
        }

        string suitToString(Suit suit){
            switch(suit){
                case HEART: return "HEARTS";
                case DIAMOND: return "DIAMONDS";
                case SPADE:   return "SPADES";
                case CLUBS:   return "CLUBS";
                case JOKER_CARD:   return "JOKER";
                default:           return "UNKNOWN";
            }

        }
        //function to shuffle the deck 
        void shuffleDeck(){
            //Is there a standard C++ for randomly shuffling a vector?
            random_device rd; 
            mt19937 gen(rd());

            shuffle(card_deck.begin(), card_deck.end(), gen);
        }
        //fucntion to draw card
        Card drawCard(){
            Card topCard = card_deck.back();
            card_deck.pop_back();
            return topCard;
        }
        //draw 1, return me a deck of cards 
        void printDeck(){
            cout << "------" << endl;
            for (const auto& card : card_deck) {
                cout << getCardName(card.value) << " of " << suitToString(card.suit) << endl;
            }
            cout << "------" << endl;
        }

        void printCard(Card card){
            cout << "------" << endl;
            cout << getCardName(card.value) << " of " << suitToString(card.suit) << endl;
            cout << "------" << endl;
        }

        void printHand(vector<Card> hand){
            cout << "------" << endl;
            for (const auto card : hand) {
                cout << getCardName(card.value) << " of " << suitToString(card.suit) << endl;
            }
            cout << "------" << endl;
        }

        int getSize(){
            return card_deck.size();
        }
};
