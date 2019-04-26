#include <iostream>
#include <graphics.h>
#include "Map.h"
#include "Game.h"

using namespace std;

int main()
{
    int x, l, w;
    cout << "Welcome to TheWalk Game" << endl;
    cout << "Choose your Robot (1/2/3)" << endl;
    cin >> x;
    cout << "Choose the size of the map (Length, Width)" << endl;
    cin >> l >> w;
    Game *NewGame;
    NewGame = new Game(w, l, x);

    NewGame->walk();
    //NewGame->print();

    return 0;
}
