#include "Main_menu.h"

Main_menu::Main_menu() {};
Main_menu::~Main_menu()
{
    //Free resources
    backgroundTexture.free();
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

void Main_menu::display(SDL_Renderer* gRenderer, GameState& gameState)
{
    ///Main menu
    backgroundTexture.loadFromFile( gRenderer, "res/img/main_menu.png" );

    ///Buttons
    Button startButton({ (SCREEN_WIDTH - 269)/ 2, 340, 269, 136 });
    startButton.loadTextures(gRenderer);

    ///Mouse position
    SDL_Point mousePos = {0, 0};
    bool mouseDown = false;
    bool mousePressed = false;


    while (gameState == MAIN_MENU)
    {
        SDL_Event event;
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );
        SDL_RenderClear( gRenderer );

        while( SDL_PollEvent( &event ) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                gameState = QUITING;
                return;
            }
            startButton.handleEvent(event, mousePos);
        }
        if (startButton.isSelected())
        {
            gameState = RUNNING_LEVEL_1;
            return;
        }
        renderBackground(gRenderer);
        startButton.renderButton(gRenderer);
        SDL_RenderPresent( gRenderer );
    }
}

