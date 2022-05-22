#include "Tile.h"

Tile::Tile(int x, int y, int type)
{
    box = {x, y, TILE_WIDTH, TILE_HEIGHT};
    this->type = type;
}

int Tile::getType()
{
    return type;
}

SDL_Rect Tile::getBox()
{
    return box;
}

bool checkCollision(SDL_Rect& camera, SDL_Rect& box)
{

}


void Tile::render(SDL_Rect& camera)
{
    //If the tile is on screen
    /*if (checkCollision(camera, box))
    {
        //Show the tile
        tileTexture.render(box.x - camera.x, box.y - camera.y, tileClips[type]);
    }*/
}


