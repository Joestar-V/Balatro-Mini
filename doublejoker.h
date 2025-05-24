#ifndef DOUBLEJOKER_H
#define DOUBLEJOKER_H

#include "joker.h"

class DoubleJoker : public Joker {
public:
    DoubleJoker();
    JokerEffect applyEffect(
        const std::map<int, int>& rankCounts,
        const std::map<int, int>& suitCounts,
        int totalRank,
        HandType handType
    ) const override;
};

#endif