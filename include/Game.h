#ifndef GAME_H
#define GAME_H
#include "Map.h"
#include "Robot.h"
#include <vector>

class Game
{
    Map *gameMap;
    Robot *Robo;

public:
    Game(int, int, int);
    //void print();
    void walk();
};

#endif // GAME_H
