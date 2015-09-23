#include <iostream>
#include <random>
#include <time.h>
#include "aStar.h"


using namespace std;

int main()
{

    std::default_random_engine engine(time(NULL));
    std::uniform_int_distribution<int> distributor(1,10);
    bool test_map[20][20];
    for (int i=0;i<20;i++)
    {
        for (int j=0;j<20;j++)
        {
            int temp=distributor(engine);
            if (temp<=2)
            {
                test_map[i][j]=1;
            }
            else
            {
                test_map[i][j]=0;
            }
            std::cout << test_map[i][j];
        }
        std::cout << endl;
    }
}