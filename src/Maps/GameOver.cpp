#include "GameOver.h"

GameOver::GameOver() {};
GameOver::~GameOver() {};

void GameOver::display(SDL_Renderer* gRenderer, GameState& gameState, TTF_Font* gFont24, TTF_Font* gFont32, TTF_Font* gFont48)
{
    SDL_Event event;

    while (gameState == GAMEOVER)
    {
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
                    gameState = RUNNING_LEVEL_1;
                }
                if (event.key.keysym.sym == SDLK_q) {
                    gameState = QUITING;
                }
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
        SDL_RenderClear(gRenderer);
        Texture text;
        std::string content = "";
        SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
        content = "--- Oops! You died! ---";
        text.loadFromRenderedText( gRenderer, content, gFont32, textColor);
        text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 200);

        content = "PRESS KEY A TO PLAY AGAIN.";
        text.loadFromRenderedText( gRenderer, content, gFont32, textColor);
        text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 280);

        content = "PRESS KEY Q TO QUIT.";
        text.loadFromRenderedText( gRenderer, content, gFont32, textColor);
        text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 360);

        SDL_RenderPresent(gRenderer);
    }
}

