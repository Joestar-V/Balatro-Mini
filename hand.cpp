#include "hand.h"
#include "card.h"
#include "joker.h"
#include <cstdlib>
#include <algorithm>
#include <iomanip>
#include <map>

Hand::~Hand() { //Go through and delete each card node in the list
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp->card;  // Delete the Card object
        delete temp;        // Delete the Node
    }
}

void Hand::Draw() { //Draw cards until your hand is full (up to 5)
    if (IsFull()) {
        cout << "Hand is already full!\n";
        return;
    }

    // Generate random card 
    int rank = 1 + rand() % 13;  // 1-13 Ranks
    int suit = 1 + rand() % 4;    // 1-4 Suits
    
    // Add to front of hand
    head = new Node(new Card(rank, suit), head);
    count++;
}

void Hand::Discard(int position) {
    if (position < 1 || position > count) {
        cerr << "Invalid position!\n";
        return;
    }

    if (position == 1) { //Navigate through the hand to find the card at the desired position, then delete the card and arrange the list accordingly
        Node* temp = head;
        head = head->next;
        delete temp->card;
        delete temp;
    } else {
        Node* current = head;
        for (int i = 1; i < position-1; ++i) {
            current = current->next;
        }
        Node* temp = current->next;
        current->next = temp->next;
        delete temp->card;
        delete temp;
    }
    count--;
}

void Hand::Display() const {
    Node* current = head;
    int pos = 1;
    while (current) {
        cout << pos << ". ";
        current->card->print();//Loop through each card in the hand and display it's name and position
        cout << "\n";
        current = current->next;
        pos++;
    }
}

int Hand::Tally(const vector<Joker*>& activeJokers) const { //This is where the total score for this round is calculated and displayed
    // Step 1: Calculate total rank value
    int totalRank = 0;
    map<int, int> rankCounts; // For detecting pairs/triples/etc, these maps are STL data structures that are used here to store a list of values, in this case ranks, and an assosciated count how many times that rank has occured in this hand.
    map<int, int> suitCounts; // For detecting flushes
    
    Node* current = head;
    while (current) {
        int rank = current->card->getRank();  //Loop through each card in hand and extract it's rank and suit information for tallying
        int suit = current->card->getSuit();
        
        totalRank += rank;
        rankCounts[rank]++;
        suitCounts[suit]++;
        
        current = current->next;
    }

    // Step 2: Detect hand features
    bool isFlush = (suitCounts.size() == 1); //The variables created here will be used to determining what type of hand this is. A hand is flush if all hands are of the same suit, so that's why it checks if there's only one suit present in the hand
    bool isStraight = false;
    if (rankCounts.size() == 5) { 
        int minRank = rankCounts.begin()->first;
        int maxRank = rankCounts.rbegin()->first;
        isStraight = (maxRank - minRank == 4); //A hand is straight when all the cards have consecutive numeric value, and if that's the case then the difference between the first card and last card will always be 4.
    }

    int pairs = 0, triples = 0, quads = 0;
    for (const auto& entry : rankCounts) {  //Check for matching cards, determining if they're pairs, triplets, or four a kind
        if (entry.second == 2) pairs++;
        else if (entry.second == 3) triples++;
        else if (entry.second == 4) quads++;
    }

    // Step 3: Determine hand type (in order of priority)
    HandType handType = HandType::HIGH_CARD; //The handType enum stores the multiplier value we'll be using in scoring, so first we must determine what type the handType is.

    // Check for Royal Flush or Straight Flush
    if (isFlush && isStraight) {
        handType = (rankCounts.rbegin()->first == 13) ? HandType::ROYAL_FLUSH : HandType::STRAIGHT_FLUSH;
    }
    // Check for Four of a Kind
    else if (quads == 1) {
        handType = HandType::FOUR_OF_A_KIND;
    }
    // Check for Full House
    else if (triples == 1 && pairs == 1) {
        handType = HandType::FULL_HOUSE;
    }
    // Check for Flush
    else if (isFlush) {
        handType = HandType::FLUSH;
    }
    // Check for Straight
    else if (isStraight) {
        handType = HandType::STRAIGHT;
    }
    // Check for Three of a Kind
    else if (triples == 1) {
        handType = HandType::THREE_OF_A_KIND;
    }
    // Check for Two Pair
    else if (pairs >= 2) {
        handType = HandType::TWO_PAIR;
    }
    // Check for One Pair
    else if (pairs == 1) {
        handType = HandType::ONE_PAIR;
    }
    // Default to High Card
    else {
        handType = HandType::HIGH_CARD;
    }
    
    //Step 3: Determine joker bonus
    
    
    int jokerPoints = 0;
    int jokerMult = 0;
    for (const Joker* joker : activeJokers) { //Loop through all jokers that the player has and run their effect, passing in all the data collected thus far for the joker to work with
        JokerEffect effect = joker->applyEffect(rankCounts, suitCounts, totalRank, handType); //Each joker will create an effect using their applyEffect function, that effect consists of a points variable and a multiplier variable
        jokerPoints += effect.points;
        jokerMult += effect.multiplier;
    }
    
    // Step 4: Calculate final score
    int finalScore = (totalRank  + jokerPoints) * (static_cast<int>(handType) + jokerMult); //The grand total score is calculated first by adding the total rank tally with bonus joker points, then adding together the hand type multiplier with the bonus joker multiplier, then multiplying the two sums
    
    // Display results in separate rows
    cout << "┌───────────────────────┐\n";
    cout << "│ Hand Type: " << left << setw(11) << GetHandTypeName(handType) << "│\n";
    cout << "├───────────────────────┤\n";
    cout << "│ Total Ranks: " << left << setw(8) << totalRank << "│\n";
    cout << "├───────────────────────┤\n";
    cout << "│ Joker Points: " << left << setw(8) << jokerPoints << "│\n";
    cout << "├───────────────────────┤\n";
    cout << "│ Joker Multiplier: " << left << setw(8) << jokerMult << "│\n";
    cout << "├───────────────────────┤\n";
    cout << "│ Final Score: " << left << setw(8) << finalScore << "│\n";
    cout << "└───────────────────────┘\n";

    
    return finalScore;
}

