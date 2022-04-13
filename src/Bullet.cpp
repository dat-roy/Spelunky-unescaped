#include "Bullet.h"
#define PI 3.14159265

double rad(double deg)
{
    return deg * PI / 180;
}

Bullet::Bullet()
{
    initPosX = posX = 0;
    initPosY = posY = 0;
    velX = 0;
    velY = 0;
    initVel = 0;
}

Bullet::Bullet(int _posX, int _posY, int _velX, int _velY, int _initVel)
{
    initPosX = posX = _posX;
    initPosY = posY = _posY;
    velX = _velX;
    velY = _velY;
    initVel = _initVel;
}

void Bullet::handleEvent(SDL_Event e, int& mouseX, int& mouseY, bool& mouseDown, bool& mousePressed)
{
    switch (e.type)
    {
         case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_SPACE)
            {
                initVel += 1;
                initVel = std::min(initVel, MAX_INIT_VELOCITY);
                std::cout << "Velocity = " << initVel << std::endl;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                mouseDown = true;
                mousePressed = true;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX < posX) {
                    mouseX = posX;
                }
                //SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                //SDL_RenderDrawLine(gRenderer, initPosX, SCREEN_HEIGHT - initPosY, mouseX, mouseY);
                //Update screen
                //SDL_RenderPresent( gRenderer );
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                mouseDown = false;
            }
            break;
    }
}

void Bullet::projectileMotion(SDL_Renderer* &gRenderer, LTexture &gBulletTexture, double alpha, double time, int mouseX, int mouseY, bool& quitGame)
{
    for (int i = 0; i <= 200; i++) {
        time += 0.1;
        updateState(alpha, time);

        if (posY < 0) {
            alpha = atan(1.0 * std::abs(velY) / std::abs(velX));
            time = 0;
            initPosX = posX;
            initPosY = posY;
            initVel = sqrt( pow(velY, 2) + pow(velX, 2) );
        }
        render(gRenderer, gBulletTexture);
        SDL_RenderPresent( gRenderer );
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        SDL_Event e;
        while( SDL_PollEvent( &e ) != 0 )
        {
            if( e.type == SDL_QUIT )
            {
                quitGame = true;
                return;
            }
        }
    }
}

void Bullet::updateState(double alpha, double time)
{
    velX = initVel * cos(alpha);
    velY = initVel * sin(alpha) - GRAVITY * time;

    posX = initPosX + initVel * cos(alpha) * time;
    posY = initPosY + initVel * sin(alpha) * time - GRAVITY * time * time / 2;
}


void Bullet::render(SDL_Renderer* &gRenderer, LTexture &gTexture)
{
    gTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY);
}

