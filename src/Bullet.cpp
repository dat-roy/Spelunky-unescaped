#include "Bullet.h"
#define PI 3.14159265

double rad(double deg)
{
    return deg * PI / 180;
}

double deg(double rad)
{
    return 180.0 * rad / PI;
}

Bullet::Bullet()
{
    initPosX = posX = 0;
    initPosY = posY = 0;
    velX = 0;
    velY = 0;
    initVel = 0;
    maxTime = 0.0;
}

Bullet::Bullet(int _posX, int _posY, int _velX, int _velY, int _initVel)
{
    initPosX = posX = _posX;
    initPosY = posY = _posY;
    velX = _velX;
    velY = _velY;
    initVel = _initVel;
    maxTime = 0.0;
}

Bullet::~Bullet()
{
    bulletTexture.free();
    arrowTexture.free();
    explodeTexture.free();
}

int Bullet::getPosX()
{
    return posX;
}
int Bullet::getPosY()
{
    return posY;
}
int Bullet::getVelX()
{
    return velX;
}
int Bullet::getVelY()
{
    return velY;
}
bool Bullet::getEndMove()
{
    return endMove;
}
double Bullet::getTimeOfMotion()
{
    return maxTime;
}

void Bullet::setInitPosX(int _initPosX)
{
    initPosX = _initPosX;
}
void Bullet::setInitPosY(int _initPosY)
{
    initPosY = _initPosY;
}
void Bullet::setEndMove(bool _endMove)
{
    endMove = _endMove;
}


void Bullet::loadTextures(SDL_Renderer* &gRenderer)
{
    bulletTexture.loadFromFile( gRenderer, "res/img/dot.bmp" );
    arrowTexture.loadFromFile( gRenderer, "res/img/arrow.png" );
    explodeTexture.loadFromFile( gRenderer, "res/img/explode.png" );
}
void Bullet::handleEvent(SDL_Event& event, int& mouseX, int& mouseY, bool& mouseDown, bool& mousePressed)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_SPACE)
        {
            initVel += 2;
            initVel = std::min(initVel, MAX_INIT_VELOCITY);
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

void Bullet::computeTimeOfMotion(const double &alpha)
{
    double t1 = initVel * sin(alpha) / GRAVITY;
    double H = pow(initVel,2) * pow(sin(alpha),2) / (2 * GRAVITY);
    double t2 = sqrt( 2 * (H + initPosY - 120) / GRAVITY);
    maxTime = t1 + t2;
}

void Bullet::projectileMotion(SDL_Renderer* &gRenderer, double &alpha, double &time)
{
    updateState(alpha, time);
    renderBullet(gRenderer, alpha);
    SDL_RenderPresent( gRenderer );
}

void Bullet::updateState(double alpha, double time)
{
    velX = initVel * cos(alpha);
    velY = initVel * sin(alpha) - GRAVITY * time;
    posX = initPosX + initVel * cos(alpha) * time;
    posY = initPosY + initVel * sin(alpha) * time - GRAVITY * time * time / 2;
}

void Bullet::renderBullet(SDL_Renderer* &gRenderer, double alpha)
{
    double angle = -alpha;
    if (velX != 0)
    {
        angle = atan(std::abs(velY) / std::abs(velX));
        if (velY > 0)
            angle = -angle;
    }
    bulletTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY + 45, NULL, deg(angle));
}

void Bullet::renderArrow(SDL_Renderer* &gRenderer, int& mouseX, int& mouseY)
{
    arrowTexture.render(
        gRenderer,
        initPosX, SCREEN_HEIGHT - initPosY + 15,
        NULL,
        -180 / PI * atan(1.0 * (SCREEN_HEIGHT - initPosY - mouseY) / (mouseX - initPosX))
    );
}

void Bullet::renderExplosion(SDL_Renderer* &gRenderer)
{
    explodeTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY + 20);
}
