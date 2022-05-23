#include "Snake.h"

Snake::Snake()
{
    SDL_Point pos = initPos = {0, 0};
    is_forward = false;
    action = CRAWLING;
}

Snake::Snake(SDL_Point pos, bool is_forward)
{
    this->initPos = this->pos = pos;
    this->is_forward = is_forward;
    action = CRAWLING;
}

Snake::~Snake()
{
    snakeTexture.free();
}

void Snake::setFirstPosition(SDL_Point pos, bool is_forward)
{
    this->initPos = this->pos = pos;
    this->is_forward = is_forward;
}

void Snake::loadTextures(SDL_Renderer* gRenderer, std::string path)
{
    snakeTexture.loadFromFile(gRenderer, path);
    for (int i = 0; i < textureClips[CRAWLING].getTotalFrames(); i++)
    {
        textureClips[CRAWLING].clips.push_back({WIDTH * i, 0, WIDTH, HEIGHT});
    }
    for (int i = 0; i < textureClips[ATTACKING].getTotalFrames(); i++)
    {
        textureClips[ATTACKING].clips.push_back({WIDTH * i, HEIGHT, WIDTH, HEIGHT});
    }
}

void Snake::move(int dx, int dy)
{
    if (is_forward)
    {
        pos.x = std::min(pos.x + dx, SCREEN_WIDTH - WIDTH);
        if (pos.x == SCREEN_WIDTH - WIDTH)
        {
            is_forward = false;
            action = CRAWLING;
        }
    }
    else
    {
        //pos.x = std::max(pos.x - dx, 0);
        pos.x = pos.x - dx;
        if (initPos.x - pos.x > 300)
        {
            action = ATTACKING;
        }
    }
    pos.y += dy;
}

bool Snake::meet(SDL_Rect character_rect)
{
    return math::checkCollision(character_rect, {pos.x, pos.y, WIDTH, HEIGHT});
}

SDL_Point Snake::getPos() {
    return pos;
}

void Snake::renderAction(SDL_Renderer* gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    snakeTexture.render(gRenderer, pos.x, SCREEN_HEIGHT - pos.y, &textureClips[action].clips[textureClips[action].getCurrentFrame() / 3], 0.0, NULL, flipType);
    textureClips[action].nextFrame();
    if (textureClips[action].getCurrentFrame() / 3 == textureClips[action].getTotalFrames())
    {
        textureClips[action].resetFrame();
    }
    move(3, 0);
}
