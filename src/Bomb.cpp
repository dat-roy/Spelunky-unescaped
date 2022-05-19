#include "Bomb.h"
#include <conio.h>

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
    initPos = pos = {0, 0};
    velX = 0;
    velY = 0;
    //vel = {0, 0};
    initVel = 0;
    alpha = 0;
    time = 0.0;
    maxTime = 0.0;
    is_moving = false;
}

Bomb::Bomb(SDL_Point pos, int velX, int velY, int initVel)
{
    this->initPos = this->pos = pos;
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
    explodeTexture.free();
}

SDL_Point Bomb::getPos()
{
    return pos;
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

void Bomb::setInitPos(SDL_Point initPos)
{
    this->initPos = initPos;
}

void Bomb::setAlpha(double alpha)
{
    this->alpha = alpha;
}

void Bomb::setMoving(bool is_moving)
{
    this->is_moving = is_moving;
}


void Bomb::loadTextures(SDL_Renderer* gRenderer)
{
    bombTexture.loadFromFile( gRenderer, "res/img/bomb.png" );
    explodeTexture.loadFromFile( gRenderer, "res/sprites/explosion/explosion.png" );
    for (int i = 0; i < explodeClips.getTotalFrames(); i++)
    {
        explodeClips.clips.push_back({0, 128 * i, 128, 128});
    }
}
void Bomb::handleEvent(SDL_Event& event, SDL_Point& mousePos, bool& mouseDown, bool& mousePressed)
{
    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            mouseDown = true;
            mousePressed = true;
            is_moving = false;
            SDL_GetMouseState(&mousePos.x, &mousePos.y);
            if (mousePos.x < pos.x)
            {
                mousePos.x = pos.x;
            }
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            mouseDown = false;
        }
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            initVel += 3;
            if (initVel > MAX_INIT_VELOCITY)
            {
                initVel = 0;
            }
            system("cls");
            std::cout << "Velocity = " << initVel << std::endl;
        }
        break;
    case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            //mouseDown = false;
            //initVel = 0;
        }
        break;
    }
}

void Bomb::computeTimeOfMotion()
{
    double t1 = initVel * sin(alpha) / GRAVITY;
    double H = pow(initVel,2) * pow(sin(alpha),2) / (2 * GRAVITY);
    double t2 = sqrt( 2 * (H + initPos.y - 120) / GRAVITY);
    maxTime = t1 + t2;
}

void Bomb::projectileMotion(SDL_Renderer* gRenderer)
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
    pos.x = initPos.x + initVel * cos(alpha) * time;
    pos.y = initPos.y + initVel * sin(alpha) * time - GRAVITY * time * time / 2;
}

void Bomb::updateTime(double dt)
{
    time += dt;
}

void Bomb::resetTime()
{
    time = 0;
}

void Bomb::renderBomb(SDL_Renderer* gRenderer)
{
    double angle = -alpha;
    if (velX != 0)
    {
        angle = atan(std::abs(velY) / std::abs(velX));
        if (velY > 0)
            angle = -angle;
    }
    bombTexture.render(gRenderer, pos.x, SCREEN_HEIGHT - pos.y, NULL, deg(angle));
}

void Bomb::renderExplosion(SDL_Renderer* gRenderer)
{
    for (int i = 0; i < explodeClips.getTotalFrames(); i++)
    {
        explodeTexture.render(gRenderer, pos.x - 50, SCREEN_HEIGHT - pos.y - 50, &explodeClips.clips[i]);
        SDL_RenderPresent(gRenderer);
    }
}