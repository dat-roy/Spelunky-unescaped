#include "Yetis.h"

Yetis::Yetis()
{
    SDL_Point pos = initPos = {0, 0};
    is_forward = false;
    action = WALKING;
}

Yetis::Yetis(SDL_Point pos, bool is_forward)
{
    this->initPos = this->pos = pos;
    this->is_forward = is_forward;
    action = WALKING;
}

Yetis::~Yetis()
{
    yetisTexture.free();
}

void Yetis::setFirstPosition(SDL_Point pos, bool is_forward)
{
    this->initPos = this->pos = pos;
    this->is_forward = is_forward;
}

void Yetis::loadTextures(SDL_Renderer* gRenderer, std::string path)
{
    yetisTexture.loadFromFile(gRenderer, path);

    for (int i = 0; i < textureClips[WALKING].getTotalFrames(); i++)
    {
        textureClips[WALKING].clips.push_back({WIDTH * i, 0, WIDTH, HEIGHT});
    }
    for (int i = 0; i < textureClips[ROARING].getTotalFrames(); i++)
    {
        textureClips[ROARING].clips.push_back({WIDTH * i, HEIGHT * 3, WIDTH, HEIGHT});
    }
}

void Yetis::move(int dx, int dy)
{
    pos.x += dx;
    pos.y += dy;
}

bool Yetis::meet(SDL_Rect character_rect)
{
    return math::checkCollision(character_rect, {pos.x, pos.y, WIDTH, HEIGHT});
}

SDL_Point Yetis::getPos() {
    return pos;
}

void Yetis::renderAction(SDL_Renderer* gRenderer)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    yetisTexture.render(gRenderer, pos.x, SCREEN_HEIGHT - pos.y, &textureClips[action].clips[textureClips[action].getCurrentFrame() / 5], 0.0, NULL, flipType);
    textureClips[action].nextFrame();
    if (textureClips[action].getCurrentFrame() / 5 == textureClips[action].getTotalFrames())
    {
        textureClips[action].resetFrame();
    }

    if (action == WALKING)
    {
        if (is_forward) move(1, 0);
        else move(-1, 0);
    }

}



