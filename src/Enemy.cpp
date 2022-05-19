#include "Enemy.h"

Enemy::Enemy()
{
    SDL_Point pos = {0, 0};
    is_forward = false;
    action = CRAWLING;
}

Enemy::Enemy(SDL_Point pos, bool is_forward)
{
    this->pos = pos;
    this->is_forward = is_forward;
    action = CRAWLING;
}

Enemy::~Enemy()
{
    snakeTexture.free();
}

void Enemy::setFirstPosition(SDL_Point pos, bool is_forward)
{
    this->pos = pos;
    this->is_forward = is_forward;
}

void Enemy::loadTextures(SDL_Renderer* gRenderer)
{
    snakeTexture.loadFromFile(gRenderer, "res/sprites/enemy/snake.png");
    for (int i = 0; i < textureClips[CRAWLING].getTotalFrames(); i++)
    {
        textureClips[CRAWLING].clips.push_back({95 * i, 0, 95, 95});
    }
    for (int i = 0; i < textureClips[ATTACKING].getTotalFrames(); i++)
    {
        textureClips[ATTACKING].clips.push_back({95 * i, 95, 95, 95});
    }
}

void Enemy::move(int dx, int dy)
{
    if (is_forward)
    {
        pos.x = std::min(pos.x + dx, SCREEN_WIDTH - 100);
        if (pos.x > 1200)
        {
            is_forward = false;
            action = CRAWLING;
        }
    }
    else
    {
        pos.x = std::max(pos.x - dx, 0);
        if (pos.x < 1000)
        {
            is_forward = true;
            action = CRAWLING;
        }
        if (pos.x < 1100 && is_forward == false)
        {
            action = ATTACKING;
        }
    }
    pos.y += dy;
}

SDL_Point Enemy::getPos() {
    return pos;
}

void Enemy::renderAction(SDL_Renderer* gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    snakeTexture.render(gRenderer, pos.x, SCREEN_HEIGHT - pos.y, &textureClips[action].clips[textureClips[action].getCurrentFrame() / 3], 0.0, NULL, flipType);
    textureClips[action].nextFrame();
    if (textureClips[action].getCurrentFrame() / 3 == textureClips[action].getTotalFrames())
    {
        textureClips[action].resetFrame();
    }
    move(1, 0);
}
