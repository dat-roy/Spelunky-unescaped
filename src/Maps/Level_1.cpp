#include "Level_1.h"

Level_1::Level_1()
{
}
Level_1::~Level_1()
{
}

void Level_1::display(SDL_Renderer* gRenderer, GameState& gameState, TTF_Font* gFont24, TTF_Font* gFont32, TTF_Font* gFont48)
{
    ///Characters
    Character character({100, 64 * 2 + 117}, true);
    character.loadTextures(gRenderer);

    ///Enemies
    std::vector<Snake> snakes(5);
    snakes[0].setFirstPosition({600, 64 * 2 + 95 - 5}, true);
    snakes[1].setFirstPosition({700, 64 * 2 + 95 - 5}, true);
    snakes[2].setFirstPosition({800, 64 * 2 + 95 - 5}, true);
    snakes[3].setFirstPosition({900, 64 * 2 + 95 - 5}, true);
    snakes[4].setFirstPosition({1000, 64 * 2 + 95 - 5}, true);
    for (auto &snake : snakes)
    {
        snake.loadTextures(gRenderer, "res/sprites/enemy/snake.png");
    }

    ///Level 1
    Map level_1;
    level_1.setBackgroundPath("res/img/bg10.jpg");
    level_1.setTilesetPath("res/map/tileset_1.png");
    level_1.loadTextures(gRenderer);
    level_1.loadTiles(gRenderer, "res/map/tileset_1.map");

    while (gameState == RUNNING_LEVEL_1)
    {
        SDL_Event event;
        while( SDL_PollEvent( &event ) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                gameState = QUITING;
                break;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_a) {
                    gameState = MAIN_MENU;
                }
            }
            character.handleEvent(event);
        }

        level_1.renderBackground(gRenderer);
        level_1.renderTiles(gRenderer);
        level_1.renderBorder(gRenderer);

        Texture text;
        std::string content = "";
        content = "Ninja in Jungle";
        text.loadFromRenderedText( gRenderer, content, gFont32, { 0xFF, 0xFF, 0xFF });
        text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 150);

        character.controlAction(level_1.tileValue, level_1.TILE_ROW, level_1.TILE_COL, gameState);
        character.renderAction(gRenderer);

        for (auto &snake : snakes)
        {
            snake.renderAction(gRenderer);
            if (snake.meet({character.getPos().x, character.getPos().y, character.getWidth() - 50, character.getHeight() - 50}))
            {
                character.action = DYING;
            }
        }

        SDL_RenderPresent(gRenderer);
    }
}

