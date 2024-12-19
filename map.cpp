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

Phases Tile::getCard() {
    return this->filled->getPhase();
}

Tile::~Tile() {
    if(this->filled) {
        delete this->filled;
    }
}

Map::Map(int id, int size, std::vector<std::pair<int, int>> connections): id{id}, size{size}, tiles{new Tile*[size]}, connections{std::vector<std::vector<std::pair<int,int>>>(size)} {

    for(int i = 0; i < size; ++i) {
        this->tiles[i] = new Tile(i);
    }

    for(auto & edge: connections) {
        this->connections.at(edge.first).emplace_back(edge);
        this->connections.at(edge.second).emplace_back(edge);
    }

}

int Map::checkAdjacent(int tile_id, int player_id) {
    if(this->tiles[tile_id] == nullptr) {
        std::cerr << "Tried to check empty tile." << std::endl;
        return -1;
    }
    
    int score = 0;

    for(auto & edge: connections.at(tile_id)) {
        
        if(this->tiles[edge.second] != nullptr) {
            // Check for pair tiles
            if(this->tiles[edge.first]->getCard() == this->tiles[edge.second]->getCard()) {
                this->tiles[edge.first]->setPlayer(player_id);
                this->tiles[edge.second]->setPlayer(player_id);
                score += 1;
            }
            // Check for matching tiles
            if(std::abs(this->tiles[edge.first]->getCard() - this->tiles[edge.second]->getCard()) == 4) {
                this->tiles[edge.first]->setPlayer(player_id);
                this->tiles[edge.second]->setPlayer(player_id);
                score += 2;
            }

            // Check for chains
            // TODO
        }
        

        

    }

    return score;
    
    
}

Map::~Map() {
    for(int i = 0; i < size; ++i) {
        delete this->tiles[i];
    }
    delete [] this->tiles;
}
