#include "heartjoker.h"
#include "hand.h"

HeartJoker::HeartJoker() : Joker("Heart Joker", "+2 Multiplier per Heart") {} //This joker is a child of the Joker class that gives the player +2 Multiplier for every heart in their hand. Through inheritance, it has the same variables and functions as it's parent

JokerEffect HeartJoker::applyEffect(
    const map<int, int>& rankCounts,
    const map<int, int>& suitCounts,
    int totalRank,
    HandType handType
) const { //This Joker's unique effect is implemented here through polymorphism of the Joker's pure virtual function. First it counts how many hearts there are and then it mulplies that amount by 2 to get the multiplier bonus.
    int hearts = suitCounts.count(2) ? suitCounts.at(2) : 0; // Hearts = suit 2
    JokerEffect effect;
    effect.points = 0;
    effect.multiplier = hearts * 2; // +2 per heart
    return effect;
}