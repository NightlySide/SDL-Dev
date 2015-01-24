#include "Map.h"

Map::Map(const char* mapFile, bool passable[TOTAL_TILE_SPRITES])
{
    if(mapFile!=NULL)
    {
        mGraph = loadMap(mapFile);
        *mPassable = *passable;
    }
}

int* Map::getGraph()
{
    return mGraph;
}
bool* Map::getPassable()
{
    return mPassable;
}


int* Map::loadMap(const char* mapFile)
{
    std::ifstream map( mapFile );

    int* graph = new int[TOTAL_TILES];

    if( map == NULL )
    {
		printf( "Unable to load map file!\n" );
    }
	else
	{
		for( int i = 0; i < TOTAL_TILES; ++i )
		{
			int tileType = -1;
			map >> tileType;
			if( map.fail() )
			{
				printf( "Error loading map: Unexpected end of file!\n" );
				break;
			}

			if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
			{
			    graph[i] = tileType;
			}
			else
			{
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				break;
			}
		}
	}
	return graph;
}

int coordToId(int posX, int posY)
{
    int graph2[MAP_TILE_HEIGHT][MAP_TILE_WIDTH];
    for(int h = 0; h<MAP_TILE_HEIGHT; h++)
    {
        for(int w = 0; w<MAP_TILE_WIDTH; w++)
        {
            graph2[h][w] = w+h*MAP_TILE_WIDTH;
        }
    }
    return graph2[posY][posX];
}

std::pair<int, int> idToCoord(int id)
{
    std::pair<int, int> coords;
    for(int h = 0; h<MAP_TILE_HEIGHT; h++)
    {
        for(int w = 0; w<MAP_TILE_WIDTH; w++)
        {
            if( id == w+h*MAP_TILE_WIDTH)
                coords = std::make_pair(w, h);
        }
    }
    return coords;
}
