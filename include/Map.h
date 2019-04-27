#ifndef MAP_H
#define MAP_H
#include<vector>


struct place
{
    int x, y;
    int value; ///-1 = obstacol, 4 = Robot, 5 = final
    ///0 = liber
    ///1 = item1
    ///2 = item2
    ///3 = item3
    int taken;
};

class Map
{
    int height, width;
    place **Table;
    int pozX, pozY;
    int finalpozX, finalpozY;

public:
    Map(int, int);
    ~Map();
    void print(int c, std::vector<int> path);
    std::vector<int> walk(int c);
    bool valid(int,int);
};

#endif // MAP_H
