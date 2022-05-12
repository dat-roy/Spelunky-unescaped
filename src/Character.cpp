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
    standingTexture.loadFromFile( gRenderer, "res/sprites/ninja/standing.png" );
    walkingTexture.loadFromFile( gRenderer, "res/sprites/ninja/walking.png" );
    for (int i = 0; i < walkingClips.getTotalFrames(); i++)
    {
        walkingClips.clips.push_back({116 * i, 0, 116, 116});
    }
    lyingTexture.loadFromFile( gRenderer, "res/sprites/ninja/lying.png");
    for (int i = 0; i < lyingClips.getTotalFrames(); i++)
    {
        lyingClips.clips.push_back({116 * i, 0, 116, 116});
    }
    crawlingTexture.loadFromFile( gRenderer, "res/sprites/ninja/crawling.png");
    for (int i = 0; i < crawlingClips.getTotalFrames(); i++)
    {
        crawlingClips.clips.push_back({121 * i, 0, 121, 116});
    }
    throwingTexture.loadFromFile( gRenderer, "res/sprites/ninja/throwing.png");
    for (int i = 0; i < throwingClips.getTotalFrames(); i++)
    {
        throwingClips.clips.push_back({116 * i, 0, 116, 116});
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
    walkingTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY, &walkingClips.clips[walkingClips.getCurrentFrame() / 4], 0.0, NULL, flipType);
    walkingClips.nextFrame();
    if (walkingClips.getCurrentFrame() / 4 == walkingClips.getTotalFrames())
    {
        walkingClips.resetFrame();
    }
}

void Character::renderLying(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    lyingTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY + 8, &lyingClips.clips[lyingClips.getCurrentFrame()], 0.0, NULL, flipType);
    if (lyingClips.getCurrentFrame() < lyingClips.getTotalFrames() - 1)
    {
        lyingClips.nextFrame();
    }
}

void Character::renderCrawling(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    crawlingTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY + 8, &crawlingClips.clips[crawlingClips.getCurrentFrame() / 3], 0.0, NULL, flipType);
    crawlingClips.nextFrame();
    if (crawlingClips.getCurrentFrame() / 3 == crawlingClips.getTotalFrames())
    {
        crawlingClips.resetFrame();
    }
}

void Character::renderThrowing(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    throwingTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY, &throwingClips.clips[throwingClips.getCurrentFrame() / 4], 0.0, NULL, flipType);
    if (throwingClips.getCurrentFrame() / 4 < throwingClips.getTotalFrames() - 1)
    {
        throwingClips.nextFrame();

    }
    if (throwingClips.getCurrentFrame() / 4 == throwingClips.getTotalFrames() - 1)
    {
        throwingClips.resetFrame();
        action = STANDING;
    }
}

