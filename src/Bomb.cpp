#include "Bomb.h"
#include <conio.h>

const double PI = 3.14159265;

double rad(double deg)
{
    return deg * PI / 180;
}

double deg(double rad)
{
    return 180.0 * rad / PI;
}

Bomb::Bomb()
{
    initPosX = posX = 0;
    initPosY = posY = 0;
    velX = 0;
    velY = 0;
    initVel = 0;
    alpha = 0;
    time = 0.0;
    maxTime = 0.0;
    is_moving = false;
}

Bomb::Bomb(int posX, int posY, int velX, int velY, int initVel)
{
    this->initPosX = this->posX = posX;
    this->initPosY = this->posY = posY;
    this->velX = velX;
    this->velY = velY;
    this->initVel = initVel;
    alpha = 0;
    time = 0.0;
    maxTime = 0.0;
    is_moving = false;
}

Bomb::~Bomb()
{
    bombTexture.free();
    arrowTexture.free();
    explodeTexture.free();
}

int Bomb::getPosX()
{
    return posX;
}
int Bomb::getPosY()
{
    return posY;
}
int Bomb::getVelX()
{
    return velX;
}
int Bomb::getVelY()
{
    return velY;
}
bool Bomb::isMoving()
{
    return is_moving;
}
double Bomb::getTime()
{
    return time;
}
double Bomb::getTimeOfMotion()
{
    return maxTime;
}

void Bomb::setInitPosX(int initPosX)
{
    this->initPosX = initPosX;
}
void Bomb::setInitPosY(int initPosY)
{
    this->initPosY = initPosY;
}

void Bomb::setAlpha(double alpha)
{
    this->alpha = alpha;
}

void Bomb::setMoving(bool is_moving)
{
    this->is_moving = is_moving;
}


void Bomb::loadTextures(SDL_Renderer* &gRenderer)
{
    bombTexture.loadFromFile( gRenderer, "res/img/bomb.png" );
    arrowTexture.loadFromFile( gRenderer, "res/img/arrow.png" );
    explodeTexture.loadFromFile( gRenderer, "res/sprites/explosion/explosion.png" );
    for (int i = 0; i < explodeClips.getTotalFrames(); i++)
    {
        explodeClips.clips.push_back({0, 128 * i, 128, 128});
    }
}
void Bomb::handleEvent(SDL_Event& event, int& mouseX, int& mouseY, bool& mouseDown, bool& mousePressed)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            mouseDown = true;
            mousePressed = true;
            is_moving = false;
            initVel += 3;
            if (initVel > MAX_INIT_VELOCITY)
            {
                initVel = 0;
            }
            system("cls");
            std::cout << "Velocity = " << initVel << std::endl;

            SDL_GetMouseState(&mouseX, &mouseY);
            if (mouseX < posX)
            {
                mouseX = posX;
            }
        }
        break;
    case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            mouseDown = false;
        }
        break;
    }
}

void Bomb::computeTimeOfMotion()
{
    double t1 = initVel * sin(alpha) / GRAVITY;
    double H = pow(initVel,2) * pow(sin(alpha),2) / (2 * GRAVITY);
    double t2 = sqrt( 2 * (H + initPosY - 120) / GRAVITY);
    maxTime = t1 + t2;
}

void Bomb::projectileMotion(SDL_Renderer* &gRenderer)
{
    updateState();
    if (time != 0) {
        renderBomb(gRenderer);
    }
}

void Bomb::updateState()
{
    velX = initVel * cos(alpha);
    velY = initVel * sin(alpha) - GRAVITY * time;
    posX = initPosX + initVel * cos(alpha) * time;
    posY = initPosY + initVel * sin(alpha) * time - GRAVITY * time * time / 2;
}

void Bomb::updateTime(double dt)
{
    time += dt;
}

void Bomb::resetTime()
{
    time = 0;
}

void Bomb::renderBomb(SDL_Renderer* &gRenderer)
{
    double angle = -alpha;
    if (velX != 0)
    {
        angle = atan(std::abs(velY) / std::abs(velX));
        if (velY > 0)
            angle = -angle;
    }
    bombTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY, NULL, deg(angle));
}

void Bomb::renderArrow(SDL_Renderer* &gRenderer, int& mouseX, int& mouseY)
{
    arrowTexture.render(
        gRenderer,
        initPosX + 10, SCREEN_HEIGHT - initPosY + 10,
        NULL,
        -180 / PI * atan(1.0 * (SCREEN_HEIGHT - initPosY - mouseY) / (mouseX - initPosX))
    );
}

void Bomb::renderExplosion(SDL_Renderer* &gRenderer)
{
    for (int i = 0; i < explodeClips.getTotalFrames(); i++)
    {
        explodeTexture.render(gRenderer, posX - 50, SCREEN_HEIGHT - posY - 50, &explodeClips.clips[i]);
        SDL_RenderPresent(gRenderer);
    }
}