void Hand::ReplaceDiscarded() {
    while (!IsFull()) {
        Draw();
    }
}

void Hand::ProcessDiscards() { //This runs during the discard phase, which is ran twice each round. The player must choose the positions of any cards they wish to discard, or skip by typing 0
    string input;
    vector<int> positions;
    
    cout << "\nEnter card positions to discard (e.g. 124 or 0 to skip): ";
    getline(cin, input); //Get user input

    // Handle skip
    if (input == "0") return;

    // Validate and collect positions
    for (char c : input) {
        if (isdigit(c)) {
            int pos = c - '0';
            if (pos >= 1 && pos <= 5) {
                positions.push_back(pos);
            }
        }
    }

    // Remove duplicates and sort descending 
    sort(positions.rbegin(), positions.rend());
    positions.erase(unique(positions.begin(), positions.end()), positions.end());

    // Discard cards (from highest to lowest to maintain positions)
    for (int pos : positions) {
        if (pos <= Size()) {  // Double-check valid position
            Discard(pos);
        }
    }

    // Replace discarded cards
    ReplaceDiscarded();
}

string Hand::GetHandTypeName(HandType type) { //This returns the name of each card type in a displayable string format
    switch(type) {
        case HandType::HIGH_CARD: return "High Card";
        case HandType::ONE_PAIR: return "One Pair";
        case HandType::TWO_PAIR: return "Two Pairs";
        case HandType::THREE_OF_A_KIND: return "Three of a Kind";
        case HandType::STRAIGHT: return "Straight";
        case HandType::FLUSH: return "Flush";
        case HandType::FULL_HOUSE: return "Full House";
        case HandType::FOUR_OF_A_KIND: return "Four of a Kind";
        case HandType::STRAIGHT_FLUSH: return "Straight Flush";
        case HandType::ROYAL_FLUSH: return "Royal Flush";
        default: return "Unknown";
    }
}

bool Hand::operator>(const int other) { // <-- This is an unused functionality originally intended to see if the player's score was higher than the requirement to beat, but it proved to be inefficient.
            //return this->Tally() > other;
            return false;
        }
        