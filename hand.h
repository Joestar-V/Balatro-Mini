


#ifndef HAND_H
#define HAND_H

#include <algorithm> 
#include <iostream>
#include <vector>
#include <stdexcept>                          
using namespace std ;

#include "card.h"  
#include "joker.h"
enum class HandType { // This enum consists of the names and multiplier values of each different type of hand. The meaning of each hand is described in the game's intro and below.
            HIGH_CARD = 1,
            ONE_PAIR = 2,
            TWO_PAIR = 3,
            THREE_OF_A_KIND = 5,
            STRAIGHT = 10,
            FLUSH = 15,
            FULL_HOUSE = 20,
            FOUR_OF_A_KIND = 25,
            STRAIGHT_FLUSH = 50,
            ROYAL_FLUSH = 100
        };
        
/*
    Hand types:
    1 = High Card (None of the below)
    2 = Pair (Two cards match in rank)
    3 = Two Pair (Two pairs of cards match)
    5 = Three of a Kind (Three cards match)
    10 = Straight (Five cards of consecutive rank value)
    15 = Flush (Five cards all of the same suit)
    20 = Full House (Three Cards matching and two other cards matching )
    25 = Four of a Kind (Four cards matching)
    50 = Straight Flush (Five cards of the same suit, consecutive in rank value)
    100 = Royal Flush (An Ace, King, Queen, Jack, and 10, all of the same suit)
    
    These are used to determine your multiplier at the end of your round, and so the hand type will be determined then.
*/

class Hand {

    private:
        struct Node { //The hand is a list of card nodes, a unique data structure for this game
            Card* card;
            Node* next;
            Node(Card* c, Node* n = nullptr) : card(c), next(n) {}
        };
        
        Node* head;
        
        
        int count;  // Tracks current hand size
        
    
    public:

        Hand() : head(nullptr), count(0) {}
        ~Hand();
    
        void Draw(); 
        void Discard(int position);  // Removes cards from your hand
        void Display() const;
        int Tally(const vector<Joker*>& activeJokers) const;  // This function calculates and displays the total score of your hand for this round
        bool IsFull() const { return count == 5; }
        int Size() const { return count; }
        void ReplaceDiscarded(); // Replaces removed cards
        void ProcessDiscards();
        static string GetHandTypeName(HandType type);     
        bool operator>(const int other) ; // <-- unused functionality for comparing values of hands to see which is bigger
};

#endif
