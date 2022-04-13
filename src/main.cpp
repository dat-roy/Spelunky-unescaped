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

//Text texture
static LTexture textLine_01;
static LTexture textLine_02;
static LTexture gBulletTexture;

bool loadMedia(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont)
{
    try
    {
        //Load bmp
        if( !gBulletTexture.loadFromFile( gRenderer, "res/img/dot.bmp" ) )
        {
            throw "Failed to load dot texture!\n";
        }
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if (! textLine_01.loadFromRenderedText(
                                          gRenderer,
                                          "Simulate projectile motion of a bullet: ",
                                          gFont,
                                          textColor
                                          ))
        {
            throw "Failed to render text texture\n";
        }

        if (! textLine_02.loadFromRenderedText(
                                          gRenderer,
                                          "Use SPACE to modify initial velocity [0..100]",
                                          gFont,
                                          textColor
                                          ))
        {
            throw "Failed to render text texture\n";
        }
        return true;
    }
    catch (const char* &error)
    {
        std::cerr << "In loadMedia(): " << error << std::endl;
        return false;
    }
}

int main( int argc, char* args[] )
{
    static SDL_Window* gWindow = NULL;
    static SDL_Renderer* gRenderer = NULL;
    static TTF_Font *gFont = NULL;


	if( !utils::init(gWindow, gRenderer, gFont) )
	{
		std::cerr << "In main(): Failed to initialize initTools!\n";
	}
	else
	{
		if( !loadMedia(gWindow, gRenderer, gFont) )
		{
			std::cerr << "In main(): Failed to load media!\n";
		}
		else
		{
			bool quitGame = false;
			SDL_Event e;

            int mouseX = 0;
            int mouseY = 0;

            int initPosX = 100;
            int initPosY = 200;
            Bullet bullet(100, 200, 0, 0);

            bool mouseDown = false;
            bool mousePressed = false;

			while( !quitGame )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
                    switch (e.type) {
                        case SDL_QUIT:
                            quitGame = true;
                            break;
                    }
                    bullet.handleEvent(e, mouseX, mouseY, mouseDown, mousePressed);
				}

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
                textLine_01.render(
                                gRenderer,
                                ( SCREEN_WIDTH - textLine_01.getWidth() ) / 2,
                                100
                            );
                textLine_02.render(
                                gRenderer,
                                ( SCREEN_WIDTH - textLine_01.getWidth() ) / 2,
                                150
                            );
                bullet.render(gRenderer, gBulletTexture);

				//Update screen
				SDL_RenderPresent( gRenderer );

                if (mousePressed == true && mouseDown == false) {

                    double alpha = atan(1.0 * (SCREEN_HEIGHT - initPosY - mouseY) / (mouseX - initPosX));
                    double time = 0;
                    //std::cout << 180.0 * alpha / 3.14 << std::endl;
                    bullet.projectileMotion(gRenderer, gBulletTexture, alpha, time,  mouseX, mouseY, quitGame);
                    mousePressed = false;
                }
			}
		}
	}

	//Free resources and close SDL
	gBulletTexture.free();
	textLine_01.free();
	textLine_02.free();
	utils::close(gWindow, gRenderer, gFont);

	return 0;
}
