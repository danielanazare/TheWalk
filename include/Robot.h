#ifndef ROBOT_H
#define ROBOT_H
#include <iostream>

class Robot
{
    int color;
public:
    void setc(int c);
    int getc();
    virtual void f() = 0;


};

class Robot1: public Robot
{
public:
    void f()
    {
        std::cout << "Robot1";
    }

};
class Robot2: public Robot
{
public:
    void f()
    {
        std::cout << "Robt2";
    }

};
class Robot3: public Robot
{
public:
    void f()
    {
        std::cout << "Robot3";
    }

};

#endif // ROBOT_H
