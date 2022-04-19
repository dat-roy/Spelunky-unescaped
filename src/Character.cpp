#include "Character.h"

Character::Character()
{
    posX = 0;
    posY = 0;
    blood = MAX_BLOOD;
    is_forward = true;
}

Character::Character(int _posX, int _posY, bool _is_forward)
{
    posX = _posX;
    posY = _posY;
    is_forward = _is_forward;
}

void Character::handleAction(SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_RIGHT)
        {
            action = WALKING;
            is_forward = true;
        }
        if (event.key.keysym.sym == SDLK_LEFT)
        {
            action = WALKING;
            is_forward = false;
        }
        break;
    case SDL_KEYUP:
        if (event.key.keysym.sym == SDLK_RIGHT)
        {
            action = STANDING;
        }
        if (event.key.keysym.sym == SDLK_LEFT)
        {
            action = STANDING;
        }
        break;
    }
}

void Character::move(int dx, int dy)
{
    if (is_forward)
    {
        posX = std::min(posX + dx, SCREEN_WIDTH - 100);
    }
    else
    {
        posX = std::max(posX - dx, 0);
    }
    posY += dy;
}

int Character::getPosX()
{
    return posX;
}

int Character::getPosY()
{
    return posY;
}

bool Character::isForward()
{
    return is_forward;
}
