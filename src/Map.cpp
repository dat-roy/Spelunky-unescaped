#include "Map.h"

Map::Map() {};
Map::~Map()
{
    //Free resources
    backgroundTexture.free();
}

void Map::setBackgroundPath(std::string path)
{
    backgroundPath = path;
}

void Map::setTilesetPath(std::string path)
{
    tilesetPath = path;
}

void Map::loadTextures(SDL_Renderer* gRenderer, TTF_Font* &gFont24, TTF_Font* &gFont32, TTF_Font* &gFont48)
{
    backgroundTexture.loadFromFile( gRenderer, backgroundPath );
    //Tile textures and clips
    tileTexture.loadFromFile(gRenderer, tilesetPath);
    tileClips.push_back({0, 0, 0, 0});
    for (int row = 0; row < TILE_COUNT; row++)
    {
        for (int col = 0; col < TILE_COUNT; col++)
        {
            tileClips.push_back( {col * TILE_WIDTH, row * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT} );
        }
    }
}

void Map::loadTiles(SDL_Renderer* gRenderer, std::string path)
{
    std::ifstream file(path);
    file >> TILE_ROW >> TILE_COL;

    //Tile values
    std::vector<int> temp;
    temp.assign(TILE_COL + 2, -1);
    tileValue.push_back(temp);
    for (int row = 1; row <= TILE_ROW; row++)
    {
        temp.assign(0, 0);
        temp.push_back(-1);
        for (int col = 1; col <= TILE_COL; col++)
        {
            int value;
            file >> value;
            temp.push_back(value);
        }
        temp.push_back(-1);
        tileValue.push_back(temp);
    }
    temp.assign(TILE_COL + 2, -1);
    tileValue.push_back(temp);

    //Tile Border values
    temp.assign(TILE_COL + 2, -1);
    tileBorderValue.push_back(temp);
    for (int row = 1; row <= TILE_ROW; row++)
    {
        temp.assign(0, 0);
        temp.push_back(-1);
        for (int col = 1; col <= TILE_COL; col++)
        {
            int value;
            file >> value;
            temp.push_back(value);
        }
        temp.push_back(-1);
        tileBorderValue.push_back(temp);
    }
    temp.assign(TILE_COL + 2, -1);
    tileBorderValue.push_back(temp);
}

void Map::renderBackground(SDL_Renderer* gRenderer, int x, int y)
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

void Map::renderTiles(SDL_Renderer* gRenderer, int x, int y)
{
    for (int i = 1; i <= TILE_ROW; i++)
    {
        for (int j = 1; j <= TILE_COL; j++)
        {
            int value = tileValue[i][j];
            SDL_RendererFlip flipType = SDL_FLIP_NONE;
            if (value < 0 || value > TILE_COL * TILE_ROW) continue;
            tileTexture.render(gRenderer, (j-1) * TILE_WIDTH, (i-1) * TILE_HEIGHT, &tileClips[value], NULL, NULL, flipType);
        }
    }
}

void Map::renderBorder(SDL_Renderer* gRenderer)
{
    for (int i = 1; i <= TILE_ROW; i++)
    {
        for (int j = 1; j <= TILE_COL; j++)
        {
            int value = tileBorderValue[i][j];
            int epsilon_x = 0;
            int epsilon_y = 0;
            SDL_RendererFlip flipType = SDL_FLIP_NONE;
            if (value < 0 || value > TILE_COL * TILE_ROW) continue;

            if (value == 13 || value == 14)
            {
                //if (tileValue[i+1][j] == 8) {
                epsilon_y = 28;
                flipType = SDL_FLIP_VERTICAL;
            }
            if (value == 15)
            {
                epsilon_y = -28;
            }
            if (value == 6)
            {
                epsilon_y = -28;
            }
            if (value == 24)
            {
                epsilon_x = 28;
            }
            if (value == 16)
            {
                epsilon_x = -28;
            }
            tileTexture.render(gRenderer, (j-1) * TILE_WIDTH + epsilon_x, (i-1) * TILE_HEIGHT + epsilon_y, &tileClips[value], NULL, NULL, flipType);
        }
    }
}
