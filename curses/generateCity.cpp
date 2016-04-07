#include "generateCity.h"
#include <vector>
#include "drawGame.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <random>

void box::makeHouse(std::vector<std::vector<std::vector<tile*> > > & tileMap, std::mt19937 & generator,std::vector<actor*> &actors)
{
    std::uniform_int_distribution<int> halfChance(0,1);
    std::uniform_int_distribution<int> doorFinder((bottom-1)+(left+1),(top+1)+(right-1));
    int half=halfChance(generator);
    int doorPlace=doorFinder(generator);

    int wallTex;
    int innerwallTex;
    int floorTex;
    int mc;
    std::string wallmat;
    std::string innerwallmat;
    std::string floormat;

    int type = -1; //1 = blacksmith
                   //2 = house
                   //3 = store
                   //4 = armorer

    int width = abs(right-left), height = abs(bottom-top);

    if (width < 5 or height < 5)return;

    else if (width < 15 and height > 10 and height <15){
        wallTex = stonewall;
        floorTex = stonefloor;
        wallmat = "stone";
        floormat = "stone";
        innerwallTex = stonewall;
        innerwallmat = "stone";
        type = 1;
    }
    else if (width<15 and height < 15){
        wallTex = woodwall;
        floorTex = woodfloor;
        wallmat = "wood";
        floormat = "wood";
        innerwallTex = woodwall;
        innerwallmat = "wood";
        type = 2;
    }
    else if (width < 20 and height < 20){
        wallTex = stonewall;
        floorTex = woodfloor;
        wallmat = "stone";
        floormat = "wood";
        innerwallTex = woodwall;
        innerwallmat = "wood";
        type = 3;
    }
    else if (height < 15 and width > 10 and width <15){
        wallTex = stonewall;
        floorTex = stonefloor;
        wallmat = "stone";
        floormat = "stone";
        innerwallTex = stonewall;
        innerwallmat = "stone";
        type = 4;
    }
    else return;

    bool emptyPlot = false;


    for(int a=left; a<=right; a++)
    {
        for(int b=bottom; b<=top; b++)
        {
                tileMap[0][b][a]= new tile(floorTex,0,floormat);

                switch(type){
                case 1:
                    if (rand()%501 < 10){
                        actors.push_back(new monster("human"));
                        actors[actors.size()-1]->pos(b,a);
                    }
                    if (rand()%201 < 5){
                        tileMap[1][b][a]= new furniture(woodchair,0,"wood");
                        tileMap[1][b][a]->position=coordinate(a,b);
                    }
                    if (rand()%501< 50){
                        tileMap[1][b][a] = new container(chest,-1,"wood");
                    }
                case 2:
                    if (rand()%4000 < 50){
                        tileMap[1][b][a] = new furniture(bed,0,"redEye");
                    }
                }
            if (emptyPlot);
            else if(b==bottom or a==right)
            {
                if(b+a==doorPlace and half==0)
                {
                    tileMap[1][b][a]=new door(false,closeddoor,0,"wood");
                }
                else
                {
                    tileMap[1][b][a]=new tile(wallTex,-1,wallmat);
                }

                tileMap[1][b][a]->position = coordinate(a,b);
            }

            else if(a==left or b==top)
            {
                if(b+a==doorPlace and half==1)
                {
                    tileMap[1][b][a]=new door(false,closeddoor,0,"wood");
                }
                else
                {
                    tileMap[1][b][a]=new tile(wallTex,-1,wallmat);
                }
                tileMap[1][b][a]->position = coordinate(a,b);
            }
            tileMap[0][b][a]->position = coordinate(a,b);

        }
    }
    top--;
    bottom++;
    left++;
    right--;
    if (!emptyPlot)divideBox(3,tileMap,"HOUSE", generator,actors);


}

void city:: setTileMap()
{
    tileMap.resize(2);
    tileMap[0].resize(tileMapSize);
    tileMap[1].resize(tileMapSize);
  for(int a=0; a<tileMapSize; a++)
    {
        tileMap[0][a].resize(tileMapSize);
        tileMap[1][a].resize(tileMapSize);
        for(int b=0; b<tileMapSize; b++)
        {
            tileMap[0][a][b]=new tile(grass,10,"grass");
            tileMap[0][a][b]->position = coordinate(b,a);
            tileMap[0][a][b]->isDoor = false;
            tileMap[1][a][b]=new tile;
            tileMap[1][a][b]->position = coordinate(b,a);
            tileMap[1][a][b]->isDoor = false;
        }
    }
}


void city:: deleteTileMap()
{
    for(int a=0; a<tileMap.size(); a++)
    {
        for(int b=0; b<tileMap.size(); b++)
        {
            delete tileMap[0][a][b];
            delete tileMap[1][a][b];
        }
    }
}

