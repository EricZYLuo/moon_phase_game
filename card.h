#include <string>
#include <queue>

enum Phases {new_moon = 0, waxing_crescent = 1, first_quarter = 2, waxing_gibbeous = 3, full_moon = 4, waning_gibbeous = 5, last_quarter = 6, waning_crescent = 7};

class Card {
    int id;
    Phases phase;

public:
    Card();
    Card(int id, Phases phase);


};

class Deck {
    int id;
    std::queue<Card*> deck;

    void shuffle();

public:
    Deck();
    Deck(int id, int copies);
    Card* deal();
    ~Deck();

};
