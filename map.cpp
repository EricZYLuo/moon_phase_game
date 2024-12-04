#include "map.h"

Map::Map(int id, int size, std::vector<std::pair<int, int>> connections): id{id}, size{size}, tiles{new Tile*[size]}, connections{connections} {

    for(int i = 0; i < size; ++i) {
        tiles[i] = new Tile(i);
    }
}

Tile::Tile(int id): id{id}, filled{nullptr}, owned{0} {}
