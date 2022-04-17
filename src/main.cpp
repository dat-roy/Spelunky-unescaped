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

#define PI 3.14159265

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static TTF_Font *gFont = NULL;

//Text texture
static LTexture gBgTexture;
static LTexture gPointerTexture;
static LTexture gBulletTexture;
static LTexture gCharacterTexture;
static LTexture gExplodeTexture;

static LTexture textLine_01;
static LTexture textLine_02;

bool loadMedia()
{
    gBgTexture.loadFromFile( gRenderer, "res/img/bg.jpg" );                 //Load background
    gPointerTexture.loadFromFile( gRenderer, "res/img/point.png" );         //Load pointer for motion
    gBulletTexture.loadFromFile( gRenderer, "res/img/weapon.png" );
    gCharacterTexture.loadFromFile( gRenderer, "res/img/idle.png" );
    gExplodeTexture.loadFromFile( gRenderer, "res/img/explode.png" );

    //Render text
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    textLine_01.loadFromRenderedText( gRenderer,
                                      "NINJA IN JUNGLE",
                                      gFont, textColor);
    textLine_02.loadFromRenderedText( gRenderer,
                                      "Use SPACE to modify initial velocity [0..100]",
                                      gFont, textColor);
}

int main( int argc, char* args[] )
{
    if( !utils::init(gWindow, gRenderer, gFont) )
    {
        std::cerr << "In main(): Failed to initialize initTools!\n";
        return 0;
    }

    loadMedia();

    bool quitGame = false;
    SDL_Event e;

    int mouseX = 0;
    int mouseY = 0;

    int initPosX = 150;
    int initPosY = 120;
    Bullet bullet(initPosX, initPosY, 0, 0);

    bool mouseDown = false;
    bool mousePressed = false;


    while( !quitGame )
    {
        //Handle events on queue
        gBgTexture.render(gRenderer, 0, 0);
        gCharacterTexture.render(gRenderer, 150, SCREEN_HEIGHT - 130);
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

        while( SDL_PollEvent( &e ) != 0 )
        {
            if (e.type == SDL_QUIT)
            {
                quitGame = true;
                break;
            }
            bullet.handleEvent(gRenderer, gPointerTexture, e, mouseX, mouseY, mouseDown, mousePressed);
        }

        SDL_RenderPresent( gRenderer );
        double time = 0;
        double alpha = atan(1.0 * (SCREEN_HEIGHT - initPosY - mouseY) / (mouseX - initPosX));
        double maxTime = bullet.getTimeOfMotion(alpha);

        while (mousePressed == true && mouseDown == false)
        {
            time += 0.12;
            if (time > maxTime)
            {
                gBgTexture.render(gRenderer, 0, 0);
                gCharacterTexture.render(gRenderer, 150, SCREEN_HEIGHT - 130);
                gExplodeTexture.render(gRenderer,bullet.getPosX(),SCREEN_HEIGHT - 100);
                SDL_RenderPresent(gRenderer);
                SDL_Delay(800);
                mousePressed = false;
            }
            gBgTexture.render(gRenderer, 0, 0);
            gCharacterTexture.render(gRenderer, 150, SCREEN_HEIGHT - 130);
            bullet.projectileMotion(gRenderer, gBulletTexture, alpha, time, quitGame);

            while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_QUIT )
                {
                    quitGame = true;
                }
            }
        }
    }


    //Free resources and close SDL
    gPointerTexture.free();
    gBgTexture.free();
    gBulletTexture.free();
    //gWeaponTexture.free();
    textLine_01.free();
    textLine_02.free();
    utils::close(gWindow, gRenderer, gFont);

    return 0;
}
