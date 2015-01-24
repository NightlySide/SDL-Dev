#include "A_star.h"

int getMinScore(map<int, int> openList)
{
    int min = 100000;
    int index = 0;
    for(map<int,int>::iterator it = openList.begin(); it != openList.end(); ++it)
        if(openList.at(it->first)<=min)
        {
            min = openList.at(it->first);
            index = it->first;
        }
    return index;
}

bool isMultiple(int n, int ref) {return n%ref==0;}

vector<int> getAdjSquares(vector<int> graphList, vector<int> closeList, int currentSquare, vector<bool> passableTiles)
{
    vector<int> adj_squares;
    try{
        if(find(passableTiles.begin(), passableTiles.end(), graphList.at(currentSquare+1))!=passableTiles.end() && !isMultiple(currentSquare+1, MAP_TILE_WIDTH))
            adj_squares.push_back(currentSquare+1);
    }catch(const exception & e){}
    try{
        if(find(passableTiles.begin(), passableTiles.end(), graphList.at(currentSquare-1))!=passableTiles.end() && !isMultiple(currentSquare, MAP_TILE_WIDTH))
            adj_squares.push_back(currentSquare-1);
    }catch(const exception & e){}
    try{
        if(find(passableTiles.begin(), passableTiles.end(), graphList.at(currentSquare+MAP_TILE_WIDTH))!=passableTiles.end() /*&& (unsigned)graphList.at(currentSquare)<graphList.size()-X*/)
            adj_squares.push_back(currentSquare+MAP_TILE_WIDTH);
    }catch(const exception & e){}
    try{
        if(find(passableTiles.begin(), passableTiles.end(), graphList.at(currentSquare-MAP_TILE_WIDTH))!=passableTiles.end() /*&& graphList.at(currentSquare)>X*/)
            adj_squares.push_back(currentSquare-MAP_TILE_WIDTH);
    }catch(const exception & e){}
    return adj_squares;
}

vector<int> pathfinding(int start, int end, int graph[TOTAL_TILES], bool isPassable[TOTAL_TILE_SPRITES])
{
    map<int, int> openList;
    vector<int> graphList;
    vector<int> closeList;
    vector<bool> passables;
    map<int, int> previous;

    for (int y = 0; y<TOTAL_TILES; y++)
            graphList.push_back(graph[y]);

    for (int x = 0; x<TOTAL_TILES; x++)
    {
        int value = graph[x];
        if(isPassable[value] == true)
        {
            passables.push_back(x);
        }
    }

    openList.insert(make_pair(start, 10));

    do {
        int currentSquare = getMinScore(openList);
        int score = openList.find(currentSquare)->second;
        /*printf("Current: %d | Score: %d\n", currentSquare, score);
        system("PAUSE");*/

        closeList.push_back(currentSquare);
        openList.erase(currentSquare);

        if(find(closeList.begin(), closeList.end(), end)!=closeList.end())
            break;

        vector<int> adjacent_squares = getAdjSquares(graphList, closeList, currentSquare, passables);

        for(int i = 0; (unsigned)i<adjacent_squares.size(); i++)
        {
            if(find(closeList.begin(), closeList.end(), adjacent_squares.at(i))!=closeList.end())
                continue;

            try{
                openList.find(adjacent_squares.at(i));
                openList.insert(make_pair(adjacent_squares.at(i), score+1));
                previous.insert(make_pair(adjacent_squares.at(i), currentSquare));
            }catch(const exception & e){
                openList.erase(adjacent_squares.at(i));
                closeList.push_back(adjacent_squares.at(i));
            }
        }
    }while(openList.size()>=0);

    int parent = previous.find(end)->second;
    vector<int> parents;
    do{
        parents.push_back(parent);
        parent = previous.find(parent)->second;
    }while(parent!=start);
    reverse(parents.begin(), parents.end());

    return parents;
}
