#include <string>

enum Phases {new_moon, waxing_crescent, first_quarter, waxing_gibbeous, full_moon, waning_gibbeous, last_quarter, waning_crescent};

class Card {

    Phases phase;

};

class Deck {

    Card* stack;

};
