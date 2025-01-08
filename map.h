#ifndef __MAP_H_INCLUDED__
#define __MAP_H_INCLUDED__


#include <cstdlib>
#include <vector>
#include <iostream>
#include <deque>

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
    int getId();
    int getPlayer();
    Phases getCard();
    ~Tile();

};

class Path {

    int start;
    int end;
    std::deque<int> tiles;
    int length;
    
public:
    Path(int start, int end);
    Path(const Path& other);
    void addToStart(int tile);
    void addToEnd(int tile);
    int getStart();
    int getEnd();
    int getLength();
    const std::deque<int>& getTiles();
    ~Path();
};

class Map {

    int id;
    int size;
    Tile** tiles;
    std::vector<std::vector<std::pair<int, int>>> connections; 

    void pathCheck(Path basePath, std::vector<Path>& pathList, int direction);

public:
    Map(int id, int size, const std::vector<std::pair<int, int>>& connections);
    int checkAdjacent(int tile_id, int player_id);
    bool mapFilled();
    void placeCard(int tileLoc, Card* card, int player);
    // Temp for debugging
    void logMap();
    ~Map();
};




#endif