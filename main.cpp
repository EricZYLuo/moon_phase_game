#include <iostream>

#include "card.h"
#include "map.h"


int main() {


    /*

    *** Deck and Card Testing ***

    Deck* test_deck = new Deck{1,1};
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
    */

   /*
   ***Testing Map***
   */
    std::vector<std::pair<int, int> > connections{std::pair{0,1}, std::pair{0,2}, std::pair{1,3}, std::pair{2,3}};

    Map mymap{0, 4, connections}; 

    // Deck deck{1,1};
    // deck.shuffle();
    Card* firstCard = new Card(1, Phases::new_moon);
    Card* secondCard = new Card(2, Phases::waxing_crescent);
    Card* thirdCard = new Card(3, Phases::first_quarter);
    
    mymap.placeCard(0, firstCard, 1);
    mymap.placeCard(1, secondCard, 1);
    mymap.placeCard(3, thirdCard, 1);
    
    mymap.logMap();

    return 0;
}