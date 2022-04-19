#include "Character.h"

Character::Character()
{
    posX = 0;
    posY = 0;
    blood = MAX_BLOOD;
    is_forward = true;
    current_walking_frame = 0;
}
Character::Character(int _posX, int _posY, bool _is_forward)
{
    posX = _posX;
    posY = _posY;
    is_forward = _is_forward;
    current_walking_frame = 0;
}
Character::~Character()
{
    gStandingTexture.free();
    gWalkingTexture.free();
}

int Character::getPosX() { return posX; }
int Character::getPosY() { return posY; }
bool Character::isForward() { return is_forward; }

void Character::loadTextures(SDL_Renderer* &gRenderer)
{
    gStandingTexture.loadFromFile( gRenderer, "res/img/idle.png" );
    gWalkingTexture.loadFromFile( gRenderer, "res/sprites/walking.png" );
    for (int i = 0; i < 10; i++)
    {
        gWalkingClips[i] = { 128 * i, 0, 128, 128};
    }
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


void Character::renderStanding(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    gStandingTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY, NULL, 0.0, NULL, flipType);
}

void Character::renderWalking(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    gWalkingTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY, &gWalkingClips[current_walking_frame], 0.0, NULL, flipType);
    current_walking_frame++;
    if (current_walking_frame == WALKING_FRAME_TOTAL)
    {
        current_walking_frame = 0;
    }
}
