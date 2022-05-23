#ifndef MAP__H_
#define MAP__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>

#include "../Global.h"
#include "../Tools/Texture.h"
#include "../Maps/Tile.h"


class Map
{
    //Graphics path
    std::string backgroundPath;
    std::string tilesetPath;

    //Graphics textures
    Texture backgroundTexture;
    Texture tileTexture;

public:
    int TILE_ROW, TILE_COL;
    std::vector<std::vector<int>> tileValue;                //Value of tiles read from matrix
    std::vector<std::vector<int>> tileBorderValue;          //Value of border tiles read from matrix
    std::vector<SDL_Rect> tileClips;                        //Clips of 64 tiles, indexed from 1..64

    Map();
    ~Map();
    void setBackgroundPath(std::string path);
    void setTilesetPath(std::string path);

    void loadTextures(SDL_Renderer* gRenderer);
    void loadTiles(SDL_Renderer* gRenderer, std::string path);

    void renderBackground(SDL_Renderer* gRenderer, int x = 0, int y = 0);
    void renderTiles(SDL_Renderer* gRenderer, SDL_Rect camera);
    void renderBorder(SDL_Renderer* gRenderer, SDL_Rect camera);
};

#endif // MAP__H_
