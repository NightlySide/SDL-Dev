#include "entity.h"

Entity::Entity(const char* textureFile)
{
    ENTITY_WIDTH = 20;
    ENTITY_HEIGHT = 20;

    mPosX = 0;
    mPosY = 0;

    mBox.x = TILE_WIDTH/2-ENTITY_WIDTH/2;
    mBox.y = TILE_HEIGHT/2-ENTITY_HEIGHT/2;
	mBox.w = ENTITY_WIDTH;
	mBox.h = ENTITY_HEIGHT;

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
        setPosition(mPath.front());
        mPath.erase(mPath.front());
    }
}

void Entity::setGoal(std::pair<int, int> pos)
{
    mGoal = pos;
    //insert A* algorithm var into mPath vector table
}

void Entity::setGoal(int posX, int posY)
{
    mGoal = std::make_pair(posX, posY);
    //insert A* algorithm var into mPath vector table
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
