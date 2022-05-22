#include "Character.h"

Character::Character()
{
    pos = {0, 0};
    is_forward = true;
    action = STANDING;
}
Character::Character(SDL_Point pos, bool is_forward)
{
    this->pos = pos;
    this->is_forward = is_forward;
    action = STANDING;
}

Character::~Character()
{
    const std::vector<ActionTypes> actionVector{
        DYING,
        STANDING,
        WALKING,
        LYING,
        CRAWLING,
        THROWING,
        JUMPING_UP,
        JUMPING_DOWN,
        CLIMBING_UP,
        CLIMBING_DOWN
    };
    for (auto a : actionVector)
    {
        actionTexture[a].free();
    }
}

SDL_Point Character::getPos()
{
    return pos;
}

bool Character::isForward()
{
    return is_forward;
}

int Character::getWidth()
{
    return WIDTH;
}

int Character::getHeight()
{
    return HEIGHT;
}

void Character::setPos(SDL_Point pos)
{
    this->pos = pos;
}

void Character::loadTextures(SDL_Renderer* gRenderer)
{
    actionTexture[DYING].loadFromFile(gRenderer, "res/sprites/ninja/dying.png");
    actionTexture[STANDING].loadFromFile( gRenderer, "res/sprites/ninja/standing.png" );
    actionTexture[WALKING].loadFromFile( gRenderer, "res/sprites/ninja/walking.png" );
    actionTexture[LYING].loadFromFile( gRenderer, "res/sprites/ninja/lying.png");
    actionTexture[CRAWLING].loadFromFile( gRenderer, "res/sprites/ninja/crawling.png");
    actionTexture[THROWING].loadFromFile( gRenderer, "res/sprites/ninja/throwing.png");
    actionTexture[JUMPING_UP].loadFromFile( gRenderer, "res/sprites/ninja/jumping_up.png");
    actionTexture[JUMPING_DOWN].loadFromFile( gRenderer, "res/sprites/ninja/jumping_down.png");
    actionTexture[CLIMBING_UP].loadFromFile( gRenderer, "res/sprites/ninja/climbing_up.png");
    actionTexture[CLIMBING_DOWN].loadFromFile( gRenderer, "res/sprites/ninja/climbing_down.png");


    const std::vector<ActionTypes> actionVector{
        DYING,
        STANDING,
        WALKING,
        LYING,
        CRAWLING,
        THROWING,
        JUMPING_UP,
        JUMPING_DOWN,
        CLIMBING_UP,
        CLIMBING_DOWN
    };
    for (auto a : actionVector)
    {
        for (int i = 0; i < textureClips[a].getTotalFrames(); i++)
        {
            textureClips[a].clips.push_back({WIDTH * i, 0, WIDTH, HEIGHT});
        }
    }

}

void Character::handleEvent(SDL_Event& event)
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
                //action = CLIMBING_UP; ///test
            }
            if (action == STANDING)
            {
                action = JUMPING_UP;
            }
            break;
        case SDLK_DOWN:
            if (action != DYING)
            {
                action = LYING;
            }
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
        case SDLK_UP:
            if (action == JUMPING_UP)
            {
                action = JUMPING_DOWN;
            }
            if (action == CLIMBING_UP)
            {
                action = CLIMBING_DOWN;
            }
            break;
        case SDLK_RIGHT:
            if (action == CRAWLING)
            {
                action = LYING;
            }
            if (action == WALKING)
            {
                action = STANDING;
            }
            break;

        case SDLK_LEFT:
            if (action == CRAWLING)
            {
                action = LYING;
            }
            if (action == WALKING)
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
        pos.x = std::min(pos.x + dx, SCREEN_WIDTH - 10);
    }
    else
    {
        pos.x = std::max(pos.x - dx, 0);
    }
    pos.y += dy;
}

void Character::renderAction(SDL_Renderer* gRenderer)
{

    switch (action)
    {
    case DYING:
        break;
    case STANDING:
        break;
    case WALKING:
        move(5, 0);
        break;
    case LYING:
        break;
    case CRAWLING:
        move(3, 0);
        break;
    case THROWING:
        if (textureClips[action].getCurrentFrame() / 3 == textureClips[action].getTotalFrames() - 1)
        {
            textureClips[action].resetFrame();
            action = STANDING;
            return;
        }
        break;
    case JUMPING_UP:
        move(0, 10);
        if (textureClips[action].getCurrentFrame() / 3 == textureClips[action].getTotalFrames() - 1)
        {
            textureClips[action].resetFrame();
            action = JUMPING_DOWN;
        }
        break;
    case JUMPING_DOWN:
        move(0, -10);
        break;

    case CLIMBING_UP:
        move(0, 2);
        break;
    case CLIMBING_DOWN:
        move(0, -2);
        break;
    }

    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    actionTexture[action].render(
            gRenderer, pos.x, SCREEN_HEIGHT - pos.y,
            &textureClips[action].clips[textureClips[action].getCurrentFrame() / 3],
            0.0, NULL, flipType);

    textureClips[action].nextFrame();

    if (textureClips[action].getCurrentFrame() / 3 == textureClips[action].getTotalFrames())
    {
        textureClips[action].resetFrame();
    }
}


