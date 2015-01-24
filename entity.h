#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <vector>
#include <SDL2/SDL.h>
#include "SDL_setup.h"
#include "A_star.h"
#include "Map.h"

class Entity
{
    public:
        Entity(const char* textureFile, SDL_Rect& camera, bool isPassable[TOTAL_TILE_SPRITES]);
        ~Entity();
        void setPosition(std::pair<int, int> pos);
        void setPosition(int posX, int posY);
        std::pair<int, int> getPosition();
        void followPath();
        bool setGoal(std::pair<int, int> pos);
        bool setGoal(int posX, int posY);
        bool loadTexture(const char* textureFile);
        void render(SDL_Rect& camera);
        void handleEvent(SDL_Event& e);
    protected:
    private:
        int ENTITY_WIDTH;
        int ENTITY_HEIGHT;
        int mPosX;
        int mPosY;
        std::vector<int> mPath;
        std::pair<int, int> mGoal;
        SDL_Rect mBox;
        SDL_Rect mCamera;
        Texture mEntityTexture;
        Map mMap;
};

#endif // ENTITY_H
