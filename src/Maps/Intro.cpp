#include "Intro.h"

Intro::Intro() {};
Intro::~Intro() {};

void Intro::display(SDL_Renderer* gRenderer, GameState& gameState, TTF_Font* gFont24, TTF_Font* gFont32, TTF_Font* gFont48)
{
    SDL_Event event;

    while (gameState == INTRO)
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
                if (event.key.keysym.sym == SDLK_s) {
                    gameState = RUNNING_LEVEL_1;
                }
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
        SDL_RenderClear(gRenderer);
        Texture text;
        std::string content = "";
        SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
        content = "--- INTRO ---";
        text.loadFromRenderedText( gRenderer, content, gFont32, textColor);
        text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 200);

        content = "You are a ninja from Spelunky world.";
        text.loadFromRenderedText( gRenderer, content, gFont32, textColor);
        text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 280);

        content = "One day you got lost in a strange land.";
        text.loadFromRenderedText( gRenderer, content, gFont32, textColor);
        text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 360);

        content = "How can you survive and come home? It all depends on you.";
        text.loadFromRenderedText( gRenderer, content, gFont32, textColor);
        text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 420);

        content = "PRESS KEY S TO START.";
        text.loadFromRenderedText( gRenderer, content, gFont32, textColor);
        text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 500);

        SDL_RenderPresent(gRenderer);
    }
}
