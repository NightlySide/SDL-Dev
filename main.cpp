//Using SDL, SDL_image, standard IO, strings, and file streams
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "SDL_setup.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture gDotTexture;
Texture gTileTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//The level tiles
		Tile* tileSet[ TOTAL_TILES ];

		//Load media
		if( !loadMedia( tileSet, "tileset.png", "main.map" ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			mainLoop(tileSet);
		}

		//Free resources and close SDL
		close( tileSet );
	}

	return 0;
}
