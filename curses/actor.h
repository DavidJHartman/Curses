#ifndef ACTOR_H_INCLUDED
#define ACTOR_H_INCLUDED
#include "aStar.h"
#include "window.h"
#include <stdlib.h>
#include <time.h>
#include <cctype>
#include <fstream>
#include "bodyParts.h"

class actor
{
protected:
    char _symbol;


    int x,y;
public:
    std::string species;
    std::string description;
    std::string name;
    std::vector<item*> inventory;
    std::vector<item*> equipment;
    std::vector<bodyPart*> body;
    item* wielded;
// WHETHER OR NOT TO DOUBLE MOVEMENT SPEED
    bool sprinting;

//  RETURN COORDINATES
    int row(){return y;}
    int col(){return x;}

//  BASIC STATS OF EVERY CREATURE
    int attack;
    int totalWeight;
    int accuracy;
    int defense;
    int counter;
    int speed(){return totalWeight-attack;};
    int customSpeed;
    std::string skinColor;

//  TAGS FOR AI
    bool EVIL;

//  WHETHER CREATURE IS UNDER PLAYER CONTROL
    bool controlled;
    bool hidden;


// VECTORS FOR PATHFINDING
    std::vector<coordinate> noGo;//represents places you absolutely should not step
    std::vector<coordinate> badPosition;//represents places that might go to noGo or not, basically temporary storage

//  RETURN THE SYMBOL OF THE CREATURE
    char symbol(){return _symbol;}

//  SET THE POSITION OF THE CREATURE
    void pos(int _y,int _x){x=_x;y=_y;}

//  METHODS FOR INTERACTING WITH COUNTERS
    int getCounter(){return counter;}// obviously returns counter position
    int getSpeed(){return speed()-(.5*speed())*sprinting;}//returns maximum speed of a creature (if counter == speed, execute turn)


//  METHODS FOR COMBAT
    void dodgeAttack(actor* enemyDodgingFrom, std::vector<std::vector<tile*> >*_map);
    void attackEnemy(actor* enemyAttacking, std::vector<std::vector<tile*> >* _map);
    void makeCorpse(std::vector<item*> *globalItems, std::vector<item*> *localItems);


//  VIRTUAL METHODS TO BE OVERRIDDEN BY CHILD CLASSES (DO NOT PUT PURE VIRTUAL METHODS IN HERE)
/*
strictly for the polymorphic attributes of C++. These allow us to place
monsters and players in a vector of actor pointers. To place a creature
in the actor class, you must use the dynamic memory function "new" like
so:
   std::vector<actor*> actors.push_back(new monster(int, char);
do not forget to "delete" every pointer at the end of the program.
*/
    virtual void movement(std::vector<std::vector<tile*> >* _map,std::vector<item*> *localItems,std::vector<actor*> actors, screen *scr){}
    virtual void setPost(int x, int y){}
    virtual void examineGround(screen* scr, std::vector<item*> *itemsExamining, coordinate spotExamining){}
    virtual void openInventory(screen* scr,std::vector<item*> *localItems){}
    virtual void moveOnPath(std::vector<std::vector<tile*> >){}
};

class player: public actor
{
public:
    void movement(std::vector<std::vector<tile*> >* _map,std::vector<item*> *localItems, std::vector<actor*> actors, screen *scr);
    void examineGround(screen* scr, std::vector<item*> *itemsExamining, coordinate spotExamining);
    void openInventory(screen* scr,std::vector<item*> *localItems);
    player(std::string speciesToLoad);
};

class monster: public actor
{
    coordinate post;
public:
    coordinate memory;
    std::vector<coordinate> path;
    monster(std::string);
    bool musttouch;
    bool canSee(std::vector<std::vector<tile*> >, coordinate);
    void movement(std::vector<std::vector<tile*> >* _map,std::vector<item*> *localItems, std::vector<actor*> actors, screen *scr);
    void setPost(int x, int y){post=coordinate(x,y);}
    void getPath(std::vector<std::vector<tile*> > _map,coordinate goal, std::vector<coordinate> noGo){path.clear();path=pathFinder(_map,coordinate(x,y),goal,noGo);}
    void moveOnPath(std::vector<std::vector<tile*> >);
};


#endif // ACTOR_H_INCLUDED
