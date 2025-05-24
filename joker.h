#ifndef JOKER_H
#define JOKER_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std ;

class Card;
enum class HandType;

struct JokerEffect { //A JokerEffect consists of two variables, the bonus point and bonus multipliers which will be added to the score.
    int points = 0;
    int multiplier = 0;
};

class Joker { //The abstract joker parent class can't be created but it acts as the framework for all types of jokers.
protected:
    string name;
    string description;
public:
    Joker(const string& n, const string& desc) : name(n), description(desc) {} //Each joker is created with a name and a description
    virtual ~Joker() = default;
    
    virtual JokerEffect applyEffect( //Each joker needs to implement their own version of the applyEffect function, which takes in hand info and returns a JokerEffect
        const map<int, int>& rankCounts,
        const map<int, int>& suitCounts,
        int totalRank,
        HandType handType
    ) const = 0;

    string getName() const { return name; }
    string getDescription() const { return description; }

    void print() const { cout << name << ": " << description << endl; }
};
#endif