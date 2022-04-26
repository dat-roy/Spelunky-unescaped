#include "Enemy.h"

Enemy::Enemy()
{
    posX = 0;
    posY = 0;
    is_forward = false;
    current_snake_crawling_frame = 0;
    current_snake_attacking_frame = 0;
    blood = MAX_BLOOD;
}

Enemy::Enemy(int _posX, int _posY, bool _is_forward)
{
    posX = _posX;
    posY = _posY;
    is_forward = _is_forward;
    current_snake_crawling_frame = 0;
    current_snake_attacking_frame = 0;
    blood = MAX_BLOOD;
}

Enemy::~Enemy()
{
    snakeTexture.free();
}

void Enemy::setFirstPosition(int _posX, int _posY, bool _is_forward)
{
    posX = _posX;
    posY = _posY;
    is_forward = _is_forward;
}

void Enemy::loadTextures(SDL_Renderer* &gRenderer)
{
    snakeTexture.loadFromFile(gRenderer, "res/sprites/enemy/snake.png");
    for (int i = 0; i < SNAKE_CRAWLING_FRAME_TOTAL; i++)
    {
        snakeCrawlingClips[i] = {95 * i, 0, 95, 95};
    }
    for (int i = 0; i < SNAKE_ATTACKING_FRAME_TOTAL; i++)
    {
        snakeAttackingClips[i] = {96 * i, 95, 96, 95};
    }
}

void Enemy::move(int dx, int dy)
{
    if (is_forward)
    {
        posX = std::min(posX + dx, SCREEN_WIDTH - 100);
        if (posX > 1200)
        {
            is_forward = false;
            action = CRAWLING;
        }
    }
    else
    {
        posX = std::max(posX - dx, 0);
        if (posX < 1000)
        {
            is_forward = true;
            action = CRAWLING;
        }
        if (posX < 1100 && is_forward == false)
        {
            action = ATTACKING;
        }
    }
    posY += dy;
}

int Enemy::getPosX() {
    return posX;
}

int Enemy::getPosY() {
    return posY;
}

int Enemy::getBlood() {
    return blood;
}

void Enemy::updateBlood(int db) {
    blood = std::max(blood + db, 0);
}

void Enemy::renderSnakeCrawling(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    snakeTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY + 7, &snakeCrawlingClips[current_snake_crawling_frame / 3], 0.0, NULL, flipType);
    current_snake_crawling_frame++;
    if (current_snake_crawling_frame / 3 == SNAKE_CRAWLING_FRAME_TOTAL)
    {
        current_snake_crawling_frame = 0;
    }
}

void Enemy::renderSnakeAttacking(SDL_Renderer* &gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    snakeTexture.render(gRenderer, posX, SCREEN_HEIGHT - posY, &snakeAttackingClips[current_snake_attacking_frame / 5], 0.0, NULL, flipType);
    current_snake_attacking_frame++;
    if (current_snake_attacking_frame / 5 == SNAKE_ATTACKING_FRAME_TOTAL)
    {
        current_snake_attacking_frame = 0;
    }
}
