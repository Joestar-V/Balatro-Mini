
#ifndef CARD_H
#define CARD_H
#include <algorithm> 
#include <iostream>
#include <vector>
#include <stdexcept>                          
using namespace std ;

//


class Card {

    private:
        int suit; //Suits are as follows 1. Spades 2. Hearts 3. Clubs 4. Diamonds
        int rank; //Ranks are the numbers listed on cards. Ace is 1, Jack is 11, Queen is 12, and King is 13.
        static vector<Card*> deck; //Keeps track of all cards drawn so that there are no repeats <-- This feature went unused in the game because it was unnecesssary and not worth the time to properly implement
    public:

        Card (int r = 1, int s = 1 ) ;
        ~Card();
        int getSuit() const;
        int getRank() const;
        void setSuit(int newSuit) ;
        void setRank(int newRank) ;
        void print() const;
        static void reshuffle();
        Card operator+(int) const; //  <-- This overloaded operator was made with the intention of allowing for easy summation of card values but it turned out to not be necessary.
        
        // Static method to access all instances
        static const vector<Card*>& getDeck(); //  <--With the deck being unused, this method also goes unused
} ;



#endif

