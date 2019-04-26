#include "Map.h"
#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>
#define HEADER_X 30
#define HEADER_Y 30
#define SQUARE 40

///constuctor cu sau fara parametri - construieste harta
Map::Map(int h = 15, int w = 15)

{
    height = h;
    width = w;
    pozX = 0;
    pozY = 0;

    Table = new place*[height];
    for(int i = 0; i< height; i++)
    {
        Table[i] = new place[width];
        for(int j = 0; j < width; j++)
        {
            Table[i][j].x = HEADER_X + j*SQUARE;
            Table[i][j].y = HEADER_Y + i*SQUARE;
            Table[i][j].value = 0;
            Table[i][j].taken = 0;
        }
    }
    ///Set Robot start position
    pozX = 0;
    pozY = 0;
    Table[pozX][pozY].value = 4;

    ///Set final pozition, different from start
    srand(time(NULL));
    finalpozX = rand() % (height - 1) + 1;
    finalpozY = rand() % (width - 1) + 1;
    Table[finalpozX][finalpozY].value = 5; /// 5 = final

    ///Place items and obstacles
    int itemno = width * height /16;
    int k, x, y;
    for(int i = 1; i <= 3; i++)
    {
        k = 0;
        while(k < itemno)
        {
            x = rand() % height;
            y = rand() % width;
            if(Table[x][y].value == 0)
            {
                Table[x][y].value = i;
                k++;
            }
        }
    }
    ///Obstacles
    k = 0;
    while(k < itemno)
    {
        x = rand() % height;
        y = rand() % width;
        if(Table[x][y].value == 0)
        {
            Table[x][y].value = -1;
            k++;
        }
    }
}

void Map::print(int c, std::vector<int> path)
{
    initwindow(SQUARE * height + 2 * HEADER_X, SQUARE * width + 2 * HEADER_Y);
    /*int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");*/

    ///Se afiseaza harta initiala

    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            setcolor(15);
            rectangle(Table[i][j].x, Table[i][j].y, Table[i][j].x + SQUARE, Table[i][j].y + SQUARE);

            if(Table[i][j].value == -1)
                setfillstyle(1, 4);
            else if(Table[i][j].value == 1)
                setfillstyle(1, 1);
            else if(Table[i][j].value == 2)
                setfillstyle(1, 2);
            else if(Table[i][j].value == 3)
                setfillstyle(1, 3);
            else if(Table[i][j].value == 4)
                {setfillstyle(1, c);///Robo->getcolor()
                //setcolor(3);
                circle(Table[i][j].x + SQUARE/2, Table[i][j].y + SQUARE/2, SQUARE/2);
                }
            else if(Table[i][j].value == 5)
                setfillstyle(1, 7);
            else
                setfillstyle(1, 0);

            floodfill(Table[i][j].x + SQUARE/2, Table[i][j].y + SQUARE/2, 15);

        }
    ///getch();
    //closegraph();
    delay(100);

    ///Afisam traseul generat

    int x, y;

    for(unsigned int i = 0; i <+ path.size(); i = i+2)
    {
        x = path[i];
        y = path[i+1];

        setfillstyle(1, 0);
        floodfill(Table[x][y].x + SQUARE/2, Table[x][y].y + SQUARE/2 ,15);

        circle(Table[x][y].x + SQUARE/2, Table[x][y].y + SQUARE/2, SQUARE/2);
        setfillstyle(1, c);
        floodfill(Table[x][y].x + SQUARE/2, Table[x][y].y + SQUARE/2 ,15);

        delay(1000);

    }

    setbkcolor(0);
    clearviewport();
    settextstyle(5, 0, 5);
    outtext("End of game\n");

   /// delay(1000);
   getch();
   closegraph();


}

Map::~Map()
{
    for(int i = 0; i < height; i++)
        delete []Table[i];
    delete []Table;
}


bool Map::valid(int x, int y)
{
    if((x >= 0) && (x < height) && (y >=0) && (y < width) && (Table[x][y].taken == 0) && (Table[x][y].value != -1))
        return true;
    else
        return false;
  ///  return (x >= 0) && (x < height) && (y >=0) && (y < width) && (Table[x][y].taken == 0) && (Table[x][y].value != 4);
}
std::vector<int> Map::walk(int c)
{
    int row[] = {-1, 0, 1, 0};
    int col[] = {0, 1, 0, -1};

    std::vector<int> X, Y, I, A, P; ///X= linia, Y = coloana, I = index, A = anterior, P = points(nr of items colected)
    X.push_back(pozX);
    Y.push_back(pozY);
    I.push_back(0);
    A.push_back(-1);
    P.push_back(0);
    Table[pozX][pozY].taken = 1;

    int x, y, xx, yy;
    int j = -1, k = 0, finali;
    while(j < k)
    {
        j++;
        x = X[j];
        y = Y[j];

        for(int i = 0; i < 4; i++)
        {
            xx = x + row[i];
            yy = y + col[i];
            if(valid(xx, yy) == true)
            {
                k++;

                if(xx == finalpozX && yy == finalpozY)
                    finali = k;

                X.push_back(xx);
                Y.push_back(yy);
                I.push_back(I.back() + 1);
                A.push_back(j);
                if(Table[xx][yy].value == c)//harta->getvalue(xx, yy)
                    P.push_back(P[j] + 1);
                else
                    P.push_back(P[j]);
                Table[xx][yy].taken = 1;
            }
        }
    }

    std::vector<int> path;
    do
    {
        path.insert(path.begin(), Y[finali]);
        path.insert(path.begin(), X[finali]);
        finali = A[finali];
    }
    while(A[finali] != -1);

    return path;

}

