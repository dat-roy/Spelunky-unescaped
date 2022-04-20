#include "Enemy.h"

Enemy::Enemy()
{
    posX = 0;
    posY = 0;
    is_forward = false;
    current_snake_frame = 0;
}

Enemy::Enemy(int _posX, int _posY, bool _is_forward)
{
    posX = _posX;
    posY = _posY;
    is_forward = _is_forward;
    current_snake_frame = 0;
}

Enemy::~Enemy()
{
    snakeTexture.free();
}

void Enemy::loadTextures(SDL_Renderer* &gRenderer)
{
    snakeTexture.loadFromFile(gRenderer, "res/sprites/snake.png");
    for (int i = 0; i < SNAKE_FRAME_TOTAL; i++)
    {
        snakeClips[i] = {79 * i, 0, 79, 76};
    }
}

void Enemy::move(int dx, int dy)
{
    if (is_forward)
    {
        posX = std::min(posX + dx, SCREEN_WIDTH - 100);
        if (posX > SCREEN_WIDTH - 400)
            is_forward = false;
    }
    else
    {
        posX = std::max(posX - dx, 0);
        if (posX < 800)
            is_forward = true;
    }
    posY += dy;
}

void Enemy::renderSnake(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    snakeTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY + 7, &snakeClips[current_snake_frame / 2], 0.0, NULL, flipType);
    current_snake_frame++;
    if (current_snake_frame == SNAKE_FRAME_TOTAL)
    {
        current_snake_frame = 0;
    }
}
