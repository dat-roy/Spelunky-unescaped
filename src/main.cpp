#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>

#include "Global.h"
#include "SDL_Utils.h"
#include "Texture.h"
#include "Map.h"
#include "Bomb.h"
#include "Character.h"
#include "Enemy.h"
#include "Button.h"
#include "Maps/Main_menu.h"

//SDL utilities
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont24 = NULL;
TTF_Font *gFont32 = NULL;
TTF_Font *gFont48 = NULL;

//Init game state
GameState gameState = MAIN_MENU;

//Mouse position
SDL_Point mousePos = {0, 0};
bool mouseDown = false;
bool mousePressed = false;

//Maps
Main_menu main_menu;
Map level_1;
Map level_2;

//Start button
Button startButton({ (SCREEN_WIDTH - 269)/ 2, 340, 269, 136 });
//Characters
Character character({100, 64 * 2 + 117}, true);
//Weapons
Bomb bomb(character.getPos(), 0, 0, 100);
//Enemies
std::vector<Enemy*> snakes;


void loadAllTextures()
{
    ///Main menu
    main_menu.loadTextures(gRenderer);

    ///Buttons
    startButton.loadTextures(gRenderer);

    ///Level 1
    level_1.setBackgroundPath("res/img/bg10.jpg");
    level_1.setTilesetPath("res/map/tileset_1.png");
    level_1.loadTextures(gRenderer, gFont24, gFont32, gFont48);
    level_1.loadTiles(gRenderer, "res/map/tileset_1.map");

    for (int i = 0; i < 3; i++)
    {
        snakes.push_back(new Enemy);
    }
    snakes[0]->setFirstPosition({500, 64 * 2 + 95 - 5}, true);
    snakes[1]->setFirstPosition({600, 64 * 2 + 95 - 5}, false);
    snakes[2]->setFirstPosition({700, 64 * 2 + 95 - 5}, true);
    for (auto &snake : snakes)
    {
        snake->loadTextures(gRenderer);
    }

    ///Level 2
    level_2.setBackgroundPath("res/img/bg9.jpg");
    level_2.setTilesetPath("res/map/tileset_2.png");
    level_2.loadTextures(gRenderer, gFont24, gFont32, gFont48);
    level_2.loadTiles(gRenderer, "res/map/tileset_2.map");


    ///Characters & weapons
    character.loadTextures(gRenderer);
    bomb.loadTextures(gRenderer);
}

void displayMainMenu();
void displayLevel_1();
void displayLevel_2();
void displayWinning();
void displayBomb();

int main( int argc, char* args[] )
{
    if( !utils::init(gWindow, gRenderer, gFont24, gFont32, gFont48) )
    {
        std::cerr << "In main(): Failed to initialize initTools!\n";
        return 0;
    }

    loadAllTextures();

    while( gameState != QUITING)
    {
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        switch (gameState)
        {
        case MAIN_MENU:
            displayMainMenu();
            break;
        case INTRO:
            //displayIntro();
            break;
        case RUNNING_LEVEL_1:
            displayLevel_1();
            break;
        case RUNNING_LEVEL_2:
            displayLevel_2();
        case WINNING:
            displayWinning();
            break;
        }
        SDL_RenderPresent( gRenderer );
    }
    utils::close(gWindow, gRenderer, gFont24, gFont32, gFont48);
    return 0;
}


void displayMainMenu()
{
    SDL_Event event;
    SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0xFF );
    SDL_RenderClear( gRenderer );


    while( SDL_PollEvent( &event ) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            gameState = QUITING;
            break;
        }
        startButton.handleEvent(event, mousePos);
    }
    if (startButton.isSelected())
    {
        gameState = RUNNING_LEVEL_1;
        startButton.setSelected(false);
    }
    main_menu.renderBackground(gRenderer);
    startButton.renderButton(gRenderer);
}

void displayLevel_1()
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) != 0 && ! bomb.isMoving())
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
        bomb.handleEvent(event, mousePos, mouseDown, mousePressed);
    }

    if ((mouseDown && mousePressed))
    {
        character.action = STANDING;
    }
    if (!mouseDown && mousePressed && ! bomb.isMoving())
    {
        character.action = THROWING;
        //mouseDown = true;
    }

    level_1.renderBackground(gRenderer);
    level_1.renderTiles(gRenderer);
    level_1.renderBorder(gRenderer);

    Texture text;
    std::string content = "";
    content = "Ninja in Jungle";
    text.loadFromRenderedText( gRenderer, content, gFont32, { 0xFF, 0xFF, 0xFF });
    text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 150);


    character.renderAction(gRenderer);
    for (auto &snake : snakes)
    {
        if (snake == nullptr) continue;

        snake->renderAction(gRenderer);
        if (snake->meet(character.getPos(), 50))
        {
            character.action = DYING;
        }
    }

    displayBomb();
}

void displayLevel_2()
{
    SDL_Event event;
    while( SDL_PollEvent( &event ) != 0 && ! bomb.isMoving())
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
        bomb.handleEvent(event, mousePos, mouseDown, mousePressed);
    }

    if (mouseDown && mousePressed)
    {
        character.action = STANDING;
    }
    if (!mouseDown && mousePressed && ! bomb.isMoving())
    {
        character.action = THROWING;
        //mouseDown = true;
    }

    level_2.renderBackground(gRenderer);
    level_2.renderTiles(gRenderer);
    level_2.renderBorder(gRenderer);

    Texture text;
    std::string content = "";
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };

    content = "Ninja in Ice Map";
    text.loadFromRenderedText( gRenderer, content, gFont32, textColor);
    text.render(gRenderer, ( SCREEN_WIDTH - text.getWidth() ) / 2, 150);

    character.renderAction(gRenderer);
    for (auto &snake : snakes)
    {
        if (snake == nullptr) continue;

        snake->renderAction(gRenderer);
        if (snake->meet(character.getPos(), 50))
        {
            character.action = DYING;
        }
    }

    displayBomb();
}

void displayWinning()
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
}

void displayBomb()
{
    if (mousePressed == true && mouseDown == false && !bomb.isMoving())
    {
        bomb.setInitPos(character.getPos());

        double alpha = atan(1.0 * std::abs(mousePos.y - SCREEN_HEIGHT + character.getPos().y) / std::abs(mousePos.x - character.getPos().x));
        bomb.setAlpha(alpha);

        bomb.resetTime();
        bomb.computeTimeOfMotion();
        bomb.setMoving(true);
    }

    if (mousePressed == true && mouseDown == false && bomb.isMoving())
    {
        bomb.updateTime(0.15);
        if (bomb.getTime() > bomb.getTimeOfMotion())
        {
            bomb.setMoving(false);
            bomb.resetTime();
            character.action = STANDING;
            mousePressed = false;
        }

        if (bomb.isMoving() == false)
        {
            bomb.renderExplosion(gRenderer);
        }

        for (auto &snake : snakes)
        {
            if (snake == nullptr) continue;
            if (snake->meet(bomb.getPos(), 30))
            {
                    bomb.renderExplosion(gRenderer);
                    //bomb.setMoving(false);
                    delete snake;
                    snake = nullptr;
            }
        }
        if (std::count(snakes.begin(), snakes.end(), nullptr) == (int)snakes.size())
        {
            if (gameState == RUNNING_LEVEL_1)
            {
                gameState = RUNNING_LEVEL_2;
            }
            else
            {
                gameState = WINNING;
            }
        }
        else
        {
            bomb.projectileMotion(gRenderer);
        }
    }
}
