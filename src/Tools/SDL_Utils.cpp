#include "SDL_Utils.h"

bool utils::init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont24, TTF_Font* &gFont32, TTF_Font* &gFont48)
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
        gFont24 = TTF_OpenFont( "res/font/SourceCodePro-Regular.ttf", 24 );
        if (gFont24 == NULL)
        {
            throw TTF_GetError();
        }
        gFont32 = TTF_OpenFont( "res/font/SourceCodePro-Regular.ttf", 32 );
        if (gFont32 == NULL)
        {
            throw TTF_GetError();
        }
        gFont48 = TTF_OpenFont( "res/font/SourceCodePro-Regular.ttf", 48 );
        if (gFont48 == NULL)
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


void utils::close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont24, TTF_Font* &gFont32, TTF_Font* &gFont48)
{

    //Free global font
    TTF_CloseFont( gFont24 );
    TTF_CloseFont( gFont32 );
    TTF_CloseFont( gFont48 );
    gFont24 = NULL;
    gFont32 = NULL;
    gFont48 = NULL;

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