void box::makeLine(road* myLine, std::vector<std::vector<std::vector<tile*> > > & tileMap, int width, std::string type, std::mt19937 & generator)
{
    int a=0;
    int b=0;

    int dc;
    int mc;
    std::string mat;

    int doorPlace;

    if(type=="HOUSE")
    {
        dc=woodwall;
        mc=-1;
        mat="wood";

        if(myLine->vertical)
        {
            a=myLine->Point1->y;
            b=myLine->Point2->y;

        }
        else
        {
            a=myLine->Point1->x;
            b=myLine->Point2->x;
        }

        std::uniform_int_distribution<int> doorFinder(a,b);
        doorPlace=doorFinder(generator);
    }

    if(type=="ROADBOX")
    {
        dc = dirt;
        mc=10;
        mat="dirt";
    }

    if(myLine->vertical==true)
    {
        signed int q1=myLine->Point1->x-(width)/2;
        signed int q2=myLine->Point1->x+(width)/2;


        if(0<=q1 and q2<tileMap[0].size())
        {
            for(int c=myLine->Point1->y; c<=myLine->Point2->y; c++)
            {
                if(0<=c and c<tileMap[0].size())
                {
                    for(int d=q1; d<=q2; d++)
                {
                    if(type=="HOUSE")
                    {
                        if (doorPlace == c) tileMap[1][c][d] = new door(false,closeddoor,0,mat);

                        else tileMap[1][c][d]=new tile(dc,-1,mat);

                        tileMap[1][c][d]->position = coordinate(d,c);
                    }
                    else if (type=="ROADBOX")
                    {
                            tileMap[0][c][d]=new tile(dc,mc,mat);
                            tileMap[0][c][d]->position = coordinate(d,c);
                    }
                }
                }

            }
        }
    }

    else //horizontal
    {
        signed int q1=myLine->Point1->y-(width)/2;
        signed int q2=myLine->Point1->y+(width)/2;

        if(0<=q1 and q2<tileMap[0].size())
        {
            for(int c=myLine->Point1->x; c<=myLine->Point2->x; c++)
            {
                for(int d=q1; d<=q2; d++)
                {
                    if(type=="HOUSE")
                    {
                        if (doorPlace == c)tileMap[1][d][c] = new door(false,closeddoor,0,mat);

                        else tileMap[1][d][c]=new tile(dc,-1,mat);

                        tileMap[1][d][c]->position = coordinate(c,d);
                    }

                    else if (type=="ROADBOX")
                    {
//                        if(d==q1 or d==q2)
//                        {
//                            tileMap[0][d][c]=new tile(grass,0,"grass");
//                        }
                            tileMap[0][d][c]=new tile(dc,mc,mat);

                        tileMap[0][d][c]->position = coordinate(c,d);
                    }
                }
            }
        }
    }
}


void box::divideBox(int level, std::vector<std::vector<std::vector<tile*> > > & tileMap, std::string type, std::mt19937 & generator,std::vector<actor*> &actors)
{
 if(level>0)
 {
std::uniform_int_distribution<int> halfChance(0,1);
    int half = halfChance(generator);
    int width;
    if(type=="ROADBOX")
    {

        width=3;
    }
    if(type=="HOUSE")
    {
        width=1;
    }

    if(half==0 and right-left>width+6) //if line vertical and there is space to draw line
    {//std::cout<<"Half0"<<std::endl;
        std::uniform_int_distribution<int> findSplitPoint(left+width/2+3, right-width/2-3);
        int splitPoint=findSplitPoint(generator);

        coordinate lowPoint(splitPoint, bottom);
        coordinate highPoint(splitPoint, top);

        road tempRoad;
        tempRoad.vertical=true;
        tempRoad.Point1=&lowPoint;
        tempRoad.Point2=&highPoint;

        makeLine(&tempRoad, tileMap, width, type, generator); //draws road on tile map

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=splitPoint-width/2-1;
        subBox1->top=top;
        subBox1->bottom=bottom;

        subBox2->left=splitPoint+width/2+1;
        subBox2->right=right;
        subBox2->top=top;
        subBox2->bottom=bottom;

        subBox1->divideBox(level-1, tileMap, type, generator,actors);
        subBox2->divideBox(level-1, tileMap, type, generator,actors);
    }

    else if(half==0)
    {
        divideBox(level-1, tileMap, type, generator,actors);
    }

    else if (half==1 and top-bottom>width+6)
    {//line horizontal
        //std::cout<<"Half2"<<std::endl;
        std::uniform_int_distribution<int> findSplitPoint(bottom+(width)/2+3,top-(width)/2-3);
        int splitPoint=findSplitPoint(generator);
        coordinate leftPoint(left, splitPoint);
        coordinate rightPoint(right, splitPoint);
        road tempRoad;
        tempRoad.vertical=false;
        tempRoad.Point1=&leftPoint;
        tempRoad.Point2=&rightPoint;


        makeLine(&tempRoad, tileMap, width, type, generator); //draws road on tileMap

        subBox1=new box;
        subBox2=new box;

        subBox1->left=left;
        subBox1->right=right;
        subBox1->top=top-1;
        subBox1->bottom=splitPoint+width/2+1;
        subBox2->left=left;
        subBox2->right=right;
        subBox2->top=splitPoint-width/2-1;
        subBox2->bottom=bottom+1;  //forms 2 new boxes
        subBox1->divideBox(level-1, tileMap, type, generator,actors);
        subBox2->divideBox(level-1, tileMap, type, generator,actors);
    }
    else if(half==1)
    {
        divideBox(level-1, tileMap, type, generator,actors);
    }
 }

 else if(level==0 and type=="ROADBOX")
{
   makeHouse(tileMap, generator,actors);
     //many houses
}

 }

  void city::generateCity(std::vector<actor*> &actors)
{
setTileMap();
divideBox(8,tileMap, "ROADBOX", generator,actors); //recursive box dividing and road drawing
}



box::~box()
{

}

