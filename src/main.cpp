#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Global.h"
#include "SDL_Utils.h"
#include "Texture.h"
#include "Map.h"
#include "Bomb.h"
#include "Character.h"
#include "Enemy.h"
#include "Button.h"

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

// Map, characters & enemies
Map map;
Character character({100, 185}, true);
Bomb bomb(character.getPos(), 0, 0, 70);
std::vector<Enemy*> snakes;

// Start button
Button startButton({ (SCREEN_WIDTH - 200)/ 2, 280, 200, 75 });

void loadAllTextures()
{
    map.loadTextures(gRenderer, gFont24, gFont32, gFont48);
    character.loadTextures(gRenderer);
    bomb.loadTextures(gRenderer);

    for (int i = 0; i < 3; i++)
    {
        snakes.push_back(new Enemy);
    }
    snakes[0]->setFirstPosition({1000, 160}, true);
    snakes[1]->setFirstPosition({900, 160}, false);
    snakes[2]->setFirstPosition({800, 160}, true);
    for (auto &snake : snakes)
    {
        snake->loadTextures(gRenderer);
    }

    startButton.loadTextures(gRenderer);
}

void displayMaps()
{
    map.renderBackground(gRenderer, 0, 0);
    if ( gameState == WINNING)
    {
        map.renderText_03(gRenderer);
    } else {
        map.renderText_01(gRenderer);
        map.renderText_02(gRenderer);
    }
}

void displayCharacter()
{
    switch (character.action)
    {
    case Character::STANDING:
        character.renderStanding(gRenderer);
        break;

    case Character::LYING:
        character.renderLying(gRenderer);
        break;

    case Character::WALKING:
        character.renderWalking(gRenderer);
        character.move(5, 0);
        break;

    case Character::CRAWLING:
        character.renderCrawling(gRenderer);
        character.move(3, 0);
    }
}

void displayEnemies()
{
    for (auto &snake : snakes)
    {
        if (snake == nullptr) continue;
        if (snake->action == Enemy::CRAWLING)
        {
            snake->renderSnakeCrawling(gRenderer);
        }
        if (snake->action == Enemy::ATTACKING)
        {
            snake->renderSnakeAttacking(gRenderer);
        }
        snake->move(1, 0);
    }
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
            character.action = Character::STANDING;
            mousePressed = false;
        }

        if (character.action == Character::THROWING)
        {
            character.renderThrowing(gRenderer);
        }
        if (character.action == Character::STANDING)
        {
            character.renderStanding(gRenderer);
        }
        if (bomb.isMoving() == false)
        {
            bomb.renderExplosion(gRenderer);
        }

        for (auto &snake : snakes)
        {
            if (snake == nullptr) continue;
            if (std::abs(bomb.getPos().x - snake->getPos().x) <= 20
                && std::abs(bomb.getPos().y - snake->getPos().y) <= 20)
            {
                    bomb.renderExplosion(gRenderer);
                    //bomb.setMoving(false);
                    character.action = Character::STANDING;
                    delete snake;
                    snake = nullptr;
            }
        }
        if (std::count(snakes.begin(), snakes.end(), nullptr) == (int)snakes.size())
        {
            gameState = WINNING;
        }
        bomb.projectileMotion(gRenderer);
    }
}

int main( int argc, char* args[] )
{
    if( !utils::init(gWindow, gRenderer, gFont24, gFont32, gFont48) )
    {
        std::cerr << "In main(): Failed to initialize initTools!\n";
        return 0;
    }

    loadAllTextures();

    SDL_Event event;

    while( gameState != QUITING)
    {
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        if (gameState == MAIN_MENU) {
            while( SDL_PollEvent( &event ) != 0)
            {
                if (event.type == SDL_QUIT)
                {
                    gameState = QUITING;
                    break;
                }
                startButton.handleEvent(event, mousePos);
                if (startButton.isSelected())
                {
                    gameState = RUNNING;
                    startButton.setSelected(false);
                }
            }
            map.renderMainMenu(gRenderer);
            startButton.renderButton(gRenderer);

        } else {
            while( SDL_PollEvent( &event ) != 0 && ! bomb.isMoving())
            {
                if (event.type == SDL_QUIT)
                {
                    gameState = QUITING;
                    break;
                }
                if (event.type == SDL_KEYDOWN)
                {
                    if (event.key.keysym.sym == SDLK_b) {
                        gameState = MAIN_MENU;
                    }
                }
                character.handleAction(event);
                bomb.handleEvent(event, mousePos, mouseDown, mousePressed);
            }

            if (mouseDown && mousePressed)
            {
                character.action = Character::STANDING;
            }
            if (!mouseDown && mousePressed)
            {
                character.action = Character::THROWING;
            }
            displayMaps();
            displayCharacter();
            displayEnemies();
            displayBomb();
        }


        SDL_RenderPresent( gRenderer );
    }
    utils::close(gWindow, gRenderer, gFont24, gFont32, gFont48);
    return 0;
}
