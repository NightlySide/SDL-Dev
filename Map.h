#ifndef MAP_H
#define MAP_H

#include <vector>
#include <fstream>
#include "SDL_setup.h"

class Map
{
    public:
        Map(const char* mapFile = NULL, bool passable[TOTAL_TILE_SPRITES] = NULL);
        int* getGraph();
        bool* getPassable();
        int* loadMap(const char* mapFile);
    private:
        bool mPassable[TOTAL_TILE_SPRITES];
        int* mGraph;
};

int coordToId(int posX, int posY);
std::pair<int, int> idToCoord(int id);

#endif // MAP_H
