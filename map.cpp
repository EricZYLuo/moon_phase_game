#include "map.h"

Tile::Tile(int id): id{id}, filled{nullptr}, owned{0} {}

void Tile::setCard(Card* card, int player) {
    if(this->filled != nullptr) {
        std::cerr << "Attempted to fill already filled space with id " << this->id << std::endl;
    }
    else {
        this->filled = card;
        this->setPlayer(player);
    }
}

void Tile::setPlayer(int player) {
    this->owned = player;
}

bool Tile::isFilled() {
    return this->filled != nullptr;
}

Tile::~Tile() {
    if(this->filled) {
        delete this->filled;
    }
}

Map::Map(int id, int size, std::vector<std::pair<int, int>> connections): id{id}, size{size}, tiles{new Tile*[size]}, connections{connections} {

    for(int i = 0; i < size; ++i) {
        this->tiles[i] = new Tile(i);
    }
}

Map::~Map() {
    for(int i = 0; i < size; ++i) {
        delete this->tiles[i];
    }
    delete this->tiles;
}
