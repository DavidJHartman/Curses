#include "aStar.h"
#include <unordered_set>

node::node(int h,int g)
{
    hCost=h;
    gCost=g;
}

node::node(coordinate pos, coordinate _goal, int g)
{
    position=pos;
    hCost=getDistance(position, _goal);
    gCost=g;
}
node::node(int h, int g, node* L, node* R)
{
    hCost=h;
    gCost=g;
}
struct comparator {
    bool operator() (const node item, const node n) const
    {
        int itemFcost=item.gCost+item.hCost;
        int nFcost=n.gCost+n.hCost;
        return nFcost<=itemFcost;
    }
};

std::vector<coordinate> pathFinder(std::vector<std::vector<tile*> > _map, coordinate start, coordinate goal, std::vector<coordinate> noGo)
{


    std::priority_queue<tile, std::vector<tile>, comparator> openSet;
    std::vector<tile> heapStorage;

    int distanceInNeighborset=1;

    std::vector<tile> closedSet;
    std::vector<tile*> tempNeighborStorage;

    tile currentNode(99999999,0);

    currentNode.position=start;
    currentNode.gCost=0;

    openSet.push(currentNode);
    int timesthroughLoop=0;

    while (openSet.size()!=0){

        if (currentNode.position==goal){
            std::vector<coordinate> path;
            while (!(currentNode.position==start)){

                for (int i=0;i<closedSet.size();i++){
                    if (closedSet[i].position==currentNode.parent){
                        path.push_back(currentNode.position);
                        currentNode=closedSet[i];
                        break;
                    }
                }
            }
            return path;
        }


        closedSet.push_back(currentNode);
        for (int y=-1; y<2; y++){
            for (int x=-1; x<2; x++){
                if (y==0 and x==0){
                    continue;
                }
                if (currentNode.position.x+x>=0 and currentNode.position.x+x<_map[0].size() and currentNode.position.y+y>=0 and currentNode.position.y+y<_map.size()){
                    if (_map[currentNode.position.y+y][currentNode.position.x+x]->movementCost != -1){
                        _map[currentNode.position.y+y][currentNode.position.x+x]->parent   = currentNode.position;
                        _map[currentNode.position.y+y][currentNode.position.x+x]->position = coordinate(currentNode.position.x+x,currentNode.position.y+y);
                        _map[currentNode.position.y+y][currentNode.position.x+x]->hCost    = getDistance(coordinate(currentNode.position.x+x,currentNode.position.y+y),goal);
                        _map[currentNode.position.y+y][currentNode.position.x+x]->gCost    = currentNode.gCost+10+(4*abs(y)-abs(x)+1);
                        tempNeighborStorage.push_back(_map[currentNode.position.y+y][currentNode.position.x+x]);
                    }
                }
            }
        }

        for (tile* _n : tempNeighborStorage){
                tile neighbor=*_n;
            int placeInSet=distanceInNeighborset;

            if (!vectorContains(closedSet, *_n)){


                int newCostToMove = currentNode.gCost+getDistance(currentNode.position,_n->position);
                if (newCostToMove<_n->gCost){
                    _n->gCost=newCostToMove;
                    _n->parent=currentNode.position;
                }
                if (heapStorage.size()==0 or !vectorContains(heapStorage,*_n))
                {
                    openSet.push(*_n);
                    heapStorage.push_back(*_n);
                }
            }

        }

        tempNeighborStorage.clear();
        currentNode.gCost=openSet.top().gCost;
        currentNode.hCost=openSet.top().hCost;
        currentNode.parent=openSet.top().parent;
        currentNode.position.x=openSet.top().position.x;
        currentNode.position.y=openSet.top().position.y;
        openSet.pop();
        timesthroughLoop++;
        if (canSee(_map,goal,currentNode.position)){
            std::vector<coordinate> path;
            path.push_back(currentNode.position);
            return path;
        }
    }
}

std::vector<node> getNeighbors(node Node, std::vector<std::vector<tile> > test_map, coordinate goal, int costSoFar)
{
    std::vector<node> neighbors;
    for (int x=-1;x<=1;x++){
    for (int y=-1;y<=1;y++){

            if (x==0 and y==0){
                continue;
            }

            int checkX=Node.position.x+x, checkY=Node.position.y+y;

            if (checkX>=0 and checkX<test_map[0].size() and checkY>=0 and checkY<test_map.size() and test_map[Node.position.y+y][Node.position.x+x].movementCost==0)
            {
                neighbors.push_back(node(coordinate(checkX,checkY), goal, costSoFar+getDistance(Node.position,coordinate(Node.position.x+x,Node.position.y+y))));
                neighbors[0].parent=Node.position;
            }
        }
    }

    return neighbors;
}

bool vectorContains(std::vector<tile> checkVector, tile nodeChecking)
{
    for (tile _n:checkVector)
    {
        if (_n.position.x==nodeChecking.position.x and _n.position.y==nodeChecking.position.y)
        {
            return true;
        }
    }
    return false;
}


int getDistance(coordinate nodeA, coordinate nodeB)
{
    int distX= abs(nodeA.x - nodeB.x);
    int distY= abs(nodeA.y - nodeB.y);

    if (distX > distY){
        return (14*distY + 10*(distX-distY));
    }
    else{
        return (14*distX + 10*(distY-distX));
    }

}
bool canSee(std::vector<std::vector<tile*> > test_map, coordinate checkSpot, coordinate spotToSee)
{
    int x1=spotToSee.x;
    int y1=spotToSee.y;
    int delta_x(checkSpot.x - x1);
    // if spotToSee.x == checkSpot.x, then it does not matter what we set here
    signed char const ix((delta_x > 0) - (delta_x < 0));
    delta_x = std::abs(delta_x) << 1;

    int delta_y(checkSpot.y - y1);
    // if spotToSee.y == checkSpot.y, then it does not matter what we set here
    signed char const iy((delta_y > 0) - (delta_y < 0));
    delta_y = std::abs(delta_y) << 1;

    if (delta_x >= delta_y)
    {
        // error may go below zero
        int error(delta_y - (delta_x >> 1));

        while (x1 != checkSpot.x)
        {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= delta_x;
                y1 += iy;
            }
            // else do nothing

            error += delta_y;
            x1 += ix;
            if (test_map[y1][x1]->movementCost==-1){
                return false;
            }
        }
    }
    else
    {
        // error may go below zero
        int error(delta_x - (delta_y >> 1));

        while (y1 != checkSpot.y)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= delta_y;
                x1 += ix;
            }
            // else do nothing

            error += delta_x;
            y1 += iy;
            if (test_map[y1][x1]->movementCost==-1){
                return false;
            }
        }
    }
    return true;
}
