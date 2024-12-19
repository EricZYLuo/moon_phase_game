#ifndef __CARD_H_INCLUDED__
#define __CARD_H_INCLUDED__

#include <string>
#include <vector>

enum Phases {new_moon = 0, waxing_crescent = 1, first_quarter = 2, waxing_gibbeous = 3, full_moon = 4, waning_gibbeous = 5, last_quarter = 6, waning_crescent = 7};

class Card {
    int id;
    Phases phase;

public:
    Card();
    Card(int id, Phases phase);
    Phases getPhase();
    // Temp for console output, eventually implement/replace drawCard
    void printCard();


};

class Deck {
    int id;
    std::vector<Card*> deck;

    
public:
    Deck();
    Deck(int id, int copies);
    Card* deal();
    void shuffle();
    ~Deck();

};


#endif