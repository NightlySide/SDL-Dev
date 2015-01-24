//Using SDL, SDL_image, standard IO, strings, and file streams
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "SDL_setup.h"
#include "entity.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
Texture gDotTexture;
Texture gTileTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];

int main( int argc, char* args[] )
{
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		Tile* tileSet[ TOTAL_TILES ];
		if( !loadMedia( tileSet, "tileset.png", "main.map" ) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
            bool quit = false;
            SDL_Event e;
            SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
            Dot dot = Dot(camera);
            dot.moveToCell(std::make_pair(1,1));

            bool isPassable[TOTAL_TILE_SPRITES] = {false, true, false, false, false, false};

            Entity second = Entity("dot.bmp", camera, isPassable);
            second.setPosition(2, 3);
            //second.setGoal(9,12);

            while(!quit)
            {
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    dot.handleEvent( e );
                    second.handleEvent(e);
                }

                dot.move( tileSet, isPassable);
                dot.setCamera( camera );

                second.followPath();

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                //Render Everything
                for( int i = 0; i < TOTAL_TILES; ++i )
                {
                    tileSet[ i ]->render( camera );
                }
                dot.render( camera );
                second.render(camera);
                SDL_RenderPresent( gRenderer );

                //To have 50 FPS
                SDL_Delay( 1000 / 50 );
            }

		}
		close( tileSet );
	}
	return 0;
}
