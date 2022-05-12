#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include "Global.h"
#include "SDL_Utils.h"
#include "Texture.h"
#include "Map.h"
#include "bomb.h"
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

int main( int argc, char* args[] )
{

    if( !utils::init(gWindow, gRenderer, gFont24, gFont32, gFont48) )
    {
        std::cerr << "In main(): Failed to initialize initTools!\n";
        return 0;
    }

    //Initialize maps
    Map map;
    map.loadTextures(gRenderer, gFont24, gFont32, gFont48);

    SDL_Event event;
    int mouseX = 0;
    int mouseY = 0;
    Character character(100, 185, true);
    character.loadTextures(gRenderer);

    Bomb bomb(character.getPosX(), character.getPosY());
    bomb.loadTextures(gRenderer);


    std::vector<Enemy*> snakes;
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

    bool mouseDown = false;
    bool mousePressed = false;

    while( !quitGame )
    {
        map.renderBackground(gRenderer, 0, 0);
        if (! winGame)
        {
            map.renderText_01(gRenderer);
            map.renderText_02(gRenderer);
        } else {
            map.renderText_03(gRenderer);
        }

        for (auto &snake : snakes)
        {
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

        while( SDL_PollEvent( &event ) != 0 )
        {
            if (event.type == SDL_QUIT)
            {
                quitGame = true;
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
        if (character.action == Character::STANDING)
        {
            character.renderStanding(gRenderer);
        }

        if (character.action == Character::LYING)
        {
            character.renderLying(gRenderer);
        }
        if (character.action == Character::WALKING)
        {
            character.renderWalking(gRenderer);
            character.move(8, 0);
        }

        if (character.action == Character::CRAWLING)
        {
            character.renderCrawling(gRenderer);
            character.move(3, 0);
        }
        SDL_RenderPresent( gRenderer );
        bomb.setInitPosX(character.getPosX());
        bomb.setInitPosY(character.getPosY());
        double alpha = atan(1.0 * (SCREEN_HEIGHT - character.getPosY() - mouseY) / (mouseX - character.getPosX()));

        double time = 0;
        bomb.computeTimeOfMotion(alpha);

        while (mousePressed == true && mouseDown == false && !bomb.getEndMove())
        {
            time += 0.12;
            if (time > bomb.getTimeOfMotion())
            {
                mousePressed = false;
                bomb.setEndMove(true);
                character.action = Character::STANDING;
            }
            map.renderBackground(gRenderer, 0, 0);

            for (auto &snake : snakes)
            {
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


            if (character.action == Character::THROWING)
            {
                character.renderThrowing(gRenderer);
            }
            if (character.action == Character::STANDING)
            {
                character.renderStanding(gRenderer);
            }
            if (bomb.getEndMove())
            {
                bomb.renderExplosion(gRenderer);
                break;
            }

            for (auto &snake : snakes)
            {
                if (std::abs(bomb.getPosX() - snake->getPosX()) <= 30
                    && std::abs(bomb.getPosY() - snake->getPosY()) <= 30)
                {
                    snake->updateBlood(-1000);
                    if (snake->getBlood() == 0) {
                        snake->~Enemy();
                        delete snake;
                        snake = nullptr;
                     }
                }
            }
            for (int i = 0; i < (int)snakes.size(); i++)
            {
                if (snakes[i] == nullptr)
                {
                    snakes.erase(snakes.begin() + i);
                }
            }
            bomb.projectileMotion(gRenderer, alpha, time);
            if (snakes.empty())
            {
                winGame = true;
            }
        }
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
    }
    utils::close(gWindow, gRenderer, gFont24, gFont32, gFont48);
}
