#include "map.h"

#include <algorithm>

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

int Tile::getId() {
    return this->id;
}

int Tile::getPlayer() {
    return this->owned;
}

Phases Tile::getCard() {
    if(this->filled) {
        return this->filled->getPhase();
    }
    else {
        std::cerr << "Attempted to get card of unfilled tile" << std::endl;
        return Phases::new_moon;
    }
    
}

Tile::~Tile() {
    if(this->filled) {
        delete this->filled;
    }
}

Map::Map(int id, int size, const std::vector<std::pair<int, int>>& connections): id{id}, size{size}, tiles{new Tile*[size]}, connections{std::vector<std::vector<std::pair<int,int>>>(size)} {

    for(int i = 0; i < size; ++i) {
        this->tiles[i] = new Tile(i);
    }

    for(auto & edge: connections) {
        this->connections.at(edge.first).emplace_back(edge);
        this->connections.at(edge.second).emplace_back(std::pair<int, int>(edge.second,edge.first));
    }

}


void Map::pathCheck(Path basePath, std::vector<Path>& pathList, int direction) {
    bool added = false;
    // Check end of path for continuations
    for(auto edge: this->connections.at(basePath.getEnd())) {
        // Check for empty tiles
        if(this->tiles[edge.second]->isFilled()) {
            //Check if tile continues the chain
            if((this->tiles[edge.first]->getCard() + direction) % 8 == this->tiles[edge.second]->getCard()) {
                //Makes sure tile is not already in path (cycle) 
                if(std::find(basePath.getTiles().begin(), basePath.getTiles().end(), this->tiles[edge.second]->getId()) == basePath.getTiles().end()) {
                    // Make a copy of the path and add to it, possibility for multiple paths to be made
                    Path newPath(basePath);
                    newPath.addToEnd(this->tiles[edge.second]->getId());
                    added = true;
                    pathCheck(newPath, pathList, direction);
                }
            }
        }
        
    }

    // Check start of path for continuations, ONLY do this if no path has yet been added, ie. no connecting tile to the end forms a chain
    if(!added) {
        for(auto edge: this->connections.at(basePath.getStart())) {
            if(this->tiles[edge.second]->isFilled()) {
                //Check if tile continues the chain
                if((this->tiles[edge.first]->getCard() - direction) % 8 == this->tiles[edge.second]->getCard()) {
                    //Makes sure tile is not already in path (cycle) 
                    if(std::find(basePath.getTiles().begin(), basePath.getTiles().end(), this->tiles[edge.second]->getId()) == basePath.getTiles().end()) {
                        // Make a copy of the path and add to it, possibility for multiple paths to be made
                        Path newPath(basePath);
                        newPath.addToStart(this->tiles[edge.second]->getId());
                        added = true;
                        pathCheck(newPath, pathList, direction);
                    }
                }
            }
            
        }   
    }

    // If still no paths are added, if the path is longer than 3, add it to the list
    if(!added && basePath.getLength() >= 3) {
        pathList.emplace_back(basePath);
    }


}

int Map::checkAdjacent(int tile_id, int player_id) {
    if(this->tiles[tile_id]->isFilled()) {
        std::cerr << "Tried to check empty tile." << std::endl;
        return -1;
    }
    
    std::vector<Path> paths;
    int score = 0;

    for(auto & edge: this->connections.at(tile_id)) {
        
        if(this->tiles[edge.second]->isFilled()) {
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
            if(((this->tiles[edge.first]->getCard() + 1) % 8 == this->tiles[edge.second]->getCard()) || ((this->tiles[edge.first]->getCard() - 1) % 8 == this->tiles[edge.second]->getCard())) {
                
                // Set up initial path object
                Tile* first = this->tiles[edge.first];
                Tile* second = this->tiles[edge.second];
                int direction;
                Path initPath(first->getId(), second->getId());
                // Determine direction of chain (increasing/decreasing)
                if(first->getCard() + 1 % 8 == second->getCard()) {
                    direction = 1;
                }
                else {
                    direction = -1;
                }
                // Call recursive function that adds all valid paths created to a vector
                pathCheck(initPath, paths, direction);
                // Iterate through vector to add score equal to length of each path
                for(auto & path: paths) {
                    score += path.getLength();
                    for(auto & id: path.getTiles()) {
                        this->tiles[id]->setPlayer(player_id);
                    }
                }

            }
            
        }
        
    }

    return score;
    
}

bool Map::mapFilled() {
    for(int i = 0; i < this->size; ++i) {
        if(!this->tiles[i]->isFilled()) {
            return false;
        }
    }
    return true;
}

void Map::placeCard(int tileLoc, Card * card, int player) {
    this->tiles[tileLoc]->setCard(card, player);
}

void Map::logMap() {
    // In progress, logs the information about the map
    std::cout << "-----MAP SUMMARY-----" << std::endl;
    std::cout << "Map ID: " << this->id << std::endl;
    std::cout << "Map size: " << this->size << std::endl;
    std::cout << "Tiles:" << std::endl;
    for(int i = 0; i < this->size; ++i) {
        Tile* cur = this->tiles[i];
        std::cout << "\tTile " << cur->getId();
        if(cur->isFilled()) {
            std::cout << " (Filled)" <<std::endl;
            std::cout << "\tOwner: Player " << cur->getPlayer() << std::endl;
            std::cout << "\tCard: " << cur->getCard() << std::endl;
        }
        else {
            std::cout << " (Empty)" << std::endl;
            std::cout << "\tOwner: None" << std::endl;
        }
        std::cout << "\tConnected to tiles ";
        for(auto & edge: connections.at(cur->getId())) {
            std::cout << edge.second << " ";
        }
        std::cout << std::endl;
        
    }
    std::cout << "-----SUMMARY COMPLETE-----" << std::endl;

}

Map::~Map() {
    for(int i = 0; i < size; ++i) {
        delete this->tiles[i];
    }
    delete [] this->tiles;
}

Path::Path(int start, int end): start{start}, end{end}, tiles{std::deque<int>()} {
    tiles.emplace_front(start);
    tiles.emplace_back(end);
}

Path::Path(const Path& other): start{other.start}, end{other.end}, tiles{std::deque<int>(other.tiles)} {}

void Path::addToStart(int tile) {
    tiles.emplace_front(tile);
    start = tile;
}

void Path::addToEnd(int tile) {
    tiles.emplace_back(tile);
    end = tile;
}

int Path::getStart() {
    return this->start;
}

int Path::getEnd() {
    return this->end;
}

int Path::getLength() {
    return this->length;
}

const std::deque<int>& Path::getTiles() {
    return this->tiles;
}

Path::~Path() {}