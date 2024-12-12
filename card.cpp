#include <algorithm>
#include <chrono>
#include <random>
#include <iostream>

#include "card.h"

Card::Card(): id{-1}, phase{new_moon} {}

Card::Card(int id, Phases phase): id{id}, phase{phase} {}

void Card::printCard() {
    std::string names[8] = {"New Moon", "Waxing Crescent", "First Quarter", "Waxing Gibbeous", "Full Moon", "Waning Gibbeous", "Last Quarter", "Waning Crescent"};
    std::cout << names[this->phase] << std::endl;
}

Deck::Deck(): id{-1} {
    // Default deck size of 4 copies of each
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 8; ++j) {
            deck.emplace_back(new Card(i*8+j, (Phases) j));
        }
    }
}

Deck::Deck(int id, int copies): id{id} {
    for(int i = 0; i < copies; ++i) {
        for(int j = 0; j < 8; ++j) {
            deck.emplace_back(new Card(i*8+j, (Phases) j));
        }
    }
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::shuffle(this->deck.begin(), this->deck.end(), std::default_random_engine(seed));

}

Card* Deck::deal() {
    if(!this->deck.empty()) {
        Card* top = this->deck.back();
        this->deck.pop_back();
        return top;
    }
    else {
        std::cerr << "Empty Deck" << std::endl;
        return nullptr;
    }
    
}

Deck::~Deck() {
    Card* top;
    while(!this->deck.empty()) {
        top = this->deck.back();
        this->deck.pop_back();
        delete top;
    }
}
