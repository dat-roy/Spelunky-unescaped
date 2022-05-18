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

#define PI 3.14159265

//SDL utilities
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont24 = NULL;
TTF_Font *gFont32 = NULL;
TTF_Font *gFont48 = NULL;

bool quitGame = false;
bool winGame = false;
int mouseX = 0;
int mouseY = 0;
bool mouseDown = false;
bool mousePressed = false;

enum GameState {
    MAIN_MENU,
    RUNNING,
    WINNING,
    LOSING,
    QUITING,
};
GameState gameState = MAIN_MENU;

Map map;
Character character(100, 185, true);
Bomb bomb(character.getPosX(), character.getPosY());
std::vector<Enemy*> snakes;

void loadAllTextures()
{
    map.loadTextures(gRenderer, gFont24, gFont32, gFont48);
    character.loadTextures(gRenderer);
    bomb.loadTextures(gRenderer);

    for (int i = 0; i < 3; i++)
    {
        snakes.push_back(new Enemy);
    }
    snakes[0]->setFirstPosition(1000, 160, true);
    snakes[1]->setFirstPosition(900, 160, false);
    snakes[2]->setFirstPosition(800, 160, true);
    for (auto &snake : snakes)
    {
        snake->loadTextures(gRenderer);
    }
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
        character.move(8, 0);
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
        bomb.setInitPosX(character.getPosX());
        bomb.setInitPosY(character.getPosY());

        bomb.setAlpha( atan(1.0 * (SCREEN_HEIGHT - character.getPosY() - mouseY) / (mouseX - character.getPosX())) );
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
            if (std::abs(bomb.getPosX() - snake->getPosX()) <= 20
                && std::abs(bomb.getPosY() - snake->getPosY()) <= 20)
            {
                    //bomb.renderExplosion(gRenderer);
                    bomb.setMoving(false);
                    character.action = Character::STANDING;
                    //snake->~Enemy();
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

        while( SDL_PollEvent( &event ) != 0 )
        {
            if (event.type == SDL_QUIT)
            {
                gameState = QUITING;
                break;
            }
            character.handleAction(event);
            bomb.handleEvent(event, mouseX, mouseY, mouseDown, mousePressed);
        }

        if (mouseDown && mousePressed)
        {
            character.action = Character::STANDING;
            bomb.renderArrow(gRenderer, mouseX, mouseY);
        }
        if (!mouseDown && mousePressed)
        {
            character.action = Character::THROWING;
        }

        displayMaps();
        displayCharacter();
        displayEnemies();
        displayBomb();
        SDL_RenderPresent( gRenderer );
    }
    utils::close(gWindow, gRenderer, gFont24, gFont32, gFont48);
}
