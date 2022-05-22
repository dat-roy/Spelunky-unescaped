#include "Outro.h"

Outro::Outro() {};
Outro::~Outro() {};

void Outro::display(SDL_Renderer* gRenderer, GameState& gameState, TTF_Font* gFont24, TTF_Font* gFont32, TTF_Font* gFont48)
{
     SDL_Event event;

    while (gameState == WINNING)
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
                    gameState = MAIN_MENU;
                }
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0);
        SDL_RenderClear(gRenderer);
        Texture text;
        std::string content = "";
        SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
        content = "You win";
        text.loadFromRenderedText( gRenderer, content, gFont32, textColor);
        text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 150);

        content = "You may wonder what is inside in that box, right?";
        text.loadFromRenderedText( gRenderer, content, gFont32, textColor);
        text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 200);

        SDL_RenderPresent(gRenderer);
    }
}
