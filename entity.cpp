#include "entity.h"

Entity::Entity(const char* textureFile, SDL_Rect& camera, bool isPassable[TOTAL_TILE_SPRITES])
{
    ENTITY_WIDTH = 20;
    ENTITY_HEIGHT = 20;

    mPosX = 0;
    mPosY = 0;

    mBox.x = TILE_WIDTH/2-ENTITY_WIDTH/2;
    mBox.y = TILE_HEIGHT/2-ENTITY_HEIGHT/2;
	mBox.w = ENTITY_WIDTH;
	mBox.h = ENTITY_HEIGHT;

	mMap = Map("main.map", isPassable);
	mCamera = camera;

	loadTexture(textureFile);
}

Entity::~Entity()
{
    //dtor
}

void Entity::setPosition(std::pair<int, int> pos)
{
    mPosX = pos.first;
    mPosY = pos.second;
    mBox.x = mPosX*TILE_WIDTH+(TILE_WIDTH/2-ENTITY_WIDTH/2);
    mBox.y = mPosY*TILE_HEIGHT+(TILE_HEIGHT/2-ENTITY_HEIGHT/2);
}

void Entity::setPosition(int posX, int posY)
{
    mPosX = posX;
    mPosY = posY;
    mBox.x = mPosX*TILE_WIDTH+(TILE_WIDTH/2-ENTITY_WIDTH/2);
    mBox.y = mPosY*TILE_HEIGHT+(TILE_HEIGHT/2-ENTITY_HEIGHT/2);
}

std::pair<int, int> Entity::getPosition()
{
    return std::make_pair(mPosX, mPosY);
}

void Entity::followPath()
{
    if(mPath.size()>0)
    {
        setPosition(idToCoord(mPath.front()));
        mPath.erase(mPath.begin());
    }
}

bool Entity::setGoal(std::pair<int, int> pos)
{
    mGoal = pos;
    mPath.clear();
    printf("Start %d | End %d\n", coordToId(mPosX, mPosY), coordToId(mGoal.first,mGoal.second));
    bool* passable = mMap.getPassable();
    int* graph = mMap.getGraph();
    if(&passable[graph[coordToId(mGoal.first,mGoal.second)]])
    {
        mPath = pathfinding(coordToId(mPosX, mPosY), coordToId(mGoal.first,mGoal.second), graph, passable);
        mPath.push_back(coordToId(mGoal.first,mGoal.second));
        return true;
    }
    else{
        printf("You shall not pass...");
        return false;
    }
}

bool Entity::setGoal(int posX, int posY)
{
    mGoal = std::make_pair(posX, posY);
    mPath.clear();
    printf("Start %d | End %d\n", coordToId(mPosX, mPosY), coordToId(mGoal.first,mGoal.second));
    bool* passable = mMap.getPassable();
    int* graph = mMap.getGraph();
    if(&passable[graph[coordToId(mGoal.first,mGoal.second)]])
    {
        mPath = pathfinding(coordToId(mPosX, mPosY), coordToId(mGoal.first,mGoal.second), graph, passable);
        mPath.push_back(coordToId(mGoal.first,mGoal.second));
        return true;
    }
    else{
        printf("You shall not pass...");
        return false;
    }
}

void Entity::render(SDL_Rect& camera)
{
    mEntityTexture.render( mBox.x - camera.x, mBox.y - camera.y );
}

bool Entity::loadTexture(const char* textureFile)
{
    bool success = true;
    if( !mEntityTexture.loadFromFile( textureFile ) )
	{
		printf( "Failed to load entity texture: %s\n", textureFile);
		success = false;
	}
	return success;
}

void Entity::handleEvent(SDL_Event& e)
{
    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        std::pair<int,int> coords = getClickedCell(mCamera, e.button.x, e.button.y);
        setGoal(coords.first, coords.second);
    }
}
