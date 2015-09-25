#include "aStar.h"
#include <unordered_set>
coordinate::coordinate(int x_t, int y_t)
{
    x=x_t;
    y=y_t;
}

coordinate::coordinate()
{
    x=0;
    y=0;
}

node::node()
{
}

node::node(coordinate current, coordinate goal, int costSoFar)
{
    gCost=10+costSoFar;
    hCost=heuristic(current, goal);
    position=current;
}

std::vector<coordinate> pathFinder(bool test_map[20][20], coordinate start, coordinate goal)
{
    int costSoFar=0;
    int lowestF_Cost=99999999;

    node currentNode;
    node neighbor;
    node temp;

    std::vector<node> openNodes;    //set to be evaluated
    std::vector<node> closedNodes;  //set already evaluated
    std::vector<coordinate> foundPath;
    std::vector<node> neighbors;

    openNodes.push_back(node(start,goal,0)); //initialize open set
    while (openNodes.size()!=0)
    {
        std::cout << "\n==========================================\n";
        for (int i=0;i<20;i++)
    {
        for (int j=0;j<20;j++)
        {
            bool nice=false;
            for (int k=0;k<foundPath.size();k++)
            {
                //std::cout << foundPath[k].x << "," <<foundPath[k].y << std::endl;
                if (foundPath[k].x==i&&foundPath[k].y==j)
                {
                    nice=true;
                }
            }
            if (nice==false)
            {
                if (test_map[i][j]==true)
                {
                    std::cout << "#";
                }
                else
                {
                    std::cout << ".";
                }
                nice=false;
            }
            else
            {
                std::cout << "p";
            }
        }
        std::cout << std::endl;
    }
        //=============SET CURRENT NODE=================
        currentNode = openNodes[0];
        for (int i=0;i<openNodes.size();i++){
            //std::cout << openNodes[i].position.x << "," << openNodes[i].position.y << std::endl;
            if (openNodes[i].fCost()<currentNode.fCost())
            {
                lowestF_Cost=currentNode.fCost();
                currentNode=openNodes[i];
                foundPath.push_back(currentNode.position);
            }
            else if (openNodes[i].fCost()==currentNode.fCost() && openNodes[i].hCost<currentNode.hCost and openNodes[i].fCost()<lowestF_Cost)
            {
                lowestF_Cost=currentNode.fCost();
                currentNode=openNodes[i];
            }
        }
        //==============================================

        for (int i=0;i<openNodes.size();i++)
        {
            if (openNodes[i].position.x==currentNode.position.x&&openNodes[i].position.y==currentNode.position.y)
            {
                closedNodes.push_back(currentNode);
                //std::cout << closedNodes[i].parent.x << "," << closedNodes[i].parent.y << std::endl;
                openNodes.erase(openNodes.begin()+i);
            }
        }
        if (currentNode.position.x == goal.x and currentNode.position.y == goal.y)
        {
            for (int i=0;i<closedNodes.size();i++)
            {
                foundPath.push_back(closedNodes[i].parent);
            }
            return foundPath;
        }
        //==============================================

        neighbors=getNeighbors(currentNode,test_map,goal,currentNode.gCost);
        for (int i=0;i<neighbors.size();i++)
        {
            neighbor=neighbors[i];
            for (int j=0;j<closedNodes.size();j++)
            {
                if (test_map[neighbors[i].position.y][neighbors[i].position.x]==0 and closedNodes[j].position.x!=neighbors[i].position.x and closedNodes[j].position.y!=neighbors[i].position.y)
                {
                    int newGCost = currentNode.gCost + getDistance(currentNode, neighbors[i]);
//                    if (openNodes.size()==0)
//                    {
//                        neighbors[i].gCost = newGCost;
//                        neighbors[i].hCost = heuristic(neighbor.position, goal)/*getDistance(neighbors[i], node(goal,goal,0))*/;
//                        neighbors[i].parent=currentNode.position;
//                        //std::cout << "Neighbor hcost: " << neighbors[i].hCost << std::endl;
//                        openNodes.push_back(neighbors[i]);
//                        //std::cout << currentNode.position.x << " , " << currentNode.position.y << std::endl;
//                    }
                    //std::cout << openNodes.size() << std::endl;
                    bool yougood=true;
                    for (int k=0;k<openNodes.size();k++)
                    {
                        if (openNodes[k].position.x==neighbors[i].position.x and openNodes[k].position.y==neighbors[i].position.y)
                        {

                        //std::cout << openNodes[k].position.x << "," << openNodes[k].position.y << std::endl;
                        //std::cout << neighbors[i].position.x << "," << neighbors[i].position.y << std::endl;
                            //std::cout << k << std::endl;
                            yougood=false;
                            break;
                        }
                    }
                    if (yougood==true)
                    {
                        if (newGCost<neighbors[i].gCost)
                        {
                            neighbors[i].gCost = newGCost;
                            neighbors[i].hCost = heuristic(neighbor.position, goal);
                            neighbor=neighbors[i];
                            std::cout << "Here\n";
                        }
                        neighbors[i].parent=currentNode.position;
                        openNodes.push_back(neighbors[i]);
                    }
                }
            }
        }


    }
}

float heuristic(coordinate current, coordinate goal)
{
    return abs(current.x-goal.x)+abs(current.y-current.y);
}

std::vector<node> getNeighbors(node Node, bool test_map[][20], coordinate goal, int costSoFar)
{
    std::vector<node> neighbors;
    for (int x=-1;x<=1;x++){
        for (int y=-1;y<=1;y++){
            if (x==0 and y==0){
                continue;
            }
            int checkX=Node.position.x+x, checkY=Node.position.y+y;
            if (checkX>=0 and checkX<20 and checkY>=0 and checkY<20 and test_map[Node.position.x+x][Node.position.y+y]==0)
            {
                neighbors.push_back(node(coordinate(checkX,checkY), goal, costSoFar));
                neighbors[0].parent=Node.position;
            }
        }
    }

    return neighbors;
}

int getDistance(node nodeA, node nodeB)
{
    int distX= abs(nodeA.position.x - nodeB.position.x);
    int distY= abs(nodeA.position.y - nodeB.position.y);

    if (distX > distY){
            //std::cout << 14*distY + 10*(distX-distY) << std::endl;
        return 14*distY + 10*(distX-distY);
    }
    else{
        //std::cout << 14*distY + 10*(distY-distX) << std::endl;
        return 14*distY + 10*(distY-distX);
    }

}
