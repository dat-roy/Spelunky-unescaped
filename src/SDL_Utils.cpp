#include "SDL_Utils.h"

bool utils::init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont)
{
    try
    {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        {
            throw SDL_GetError();
        }

        //Set texture filtering to linear
        if (! SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            throw SDL_GetError();
        }

        //Create window
		gWindow = SDL_CreateWindow(
                             WINDOW_TITLE.c_str(),
                             SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED,
                             SCREEN_WIDTH,
                             SCREEN_HEIGHT,
                             SDL_WINDOW_SHOWN
                             );
        if (gWindow == NULL)
        {
            throw SDL_GetError();
        }

        //Create vsynced renderer for window
        gRenderer = SDL_CreateRenderer(
                              gWindow,
                              -1,
                              SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                              );
        std::cout << gRenderer;
        if (gRenderer == NULL)
        {
            throw SDL_GetError();
        }

        //Initialize renderer color
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

        //Initialize PNG loading
        if(! IMG_Init( IMG_INIT_PNG ) )
        {
            throw IMG_GetError();
        }

        //Initialize SDL_mixer
        //44100 is a standard frequency that works on most systems
        //The second argument determines the sample format.
        //The third argument is the number of hardware channels, and here using 2 channels for stereo.
        //The last argument is the sample size, which determines the size of the chunks we use when playing sound.
        //2048 bytes (AKA 2 kilobyes) worked fine for me, but you may have to experiment with this value to minimize lag when playing sounds.
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            throw Mix_GetError();
        }

        //Initialize SDL_ttf
        if (TTF_Init() == -1)
        {
            throw TTF_GetError();
        }
        //Open the font
        gFont = TTF_OpenFont( "res/font/SourceCodePro-Regular.ttf", 24 );
        if (gFont == NULL)
        {
            throw TTF_GetError();
        }
        return true;
    }
    catch (const char* &error)
    {
        std::cerr << "In utils::init(): " << error << std::endl;
        return false;
    }
}


void utils::close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont)
{

    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;

	//Destroy window, renderer
	SDL_DestroyWindow( gWindow );
	SDL_DestroyRenderer( gRenderer );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();
	SDL_Quit();
}
