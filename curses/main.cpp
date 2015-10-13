#include <iostream>
#include "include/curses.h"
#include "include/dungeon.h"
#include <cstdlib>

using namespace std;

class tile
{
public:
    bool corner;
    char occupychar;
    char defaultchar;
    int movementCost;
    tile(char,char,int);
    tile(){corner=false;};
};

class player
{
public:
    int x,y;
    char symbol;
    void movement(vector<vector<tile> >,char);
    player();
};

player::player()
{
    x=3;
    y=3;
    symbol='@';
}

tile::tile(char oc,char dc, int mc)
{
    occupychar=oc;
    defaultchar=dc;
    movementCost=mc;
}

void player::movement(vector<vector<tile> > map_, char ch)
{

    if (ch=='w')
    {
        if (map_[y-1][x].movementCost!=-1)
        {
            y--;
        }
    }
    if (ch=='s')
    {
        if (map_[y+1][x].movementCost!=-1)
        {
            y++;
        }
    }
    if (ch=='a')
    {
        if (map_[y][x-1].movementCost!=-1)
        {
            x--;
        }
    }
    if (ch=='d')
    {
        if (map_[y][x+1].movementCost!=-1)
        {
            x++;
        }
    }
}

class coord
{
public:
    int x,y;
    coord(int x_,int y_){x=x_;y=y_;};
    coord(){};
};

int main()
{
    coord direction[4]={coord(0,-1),coord(1,0),coord(0,+1),coord(-1,0)};
    bool inventory=false;
    std::vector< std::vector<bool> > map_t=dungeon().dungeon_grid;
    std::vector<std::vector<tile> > map_;
    map_.resize(map_t.size());
    player test;
    for (int y=0;y<map_t.size();y++)
    {
        map_[y].resize(map_t[0].size());
        for (int x=0;x<map_t[0].size();x++)
        {
            if (map_t[y][x]==1)
            {
                map_[y][x]=tile('.','.',0);
                test.x=x;
                test.y=y;
            }
            else
            {
                map_[y][x]=tile('#','#',-1);
            }
        }
    }
    map_[6][9]=tile('+','+',0);
    WINDOW* gameView;
    gameView=initscr();
    WINDOW* inv = newwin(15,20,4,2);
    resize_term(50,100);
    keypad(gameView,true);
    noecho();
    cbreak();
    curs_set(0);
    int ch;
    int chpos=0;
    while (ch!='p')
    {
        test.movement(map_, ch);
        if (ch=='i' and inventory==false)
        {
            ch=0;
            wborder(inv,0,0,0,0,0,0,0,0);
            touchwin(inv);
            wrefresh(inv);
            inventory=true;
            while (ch!='i')
            {
                mvwaddstr(inv,1,1,"menu");
                wrefresh(inv);
                ch=getch();
            }
            delwin(inv);
            touchwin(gameView);
            wrefresh(gameView);
            inventory=false;
        }
        for (int y=test.y-12;y<test.y+12;y++)
        {
            for (int x=test.x-12;x<test.x+12;x++)
            {
                if (y-test.y==0 and x-test.x==0)
                {
                    mvaddch(y-test.y+12,x-test.x+12,test.symbol);
                }
                else
                {
                    mvaddch(y-test.y+12,x-test.x+12, map_[y][x].defaultchar);
                }
            }
        }
        ch=getch();
        refresh();
    }
    endwin();
}