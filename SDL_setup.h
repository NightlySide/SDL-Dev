#ifndef SDL_SETUP_H_INCLUDED
#define SDL_SETUP_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

class Texture
{
	public:
		Texture();
		~Texture();

		bool loadFromFile( std::string path );
		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		void free();
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
		void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha );
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};

class Tile
{
    public:
		Tile( int x, int y, int tileType );
		void render( SDL_Rect& camera );
		int getType();
		SDL_Rect getBox();

    private:
        //SDLSetup mSdlsetup;
		SDL_Rect mBox;
		int mType;
};

class Dot
{
    public:
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;
		Dot(SDL_Rect camera);
		void handleEvent( SDL_Event& e );
		void move( Tile *tiles[] );
		void setCamera( SDL_Rect& camera );
		void render( SDL_Rect& camera );
		void moveToCell(std::pair<int,int> coords);

    private:
		SDL_Rect mBox;
		SDL_Rect mCamera;
		int mVelX, mVelY;
};

//Dimension du .map
const int MAP_TILE_WIDTH = 16;
const int MAP_TILE_HEIGHT = 12;

//Tile constants
const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;
const int TOTAL_TILES = MAP_TILE_WIDTH*MAP_TILE_HEIGHT;
const int TOTAL_TILE_SPRITES = 6;

//The dimensions of the level
const int LEVEL_WIDTH = TILE_WIDTH*MAP_TILE_WIDTH;
const int LEVEL_HEIGHT = TILE_HEIGHT*MAP_TILE_HEIGHT;

//Screen dimension constants
const int SCREEN_WIDTH = 10*TILE_WIDTH;
const int SCREEN_HEIGHT = 8*TILE_HEIGHT;

//Col et lignes du tileset
const int TILESET_LINES = 2;
const int TILESET_COLUMNS = 3;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern Texture gDotTexture;
extern Texture gTileTexture;
extern SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

bool checkCollision( SDL_Rect a, SDL_Rect b );
bool init();
void close( Tile* tiles[] );
bool touchesWall( SDL_Rect box, Tile* tiles[] );
bool setTiles( Tile *tiles[], const char* mapFile );
bool loadMedia( Tile* tiles[], const char* tileSetFile, const char* mapFile );
std::pair<int,int> getClickedCell(SDL_Rect& camera, int mouseX, int mouseY);

#endif // SDL_SETUP_H_INCLUDED
