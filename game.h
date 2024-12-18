#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__


#include <vector>

#include "map.h"
#include "card.h"

class Game {
    int id;
    Map* game_board;
    Deck* deck;
};

#endif