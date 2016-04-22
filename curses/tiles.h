#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED
#include <vector>
#include "tile.h"
#include "actor.h"
#include "include/dungeon.h"
#include <noise/noise.h>
#include "noiseutils.h"

class tiles
    {
        public:
        std::vector<std::vector<tile*> > tileMap;
        int height;
        int width;
        tiles();

        void fillMap();
        void setPositions();
        void makeTileMap();
    };

void fillInDungeon(std::vector<std::vector<std::vector<tile*>>> &_map)
{
    dungeon Dungeon;
    _map.resize(2);
    for (int i = 0; i < _map.size(); i++){
        _map[i].resize(Dungeon.h);
        for (int j = 0; j < _map[i].size(); j++){
            _map[i][j].resize(Dungeon.w);
        }
    }
    int numberOfEnemies = 0;
    for (int y = 0; y < Dungeon.h; y++){
        for (int x = 0; x < Dungeon.w; x++){
            if (Dungeon.dungeon_grid[y][x] == true){
                _map[0][y][x] = new  tile(stonefloor,0,"stone",x,y);
                _map[0][y][x]->position = coordinate(x,y);
                _map[1][y][x] = new  tile;
                _map[1][y][x]->position = coordinate(x,y);
            }
            else{
                _map[0][y][x] = new  tile(stonefloor,0,"stone",x,y);
                _map[0][y][x]->position = coordinate(x,y);
                _map[1][y][x] = new  tile(stonewall,-1,"stone",x,y);
                _map[1][y][x]->position = coordinate(x,y);
            }

        }
    }
    for (int y = 0; y < 2000; y++){
        for (int x = 0; x < 2000; x++){
            if (rand()%1000 == 1 and _map[1][y][x]->movementCost != -1){
                    if (rand()%2==0)_map[1][y][x]->occupied = new monster("bat");
                    else _map[1][y][x]->occupied = new monster("snake");
                }
                else if (rand()%300 == 1 and _map[1][y][x]->movementCost != -1){
                    std::cout << "Time4soc\n";
                    _map[1][y][x] = new socialTile(opendoor,0,"wood");
                    for (int yy = y-6;yy<y+6;yy++){
                        for (int xx = x-6;xx<x+6;xx++){
                            if (yy == y and xx == x or yy < 0  or xx < 0 or yy >=2000 or xx >=2000 or _map[1][yy][xx]->movementCost != -1)continue;

                            _map[1][yy][xx] = new tile;
                            if (rand()%6 == 1){
                                    if (_map[1][yy][xx] != NULL)continue;
                                    _map[1][yy][xx]->occupied = new monster("goblin");
                                    _map[1][yy][xx]->occupied->pos(yy,xx);
                                    numberOfEnemies++;
                                    std::cout << numberOfEnemies << std::endl;
                            }
                            else if (rand()%10 == 1){
                                    if (_map[1][yy][xx] != NULL)continue;
                                    _map[1][yy][xx]->occupied = new monster("orc");
                                    _map[1][yy][xx]->occupied->pos(yy,xx);
                                    numberOfEnemies++;
                                    std::cout << numberOfEnemies << std::endl;
                            }
                        }
                    }
                }
        }
    }
    std::cout << "Number of sentient enemies: " << numberOfEnemies << std::endl;
    std::cout << "Done w dungeon\n";
    return;
}


#endif //TILES_H_INCLUDE
