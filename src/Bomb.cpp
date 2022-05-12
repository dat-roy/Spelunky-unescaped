#include "Bomb.h"
#define PI 3.14159265

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
    maxTime = 0.0;
}

Bomb::Bomb(int _posX, int _posY, int _velX, int _velY, int _initVel)
{
    initPosX = posX = _posX;
    initPosY = posY = _posY;
    velX = _velX;
    velY = _velY;
    initVel = _initVel;
    maxTime = 0.0;
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
bool Bomb::getEndMove()
{
    return endMove;
}
double Bomb::getTimeOfMotion()
{
    return maxTime;
}

void Bomb::setInitPosX(int _initPosX)
{
    initPosX = _initPosX;
}
void Bomb::setInitPosY(int _initPosY)
{
    initPosY = _initPosY;
}
void Bomb::setEndMove(bool _endMove)
{
    endMove = _endMove;
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
            initVel += 2;
            initVel = std::min(initVel, MAX_INIT_VELOCITY);
            //system("cls");
            std::cout << "Velocity = " << initVel << std::endl;
        }
        if (event.key.keysym.sym == SDLK_m)
        {
            mouseDown = true;
            mousePressed = true;
            endMove = false;

            SDL_GetMouseState(&mouseX, &mouseY);
            if (mouseX < posX)
            {
                mouseX = posX;
            }
        }
        break;
    case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_m)
        {
            mouseDown = false;
        }
        break;
    }
}

void Bomb::computeTimeOfMotion(const double &alpha)
{
    double t1 = initVel * sin(alpha) / GRAVITY;
    double H = pow(initVel,2) * pow(sin(alpha),2) / (2 * GRAVITY);
    double t2 = sqrt( 2 * (H + initPosY - 120) / GRAVITY);
    maxTime = t1 + t2;
}

void Bomb::projectileMotion(SDL_Renderer* &gRenderer, double &alpha, double &time)
{
    updateState(alpha, time);
    renderbomb(gRenderer, alpha);
    SDL_RenderPresent( gRenderer );
}

void Bomb::updateState(double alpha, double time)
{
    velX = initVel * cos(alpha);
    velY = initVel * sin(alpha) - GRAVITY * time;
    posX = initPosX + initVel * cos(alpha) * time;
    posY = initPosY + initVel * sin(alpha) * time - GRAVITY * time * time / 2;
}

void Bomb::renderbomb(SDL_Renderer* &gRenderer, double alpha)
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
        SDL_Delay(30);
    }
}
