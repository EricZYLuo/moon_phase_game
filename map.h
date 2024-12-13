#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__


#include <cstdlib>
#include <vector>
#include <iostream>

#include "card.h"

class Tile {

    int id;
    Card* filled;
    int owned;

public:
    Tile(int id);
    void setCard(Card* card, int player);
    void setPlayer(int player);
    bool isFilled();
    ~Tile();

};

class Map {

    int id;
    int size;
    Tile** tiles;
    std::vector<std::pair<int, int>> connections; 

public:
    Map(int id, int size, std::vector<std::pair<int, int>> connections);
    ~Map();
};



#endif