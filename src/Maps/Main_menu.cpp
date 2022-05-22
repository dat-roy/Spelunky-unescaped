#include "Main_menu.h"

Main_menu::Main_menu() {};
Main_menu::~Main_menu()
{
    //Free resources
    backgroundTexture.free();
}

void Main_menu::loadTextures(SDL_Renderer* gRenderer)
{
    backgroundTexture.loadFromFile( gRenderer, "res/img/main_menu.png" );                 //Load background
}

void Main_menu::renderBackground(SDL_Renderer* gRenderer, int x, int y)
{
    if (x == 0 && y == 0)
    {
        backgroundTexture.render(gRenderer, (SCREEN_WIDTH - backgroundTexture.getWidth()) / 2, (SCREEN_HEIGHT - backgroundTexture.getHeight()) / 2);
    }
    else
    {
        backgroundTexture.render(gRenderer, x, y);
    }

}
