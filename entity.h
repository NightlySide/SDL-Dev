#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include "SDL_setup.h"

class Entity
{
    public:
        Entity(const char* textureFile);
        ~Entity();
        void setPosition(std::pair<int, int> pos);
        void setPosition(int posX, int posY);
        std::pair<int, int> getPosition();
        void followPath();
        void setGoal(std::pair<int, int> pos);
        void setGoal(int posX, int posY);
        bool loadTexture(const char* textureFile);
        void render(SDL_Rect& camera);
    protected:
    private:
        int ENTITY_WIDTH;
        int ENTITY_HEIGHT;
        int mPosX;
        int mPosY;
        std::vector< std::pair<int, int> > mPath;
        std::pair<int, int> mGoal;
        SDL_Rect mBox;
        Texture mEntityTexture;
};

#endif // ENTITY_H
