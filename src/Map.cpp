#include "Map.h"

Map::Map() {};
Map::~Map()
{
    //Free resources
    gBgTexture.free();
    text_01.free();
    text_02.free();
}

void Map::loadTextures(SDL_Renderer* &gRenderer, TTF_Font* &gFont24, TTF_Font* &gFont32, TTF_Font* &gFont48)
{
    gBgTexture.loadFromFile( gRenderer, "res/img/bg1.jpg" );                 //Load background
    //Render text
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    text_01.loadFromRenderedText( gRenderer,
                                      " ",
                                      gFont32, textColor);
    text_02.loadFromRenderedText( gRenderer,
                                      "Use SPACE to modify initial velocity [0..100]",
                                      gFont24, textColor);
}

LTexture Map::getText_01()
{
    return text_01;
}

LTexture Map::getText_02()
{
    return text_02;
}

void Map::renderBackground(SDL_Renderer* &gRenderer, int x, int y)
{
    gBgTexture.render(gRenderer, x, y);
}

void Map::renderText_01(SDL_Renderer* &gRenderer, int x, int y)
{
    text_01.render(gRenderer, x, y);
}
void Map::renderText_02(SDL_Renderer* &gRenderer, int x, int y)
{
    text_02.render(gRenderer, x, y);
}
