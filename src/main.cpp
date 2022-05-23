#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

#include "Global.h"
#include "Tools/SDL_Utils.h"
#include "Maps/Main_menu.h"
#include "Maps/Level_1.h"
#include "Maps/Level_2.h"
#include "Maps/Intro.h"
#include "Maps/Outro.h"
#include "Maps/GameOver.h"

//SDL utilities
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont24 = NULL;
TTF_Font *gFont32 = NULL;
TTF_Font *gFont48 = NULL;

//Init game state
GameState gameState = MAIN_MENU;

void displayLevel_2();
void displayWinning();
void displayBomb();

int main( int argc, char* args[] )
{
    if( !utils::init(gWindow, gRenderer, gFont24, gFont32, gFont48) )
    {
        std::cerr << "In main(): Failed to initialize initTools!\n";
        return 0;
    }

    Main_menu mainMenu;
    Intro intro;
    Level_1 mapLevel_1;
    Level_2 mapLevel_2;
    Outro outro;
    GameOver gameOver;
    while( gameState != QUITING)
    {
        switch (gameState)
        {
        case MAIN_MENU:
            mainMenu.display(gRenderer, gameState);
            break;
        case INTRO:
            intro.display(gRenderer, gameState, gFont24, gFont32, gFont48);
            break;
        case RUNNING_LEVEL_1:
            mapLevel_1.display(gRenderer, gameState, gFont24, gFont32, gFont48);
            break;
        case RUNNING_LEVEL_2:
            mapLevel_2.display(gRenderer, gameState, gFont24, gFont32, gFont48);
            break;
        case WINNING:
            outro.display(gRenderer, gameState, gFont24, gFont32, gFont48);
            break;
        case GAMEOVER:
            gameOver.display(gRenderer, gameState, gFont24, gFont32, gFont48);
            break;
        }
    }
    utils::close(gWindow, gRenderer, gFont24, gFont32, gFont48);
    return 0;
}
