#include <iostream> 
#include <vector>
#include "Deck.cpp"

using namespace std;

 class Hand{ 
    public: 
        virtual void drawCard() = 0;
        virtual vector<Card>* getHand() = 0;
 };

class BlackjackHand : public Hand{
    private: 
        vector<Card> cards_in_hand;
        Deck* deck;
        bool standing = false;
    public: 
        BlackjackHand(Deck* _deck){
            deck = _deck;
        };

        void drawCard() override{
            Card tmp_card = deck->drawCard();
            cards_in_hand.push_back(tmp_card);
        }

        void addCard(Card card){
            cards_in_hand.push_back(card);
        }

        vector<Card>* getHand() override {
            return &cards_in_hand;
        }

        void hit(){
            drawCard();
        }

        void stand(){
            standing = true;
        }

        bool takeTurn(){
            if(standing){
                cout << "Player called stand, skipping turn." << endl; 
                return false;
            }
            //Give user their current score and ask them if they want to hit or stand
            
            cout << "Possible Scores: ";
            for (int score : calculateScores()) {
                cout << score << " ";
            }
            cout << endl;

            cout << "Do you want to hit or stand? (hit/stand)" << endl; 
            string action;
            cin >> action;
            if(action == "hit"){
                hit();
            }else if(action == "stand"){
                stand();
            }else{
                cout << "Invalid action. Please enter 'hit' or 'stand'." << endl;
                return false;
            }

            cout << "Action recorded. Your possible scores are: ";
            for (int score : calculateScores()) {
                cout << score << " ";
            }
            cout << endl;

            //Game ends when standing 
            return true;
        }

        vector<int> calculateScores(){
            //Note: Idc about splitting hands
            //We need to return a list of possible scores, and the number of aces
            int aceCounter = 0;
            int sum = 0;
            vector<int> possibleScores;
            for(const Card currCard: cards_in_hand){
                int faceVal = currCard.value;
                if(faceVal == 1){
                    aceCounter++;
                }else if(faceVal > 10){
                    sum += 10;    
                }else{
                    sum += faceVal;
                }
            }
            if(aceCounter == 0){
                possibleScores.push_back(sum);
                return possibleScores;
            }else{
                //add the smallest possibel sum 
                possibleScores.push_back(sum+aceCounter);

                if(aceCounter > 0){
                    //Change one ace
                    int tmpSum = ((aceCounter-1) + sum)+10;
                    if(tmpSum <= 21){
                        possibleScores.push_back(tmpSum);
                    }             
                }

                if(aceCounter > 1){
                    int tmpSum = ((aceCounter-2) + sum)+20;
                    if(tmpSum <= 21){
                        possibleScores.push_back(tmpSum);
                    }             
                }
            }
            return possibleScores;
        }
};

int main(){
    Deck gameDeck; 
    gameDeck.shuffleDeck();

    cout << "Welcome to Blackjack! This will be a 1v1 with the dealer!" << endl; 
    BlackjackHand dealer(&gameDeck);
    BlackjackHand player(&gameDeck);

    // Deal initial cards
    dealer.drawCard();
    dealer.drawCard();
    player.drawCard();
    player.drawCard();

    // Display initial hands
    cout << "Dealer's hand: ";
    gameDeck.printHand(*dealer.getHand());
    cout << "Player's hand: ";
    gameDeck.printHand(*player.getHand());

    // Player's turn
    while(player.takeTurn()){
        cout << "Player's hand: ";
        gameDeck.printHand(*player.getHand());
        
        /*Honestly I ran out of steam and didn't feel
        *like hardcoding a good dealer stategy so here's 
        *what I do when I turn off my brain
        */
        if(dealer.calculateScores().front() < 15){
            dealer.addCard(gameDeck.drawCard());
        }
    }

    // Display final hands
    cout << "Dealer's hand: ";
    gameDeck.printHand(*dealer.getHand());
    cout << "Player's hand: ";
    gameDeck.printHand(*player.getHand());

    // Determine winner
    vector<int> dealerScores = dealer.calculateScores();
    vector<int> playerScores = player.calculateScores();

    //Remove the scores that are over 21
    for(int i = dealerScores.size() - 1; i >= 0; i--){
        if(dealerScores[i] > 21){
            dealerScores.erase(dealerScores.begin() + i);
        }
    }
    for(int i = playerScores.size() - 1; i >= 0; i--){
        if(playerScores[i] > 21){
            playerScores.erase(playerScores.begin() + i);
        }
    }

    //Get the highest scores now that we've removed the busts
    int highestDealerScore = *max_element(dealerScores.begin(), dealerScores.end());
    int highestPlayerScore = *max_element(playerScores.begin(), playerScores.end());

    if(highestDealerScore > 21){
        cout << "Dealer busts! Player wins!" << endl;
    }else if(highestPlayerScore > 21){
        cout << "Player busts! Dealer wins!" << endl;
    }else if(highestDealerScore > highestPlayerScore){
        cout << "Dealer wins!" << endl;
    }else if(highestDealerScore < highestPlayerScore){
        cout << "Player wins!" << endl;
    }else{
        cout << "It's a tie!" << endl;
    }
};