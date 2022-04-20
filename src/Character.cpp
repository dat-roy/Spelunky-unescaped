#include "Character.h"

Character::Character()
{
    posX = 0;
    posY = 0;
    blood = MAX_BLOOD;
    is_forward = true;
    current_walking_frame = 0;
    current_lying_frame = 0;
    current_crawling_frame = 0;
    current_throwing_frame = 0;
}
Character::Character(int _posX, int _posY, bool _is_forward)
{
    posX = _posX;
    posY = _posY;
    is_forward = _is_forward;
    current_walking_frame = 0;
    current_lying_frame = 0;
    current_crawling_frame = 0;
    current_throwing_frame = 0;
}
Character::~Character()
{
    standingTexture.free();
    walkingTexture.free();
    lyingTexture.free();
    crawlingTexture.free();
    throwingTexture.free();
}

int Character::getPosX() { return posX; }
int Character::getPosY() { return posY; }
bool Character::isForward() { return is_forward; }

void Character::loadTextures(SDL_Renderer* &gRenderer)
{
    standingTexture.loadFromFile( gRenderer, "res/sprites/standing.png" );
    walkingTexture.loadFromFile( gRenderer, "res/sprites/walking.png" );
    for (int i = 0; i < WALKING_FRAME_TOTAL; i++)
    {
        walkingClips[i] = {76 * i, 0, 76, 76};
    }
    lyingTexture.loadFromFile( gRenderer, "res/sprites/lying.png");
    for (int i = 0; i < LYING_FRAME_TOTAL; i++)
    {
        lyingClips[i] = {76 * i, 0, 76, 76};
    }
    crawlingTexture.loadFromFile( gRenderer, "res/sprites/crawling.png");
    for (int i = 0; i < CRAWLING_FRAME_TOTAL; i++)
    {
        crawlingClips[i] = {81 * i, 0, 81, 76};
    }
    throwingTexture.loadFromFile( gRenderer, "res/sprites/throwing.png");
    for (int i = 0; i < THROWING_FRAME_TOTAL; i++)
    {
        throwingClips[i] = {76 * i, 0, 76, 76};
    }
}

void Character::handleAction(SDL_Event& event)
{
    switch (event.type)
    {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            if (action == LYING)
            {
                action = STANDING;
            }
            break;
        case SDLK_DOWN:
            action = LYING;
            break;
        case SDLK_RIGHT:
            is_forward = true;
            if (action == STANDING)
            {
                action = WALKING;
            }
            if (action == LYING)
            {
                action = CRAWLING;
            }
            break;

        case SDLK_LEFT:
            is_forward = false;
            if (action == STANDING)
            {
                action = WALKING;
            }
            if (action == LYING)
            {
                action = CRAWLING;
            }
            break;
        }
        break;
    case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
            if (action == CRAWLING)
            {
                action = LYING;
            }
            else
            {
                action = STANDING;
            }
            break;

        case SDLK_LEFT:
            if (action == CRAWLING)
            {
                action = LYING;
            }
            else
            {
                action = STANDING;
            }
            break;
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
    standingTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY, NULL, 0.0, NULL, flipType);
}

void Character::renderWalking(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    walkingTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY, &walkingClips[current_walking_frame], 0.0, NULL, flipType);
    current_walking_frame++;
    if (current_walking_frame == WALKING_FRAME_TOTAL)
    {
        current_walking_frame = 0;
    }
}

void Character::renderLying(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    lyingTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY + 5, &lyingClips[current_lying_frame], 0.0, NULL, flipType);
    if (current_lying_frame < LYING_FRAME_TOTAL - 1)
    {
        current_lying_frame++;
    }
}

void Character::renderCrawling(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    crawlingTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY + 5, &crawlingClips[current_crawling_frame], 0.0, NULL, flipType);
    current_crawling_frame++;
    if (current_crawling_frame == CRAWLING_FRAME_TOTAL)
    {
        current_crawling_frame = 0;
    }
}

void Character::renderThrowing(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    throwingTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY, &throwingClips[current_throwing_frame], 0.0, NULL, flipType);
    if (current_throwing_frame < THROWING_FRAME_TOTAL - 1)
    {
        current_throwing_frame++;
    }
    if (current_throwing_frame == THROWING_FRAME_TOTAL - 1)
    {
        current_throwing_frame = 0;
        action = STANDING;
    }
}

