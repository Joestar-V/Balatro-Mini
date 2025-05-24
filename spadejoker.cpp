#include "spadejoker.h"
#include "hand.h"

SpadeJoker::SpadeJoker() : Joker("Spade Joker", "+20 points per Spade") {} //This joker is a child of the Joker class that adds 20 bonus points for every spade in the player's hand


JokerEffect SpadeJoker::applyEffect(
    const map<int, int>& rankCounts,
    const map<int, int>& suitCounts,
    int totalRank,
    HandType handType
) const {
    int spades = suitCounts.count(1) ? suitCounts.at(1) : 0; // Spades = suit 1
    JokerEffect effect;
    effect.points = spades * 20;
    effect.multiplier = 0;
    return effect;
}
   