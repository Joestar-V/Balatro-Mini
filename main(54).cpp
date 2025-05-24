

/*  Main.cpp
    Title: Balatro-Mini
    Author: Joseph Valencia
    Module: 17
    Project: Final
    Problem Statement: This is an abridged version of the popular card game Balatro 

    Algorithm:
        1. Create the Card class
            a. Each card instance will have the private variables that denotes them such as Suit and Rank
            b. Create a constructor that initializes these values.
            c. Create a destructor that deletes the card from the player's hand.
            d. Create a print funtion that displays the card's identity (ex: 2 of spades)
            e. Overload the + operator to easily add the card's values. 
            f. Create getters to retrieve private variables of the card.
            g. Create setters in the eventuality that tarot cards are added (items that allow the player to modify their cards). <-- This feature was not implemented but the setters are still there.
            h. Create a static variable that keeps track of all cards that have been made. <-- This variable, the deck, is a vector list of cards that was supposed to prevent repeat cards from being played, but this feature wasn't implemented due to being unnecessary.
            k. Create a reshuffler function that removes all cards from the list played cards. <-- This feature was similarly created but not implemented in the game due to being unnecessary 
        2. Create an abstract base class called Joker.
            a. Each joker has a name and a description.
            b. Create a constructor, destructor, a getter for the name, a pure virtual effect function, and a print function that displays what their description is.
        3. Create a subclass of Joker called Heart Joker,
            a. Heart Joker just has an overloaded effect function that gives +2 Multiplier for each heart played.
        4. Create anoter subclass of Joker called Spade Joker.
            a. Overload the effect function to give +20 chips for each spade played.
        5. Create a subclass of Joker called Double Joker,
            a. Double Joker just has an overloaded effect function that gives +20 Multiplier if the hand is a pair.
        6. Create anoter subclass of Joker called Royal Joker.
            a. Overload the effect function to give +40 chips for each king, queen, or jack played.
        7. Create the Hand class
            a. Each hand is a struct containing atleast 5 cards with a HandType variable that will be determined at time of scoring (Pair, Full House, Flush, etc)
            b. Hand needs necessary functions for removing, replacing, and displaying cards, all of which use iterators to navigate across the list.
            c. Create Tally(), a function that counts up the total score of all cards in the hand, evaluates the hand type, executes joker effects, and gives the total score of that hand (total ranks + multiplier)
            d. Each hand type must be defined, both the conditions under which they will be classified and the amount they multiply your score by.
        8. Create the Round class
            a. Each round will have a round number and a required score to beat.
            b. The constructor will either create a default round or set the number and score to be an increment of whatever round is passed in, presumably the previous round. 
            c. Create playRound(), a function that conducts the main gameplay of this game.
            d. Within playRound(), the player picks a joker, a hand is created, and the player is given two opportunities to discard any cards they wish. Then the hand score is tallied and joker effects are applied.
            e. If the tallied scored is greater than the round's required score to beat, the player completes the round and they are prompted to choose one of three random jokers to acquire before they get to move on. Otherwise, it's game over and the loop ends.
        9. Create the main function
            a. After displaying welcome info, the main function creates a random number generator seed so that each run is unique.
            b. Create a default Round and start a while loop that will keep running as long as there's no gameover or exit code.
            c. Within the loop, start a new round based on the old one and execute playRound() to run the game.
            d. After the loop ends (game over), end the program.
*/

#include <iostream>
#include <vector>
#include <cmath>    
#include <string> 
#include <algorithm>
#include "hand.h"
#include "card.h"
#include "round.h"
using namespace std ;


int main() {
    srand(time(0));  // Seed random number generator
    
    //Introduction
    cout << "Welcome to Balatro-Mini! Your goal is to draw and discard cards in order to make the perfect poker hand!" << endl;
    cout << "You have to obtain atleast a certain number of points each round. Your points are equal to the rank (number) of each of your cards multiplied by a multipier."  << endl;
    cout << "Here is a list of the following possible hands you can make, each of them providing a different multiplier: " << endl;
    cout << "Hand types: " << endl << endl;
    cout << "    1 = High Card (None of the below)" << endl;
    cout << "    2 = Pair (Two cards match in rank)" << endl;
    cout << "    3 = Two Pair (Two pairs of cards match in rank)" << endl;
    cout << "    5 = Three of a Kind (Three cards match in rank)" << endl;
    cout << "    10 = Straight (Five cards of consecutive rank value)" << endl;
    cout << "    15 = Flush (Five cards all of the same suit)" << endl;
    cout << "    20 = Full House (Three Cards matching and two other cards matching in rank)" << endl;
    cout << "    25 = Four of a Kind (Four cards matching in rank)" << endl;
    cout << "    50 = Straight Flush (Five cards of the same suit, consecutive in rank value) " << endl;
    cout << "    100 = Royal Flush (An Ace, King, Queen, Jack, and 10, all of the same suit)" << endl << endl;
    
    cout << "You might also find special joker cards at the end of each round, collecting them will change how your score." << endl;
    
    cout << endl << "Now, let's begin!" << endl;
    
    
    
    Round oldRound;
    bool running = true;
    while(running){ // Main Loop
        Round newRound(oldRound);
        
        running = newRound.playRound(); //This is where all the logic and player input occurs
        
        oldRound = newRound;
    }
    //The loop only ends if the player reached a game over, and so now the program ends.    
    
    
    
    

    return 0;
}







