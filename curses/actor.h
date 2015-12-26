#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include "aStar.h"

class actor
{
protected:
    char _symbol;


    int x,y;
public:
    bool sprinting;
    int row(){return y;}
    int col(){return x;}
    int health;
    int attack;
    int defense;
    int counter;
    int speed;

    bool controlled;
    bool hidden;

    std::vector<coordinate> noGo;
    std::vector<coordinate> badPosition;


    char symbol(){return _symbol;}
    void pos(int _y,int _x){x=_x;y=_y;}

    int getCounter(){return counter;}
    int getSpeed(){return speed-(.5*speed)*sprinting;}

    virtual void movement(std::vector<std::vector<tile> >*, char*){}
    virtual void aiMovement(std::vector<std::vector<tile> >, coordinate, std::vector<actor*>){}
};

class player : public actor
{
public:
    void movement(std::vector<std::vector<tile> >*, char*);
    player();
    int raiseCounter(){counter++;}
};

class monster : public actor
{
    coordinate post;
public:
    coordinate memory;
    std::vector<coordinate> path;
    bool musttouch;
    void aiMovement(std::vector<std::vector<tile> >, coordinate, std::vector<actor*>);
    bool canSee(std::vector<std::vector<tile> >, coordinate);
    monster(int,char);
    void setPost(int x, int y){post=coordinate(x,y);}
    void getPath(std::vector<std::vector<tile> > _map,coordinate goal, std::vector<coordinate> noGo){path=pathFinder(_map,coordinate(x,y),goal,noGo);}
    void moveOnPath(std::vector<std::vector<tile> >);
};

#endif // ACTOR_H_INCLUDED
