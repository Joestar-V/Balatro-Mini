#ifndef HEARTJOKER_H
#define HEARTJOKER_H

#include "joker.h"
using namespace std ;

class HeartJoker : public Joker {
public:
    HeartJoker();
    JokerEffect applyEffect(
        const map<int, int>& rankCounts,
        const map<int, int>& suitCounts,
        int totalRank,
        HandType handType
    ) const override;
};

#endif