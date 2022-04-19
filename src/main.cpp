#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "Global.h"
#include "SDL_Utils.h"
#include "LTexture.h"
#include "Map.h"
#include "Bullet.h"
#include "Character.h"

#define PI 3.14159265

//SDL utilities
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont24 = NULL;
TTF_Font *gFont32 = NULL;
TTF_Font *gFont48 = NULL;

bool quitGame = false;

int main( int argc, char* args[] )
{
    if( !utils::init(gWindow, gRenderer, gFont24, gFont32, gFont48) )
    {
        std::cerr << "In main(): Failed to initialize initTools!\n";
        return 0;
    }

    Map map;
    map.loadTextures(gRenderer, gFont24, gFont32, gFont48);

    SDL_Event event;
    int mouseX = 0;
    int mouseY = 0;
    Character character(100, 200, true);
    character.loadTextures(gRenderer);
    Bullet bullet(character.getPosX(), character.getPosY());
    bullet.loadTextures(gRenderer);

    bool mouseDown = false;
    bool mousePressed = false;

    while( !quitGame )
    {
        map.renderBackground(gRenderer, 0, 0);
        map.renderText_01( gRenderer, ( SCREEN_WIDTH - map.getText_01().getWidth() ) / 2, 100 );
        map.renderText_02( gRenderer, ( SCREEN_WIDTH - map.getText_02().getWidth() ) / 2, 150 );
        //SDL_Delay(100);

        while( SDL_PollEvent( &event ) != 0 )
        {
            if (event.type == SDL_QUIT)
            {
                quitGame = true;
                break;
            }
            character.handleAction(event);
            bullet.handleEvent(event, mouseX, mouseY, mouseDown, mousePressed);
        }

        if (mouseDown && mousePressed)
        {
            character.action = Character::STANDING;
            bullet.renderArrow(gRenderer, mouseX, mouseY);
        }
        if (character.action == Character::STANDING)
        {
            character.renderStanding(gRenderer);
        }

        if (character.action == Character::WALKING)
        {
            bullet.setInitPosX(character.getPosX());
            bullet.setInitPosY(character.getPosY());

            character.renderWalking(gRenderer);
            character.move(8, 0);
            SDL_Delay(10);
            SDL_RenderPresent( gRenderer );

            character.action = Character::STANDING;
        }
        SDL_RenderPresent( gRenderer );
        double time = 0;
        double alpha = atan(1.0 * (SCREEN_HEIGHT - character.getPosY() - mouseY) / (mouseX - character.getPosX()));

        bullet.computeTimeOfMotion(alpha);

        while (mousePressed == true && mouseDown == false && !bullet.getEndMove())
        {
            time += 0.12;
            if (time > bullet.getTimeOfMotion())
            {
                bullet.setEndMove(true);
            }
            map.renderBackground(gRenderer, 0, 0);
            character.renderStanding(gRenderer);
            if (bullet.getEndMove())
            {
                bullet.renderExplosion(gRenderer);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(800);
                break;
            }
            bullet.projectileMotion(gRenderer, alpha, time);
        }
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
    }
    return 0;

    utils::close(gWindow, gRenderer, gFont24, gFont32, gFont48);
}


