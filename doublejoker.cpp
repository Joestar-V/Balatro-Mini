#include "doublejoker.h"
#include "hand.h"

DoubleJoker::DoubleJoker() : Joker("Double Joker", "+20 multipler if hand is a Pair") {} //This joker is a child of the Joker class that adds 20 bonus multiplier if the player's hand is a Pair


JokerEffect DoubleJoker::applyEffect(
    const map<int, int>& rankCounts,
    const map<int, int>& suitCounts,
    int totalRank,
    HandType handType
) const {
    JokerEffect effect;
    if (handType == HandType::ONE_PAIR){ //Check if the hand is a pair, if so add 20 bonus mult, if not then add nothing
        effect.multiplier = 20;
    }
    else {
        effect.multiplier = 0;
    }
    effect.points = 0;
    return effect;
}