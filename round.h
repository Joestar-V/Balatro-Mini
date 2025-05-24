

#ifndef ROUND_H
#define ROUND_H

#include <algorithm> 
#include <iostream>
#include <vector>
#include <stdexcept>                         
using namespace std ;

#include "card.h"
#include "hand.h"
#include "joker.h"
class Joker;

class Round { //Each round has a number and a score to beat. Since it handles the player's interactions and can pass info into the next round, it also holds onto the player's list of jokers for them.

    private:
        int number;
        int req; //The score to beat
        vector<Joker*> activeJokers;  // Active Jokers for this round
        
    public:
        
        Round(); //Default round constructor (round 0)
        Round(const Round& r); //Round constructor that passes in the previous round to form the next one
        
        bool playRound();
        
        void addJoker(Joker* joker) { activeJokers.push_back(joker); }
        const vector<Joker*>& getJokers() const { return activeJokers; }

        
};

#endif
