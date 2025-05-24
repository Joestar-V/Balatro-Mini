#include "round.h"
#include "heartjoker.h"  
#include "spadejoker.h"  
#include "royaljoker.h"  
#include "doublejoker.h"  

#include <cstdlib>  
#include <algorithm>
#include <iomanip>
#include <map>

Round::Round(){ //Default
    number = 0;
    req = 10;
}

Round::Round(const Round& r){ 
    number = r.number + 1; //The newly formed round will be one number greater than the last and have twice it's required value, the passed in jokers will be the same
    req = r.req * 2;
    activeJokers = r.activeJokers;
    
}



bool Round::playRound(){ //This is where the main gameplay loop is ran. 
        
        cout << "\n=====Round: " << number << "=====" << endl; //Display round info
        cout << "Score to beat: " << req << endl;
        // Display active jokers
        if (!activeJokers.empty()) {
            cout << "Active Jokers: ";
            
            // Count joker types
            map<string, int> jokerCounts;
            for (Joker* joker : activeJokers) {
                jokerCounts[joker->getName()]++;
            }
            
            // Display counts
            bool first = true;
            for (const auto& pair : jokerCounts) {
                if (!first) cout << ", ";
                cout << pair.first;
                if (pair.second > 1) {
                    cout << " x" << pair.second;
                }
                first = false;
            }
            cout << endl;
        }
        
        
        
        //Create the hand for this round
        Hand playerHand;

        // Draw 5 cards
        while (!playerHand.IsFull()) {
            playerHand.Draw();
        }
        cout << "\nInitial hand:\n";
        playerHand.Display();
        
         // Discard phase
        playerHand.ProcessDiscards();
        playerHand.Display();

        // 2nd Discard phase
        playerHand.ProcessDiscards();
        
        cout << "\nYour final hand:\n";
        playerHand.Display();
        
        // Calculate hand score and display total points
        int score = playerHand.Tally(activeJokers);
        
        bool winOrLose = score > req;
        if(winOrLose){ //Upon victory
            cout << score << " beats " <<req << ", congratulations!" << endl;
            // Joker selection phase as a reward
            vector<Joker*> jokerPool = {
                new HeartJoker(),
                new SpadeJoker(),
                new RoyalJoker(),  
                new DoubleJoker()      
            };
    
            // Pick 3 random unique jokers
            random_shuffle(jokerPool.begin(), jokerPool.end());
            vector<Joker*> choices(jokerPool.begin(), jokerPool.begin() + 3);
    
            cout << "\nChoose a Joker to add (or 0 to skip):\n";
            for (size_t i = 0; i < choices.size(); ++i) {
                cout << i+1 << ". " << choices[i]->getName() 
                     << " - " << choices[i]->getDescription() << endl;
            }
    
            // Get player choice
            int choice;
            do {
                cout << "Your choice (0-3): ";
                cin >> choice;
                cin.ignore(); // Clear newline
            } while (choice < 0 || choice > 3);
    
            // Add selected joker
            if (choice > 0) {
                activeJokers.push_back(choices[choice-1]);
                cout << "Added " << choices[choice-1]->getName() << "!\n";
                // Delete unchosen jokers
                for (size_t i = 0; i < choices.size(); ++i) {
                    if (i != static_cast<size_t>(choice-1)) {
                        delete choices[i];
                    }
                }
            } else {
                // Clean up all jokers if skipped
                for (Joker* j : choices) delete j;
                cout << "Skipped joker selection.\n";
            }
        }
        else { //In the case that the player loses
            cout << score << " doesn't beat " << req << ", game over!" << endl;
        }
        return(winOrLose);
}
    