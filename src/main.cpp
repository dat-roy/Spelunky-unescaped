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
#include "Bullet.h"
#include "Character.h"

#define PI 3.14159265

//SDL utilities
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font *gFont24 = NULL;
TTF_Font *gFont32 = NULL;
TTF_Font *gFont48 = NULL;

//Graphics textures
LTexture gBgTexture;
LTexture gArrowTexture;
LTexture gBulletTexture;
LTexture gStandingTexture;
LTexture gWalkingTexture;
SDL_Rect gWalkingClips[10];

LTexture gExplodeTexture;

//Text textures
LTexture textLine_01;
LTexture textLine_02;

bool quitGame = false;

void loadMedia();
void closeGame();

int main( int argc, char* args[] )
{
    if( !utils::init(gWindow, gRenderer, gFont24, gFont32, gFont48) )
    {
        std::cerr << "In main(): Failed to initialize initTools!\n";
        return 0;
    }

    loadMedia();
    SDL_Event event;

    int mouseX = 0;
    int mouseY = 0;
    Character character(100, 200, true);
    Bullet bullet(character.getPosX(), character.getPosY());

    bool mouseDown = false;
    bool mousePressed = false;
    int frame = 0;

    while( !quitGame )
    {
        gBgTexture.render(gRenderer, 0, 0);
        textLine_01.render(
            gRenderer,
            ( SCREEN_WIDTH - textLine_01.getWidth() ) / 2,
            100
        );
        textLine_02.render(
            gRenderer,
            ( SCREEN_WIDTH - textLine_02.getWidth() ) / 2,
            150
        );

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
            bullet.renderArrow(gRenderer, gArrowTexture, mouseX, mouseY);

        }
        if (character.action == Character::STANDING)
        {
            SDL_RendererFlip flipType = (character.isForward()) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
            gStandingTexture.render(gRenderer, character.getPosX(), SCREEN_HEIGHT - character.getPosY(), NULL, 0.0, NULL, flipType);
        }

        if (character.action == Character::WALKING)
        {
            bullet.setInitPosX(character.getPosX());
            bullet.setInitPosY(character.getPosY());

            SDL_RendererFlip flipType = (character.isForward()) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;

            gWalkingTexture.render(gRenderer, character.getPosX(), SCREEN_HEIGHT - character.getPosY(), &gWalkingClips[frame], 0.0, NULL, flipType);
            frame++;
            if (frame == 10)
            {
                frame = 0;
            }
            character.move(8, 0);
            SDL_Delay(10);
            SDL_RenderPresent( gRenderer );

            character.action = Character::STANDING;
        }
        SDL_RenderPresent( gRenderer );
        double time = 0;
        double alpha = atan(1.0 * (SCREEN_HEIGHT - character.getPosY() - mouseY) / (mouseX - character.getPosX()));
        double maxTime = bullet.getTimeOfMotion(alpha);

        while (mousePressed == true && mouseDown == false && !bullet.getEndMove())
        {
            time += 0.12;
            if (time > maxTime)
            {
                bullet.setEndMove(true);
            }
            gBgTexture.render(gRenderer, 0, 0);
            gStandingTexture.render(gRenderer, character.getPosX(), SCREEN_HEIGHT - character.getPosY());
            if (bullet.getEndMove())
            {
                gExplodeTexture.render(gRenderer, bullet.getPosX(), SCREEN_HEIGHT - bullet.getPosY());
                SDL_RenderPresent(gRenderer);
                SDL_Delay(800);
                break;
            }
            bullet.projectileMotion(gRenderer, gBulletTexture, alpha, time);
            while( SDL_PollEvent( &event ) != 0 )
            {
                if( event.type == SDL_QUIT )
                {
                    quitGame = true;
                }
            }
        }
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
    }
    return 0;
}


void loadMedia()
{
    gBgTexture.loadFromFile( gRenderer, "res/img/bg_.jpg" );                 //Load background
    gArrowTexture.loadFromFile( gRenderer, "res/img/point.png" );         //Load pointer for motion
    gBulletTexture.loadFromFile( gRenderer, "res/img/bomb.png" );
    gStandingTexture.loadFromFile( gRenderer, "res/img/idle.png" );
    gWalkingTexture.loadFromFile( gRenderer, "res/sprites/walking.png" );
    for (int i = 0; i < 10; i++)
    {
        gWalkingClips[i] = { 128 * i, 0, 128, 128};
    }
    gExplodeTexture.loadFromFile( gRenderer, "res/img/explode.png" );

    //Render text
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    textLine_01.loadFromRenderedText( gRenderer,
                                      " ",
                                      gFont32, textColor);
    textLine_02.loadFromRenderedText( gRenderer,
                                      "Use SPACE to modify initial velocity [0..100]",
                                      gFont24, textColor);
}

void closeGame()
{
    //Free resources
    gArrowTexture.free();
    gBgTexture.free();
    gBulletTexture.free();
    textLine_01.free();
    textLine_02.free();

    utils::close(gWindow, gRenderer, gFont24, gFont32, gFont48);
}
