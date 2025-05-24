#include "card.h"
#include <algorithm> 
#include <iostream>

vector<Card*> Card::deck; // Initialize static member //  <-- The deck is an unused list



Card::Card(int r, int s) : rank(r), suit(s) { 
    deck.push_back(this);  // Add to deck list when created //  <-- Adding the card to the deck is not relevant but defining it's variables is
}

Card::~Card() {
        
        
        // Remove from deck when destroyed //  <-- This code was made unnecessary by the lack of deck implementation
        //auto it = find(deck.begin(), deck.end(), this);
        //if (it != deck.end()) {
        //    deck.erase(it);
        //}
        
    }
    

const vector<Card*>& Card::getDeck() { //  <-- This code was made unnecessary by the lack of deck implementation
    return deck;
}

int Card::getSuit() const  {
    return suit;
}

int Card::getRank() const {
    return rank;  
}


void Card::setSuit(int newSuit){
    suit = newSuit;
}
void Card::setRank(int newRank){
    rank = newRank;
}

void Card::print() const { //This function allows for the cards to be displayed properly following the format : "rank" of "suit" (ex: 3 of clubs, king of diamonds, etc)
    switch(rank){
        case 1:
            cout << "Ace of ";
            break;
        case 11:
            cout << "Jack of ";
            break;
        case 12:
            cout << "Queen of ";
            break;
        case 13:
            cout << "King of ";
            break;
        default:
            cout << rank << " of ";
            break;
    }
    switch(suit){
        case 1:
            cout << "Spades";
            break;
        case 2:
            cout << "Hearts";
            break;
        case 3:
            cout << "Clubs";
            break;
        case 4:
            cout << "Diamonds";
            break;
        
    }
}

 void Card::reshuffle() { //  <-- This code was made unnecessary by the lack of deck implementation
    for (Card* instance : deck) {
        delete instance;  // Explicitly free memory
    }
    deck.clear(); // Clear the list afterward
}

// The overloaded + operator was made for adding card values but this was rendered an inefficient way to do it and so it goes unused.
Card Card::operator+(int value) const {
    return Card(rank + value, suit);
}


