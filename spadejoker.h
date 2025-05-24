#ifndef SPADEJOKER_H
#define SPADEJOKER_H

#include "joker.h"

class SpadeJoker : public Joker {
public:
    SpadeJoker();
    JokerEffect applyEffect(
        const std::map<int, int>& rankCounts,
        const std::map<int, int>& suitCounts,
        int totalRank,
        HandType handType
    ) const override;
};

#endif