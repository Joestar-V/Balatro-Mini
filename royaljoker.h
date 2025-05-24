#ifndef ROYALJOKER_H
#define ROYALJOKER_H

#include "joker.h"
using namespace std ;

class RoyalJoker : public Joker {
public:
    RoyalJoker();
    JokerEffect applyEffect(
        const map<int, int>& rankCounts,
        const map<int, int>& suitCounts,
        int totalRank,
        HandType handType
    ) const override;
};

#endif