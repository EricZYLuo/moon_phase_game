#include <iostream>

#include "card.h"


int main() {

    Deck* test_deck = new Deck(1,1);
    Card* draw = nullptr;

    do {

        draw = test_deck->deal();
        draw->printCard();

    } while(draw);

    std::cout << std::endl << "BREAK" << std::endl << std::endl;

    delete test_deck;

    test_deck = new Deck(2, 4);
    test_deck->shuffle();

    do {

        draw = test_deck->deal();
        draw->printCard();

    } while(draw);

    return 0;
}