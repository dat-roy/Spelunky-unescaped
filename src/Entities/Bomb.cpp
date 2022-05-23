#include "Bomb.h"
#include <conio.h>

Bomb::Bomb()
{
    initPos = pos = {0, 0};
    velX = 0;
    velY = 0;
    //vel = {0, 0};
    initVel = 100;
    alpha = 0;
    time = 0.0;
    maxTime = 0.0;
    is_moving = false;
}

Bomb::Bomb(SDL_Point pos, int initVel)
{
    this->initPos = this->pos = pos;
    this->velX = 0;
    this->velY = 0;
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
    }
}

//void Bomb::computeTimeOfMotion()
//{
//    double t1 = initVel * sin(alpha) / physics::GRAVITY;
//    double H = pow(initVel,2) * pow(sin(alpha),2) / (2 * physics::GRAVITY);
//    double t2 = sqrt( 2 * (H + initPos.y) / physics::GRAVITY);
//    maxTime = t1 + t2;
//}

void Bomb::projectileMotion(SDL_Renderer* gRenderer, SDL_Rect camera)
{
    updateState();
    if (time != 0) {
        renderBomb(gRenderer, camera);
    }
}

void Bomb::updateState()
{
    velX = initVel * cos(alpha);
    velY = initVel * sin(alpha) - physics::GRAVITY * time;
    pos.x = initPos.x + initVel * cos(alpha) * time;
    pos.y = initPos.y + initVel * sin(alpha) * time - physics::GRAVITY * time * time / 2;
}

void Bomb::updateTime(double dt)
{
    time += dt;
}

void Bomb::resetTime()
{
    time = 0;
}

void Bomb::renderBomb(SDL_Renderer* gRenderer, SDL_Rect camera)
{
    double angle = -alpha;
    if (velX != 0)
    {
        angle = atan(std::abs(velY) / std::abs(velX));
        if (velY > 0)
            angle = -angle;
    }
    bombTexture.render(gRenderer, pos.x - camera.x, SCREEN_HEIGHT - pos.y - camera.y, NULL, math::deg(angle));
}

void Bomb::renderExplosion(SDL_Renderer* gRenderer, SDL_Rect camera)
{
    for (int i = 0; i < explodeClips.getTotalFrames(); i++)
    {
        explodeTexture.render(gRenderer, pos.x - 50 - camera.x, SCREEN_HEIGHT - pos.y - 50 - camera.y, &explodeClips.clips[i]);
        SDL_RenderPresent(gRenderer);
    }
}

bool Bomb::meetBarrier(std::vector<std::vector<int>> tileValue, int TILE_ROW, int TILE_COL)
{
    if (pos.y > LEVEL_HEIGHT || pos.y < 0) return true;
    if (pos.x > LEVEL_WIDTH || pos.x < 0) return true;

    for (int i = 1; i <= TILE_ROW; i++)
    {
        for (int j = 1; j <= TILE_COL; j++)
        {
            SDL_Rect tile_rect;
            tile_rect.x = (j - 1) * TILE_WIDTH;
            tile_rect.y = (TILE_ROW - i + 1) * TILE_HEIGHT;
            tile_rect.w = TILE_WIDTH;
            tile_rect.h = TILE_HEIGHT;

            //Check tiles under character?
            if (math::checkCollision({pos.x, pos.y, WIDTH, HEIGHT}, tile_rect))
            {
                //If it is a soil tile
                if (tiles::isSoil(tileValue[i][j]))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
