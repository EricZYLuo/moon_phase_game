#include <iostream>

#include "card.h"


int main() {

    Deck* test_deck = new Deck(1,1);
    Card* draw = test_deck->deal();


    while(draw) {
        draw->printCard();
        delete draw;
        draw = test_deck->deal();
    }

    std::cout << std::endl << "BREAK" << std::endl << std::endl;

    delete test_deck;

    test_deck = new Deck();
    test_deck->shuffle();

    draw = test_deck->deal();

    while(draw) {

        draw->printCard();
        delete draw;
        draw = test_deck->deal();
    }

    delete test_deck;

    return 0;
}