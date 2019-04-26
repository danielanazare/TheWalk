#include "Game.h"
#include <vector>

Game::Game(int width = 15, int lenght = 15, int c = 1)
{
    harta = new Map(width, lenght);
    switch (c)
    {
    case 1 :
    {
        Robo = new Robot1;
        Robo->setc(1);
        break;
    }
    case 2:
    {
        Robo = new Robot2();
        Robo->setc(2);
        break;
    }
    case 3:
    {
        Robo = new Robot3();
        Robo->setc(3);
        break;
    }
    }
}
/*void Game::print()
{
    harta->print(Robo->getc());
}*/
void Game::walk()
{
    std::vector<int> path;
    path = harta->walk(Robo->getc());

    harta->print(Robo->getc(), path);

}



