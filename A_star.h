#ifndef A_STAR_H
#define A_STAR_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include "SDL_setup.h"

using namespace std;

int getMinScore(map<int, int> openList);
bool isMultiple(int n, int ref);
vector<int> getAdjSquares(vector<int> graphList, vector<int> closeList, int currentSquare, vector<bool> passableTiles);
vector<int> pathfinding(int start, int end, int graph[TOTAL_TILES], bool isPassable[TOTAL_TILE_SPRITES]);

/*int main()
{
        0: Stone
        1: Herbe
        2: Fleur
        3: Mur
        4: Arbre
        5: Eau
        6: Toit
        7: Rock
        8: Sentier
        9: Vide


    bool isPassable[10] = {true, true, true, false, false, false, false, false, true, false};
    //no = 6,9,10
    int tileMap[Y][X] = {{0,0,0,0},
                         {0,0,3,0},
                         {0,3,3,0},
                         {0,0,0,0}
                        };
    pathfinding(2, 15, tileMap, isPassable);
    return 0;
}
*/

#endif // A_STAR_H
