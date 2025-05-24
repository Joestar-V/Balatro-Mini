#include "royaljoker.h"
#include "hand.h"

RoyalJoker::RoyalJoker() : Joker("Royal Joker", "+40 points per face card (King, Queen, Jack)") {} //This joker is a child of the Joker class that adds 40 bonus points for every face card in the player's hand


JokerEffect RoyalJoker::applyEffect(
    const map<int, int>& rankCounts,
    const map<int, int>& suitCounts,
    int totalRank,
    HandType handType
) const {
    int faceCards = 0;
    // Add up all face cards in hand;
    if (rankCounts.count(11)) faceCards += rankCounts.at(11);
    if (rankCounts.count(12)) faceCards += rankCounts.at(12);
    if (rankCounts.count(13)) faceCards += rankCounts.at(13);
    
    JokerEffect effect;
    effect.points = faceCards * 40;
    effect.multiplier = 0;
    return effect;
}