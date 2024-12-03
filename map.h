#include <cstdlib>
#include <vector>
#include <iostream>

#include "card.h"

class Map {

    int id;
    int size;
    Tile* tiles;
    std::vector<std::pair<int, int>> connections; 

};

class Tile {

    int id;
    Card* filled;
    int owned;

};
