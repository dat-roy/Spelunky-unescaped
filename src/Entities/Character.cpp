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
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            switch (action)
            {
            case LYING:
                action = STANDING;
                break;
            case STANDING:
                action = JUMPING_UP;
                vel_y = 8;
                break;
            case CLIMBING_DOWN:
                action = CLIMBING_UP;
                vel_y = 2;
                break;
            }
            break;

        case SDLK_DOWN:
            if (action == STANDING)
            {
                action = LYING;
                vel_x = 0;
                vel_y = 0;
            }
            break;
        case SDLK_RIGHT:
            is_forward = true;
            if (action == STANDING)
            {
                action = WALKING;
                vel_x = 4;
            }
            if (action == LYING)
            {
                action = CRAWLING;
                vel_x = 2;
                vel_y = 0;
            }
            if (action == JUMPING_UP || action == JUMPING_DOWN)
            {
                vel_x = 5;
            }
            if (action == CLIMBING_DOWN)
            {
                action = WALKING;
                vel_x = 4;
                vel_y = 0;
                is_forward = true;
            }
            break;

        case SDLK_LEFT:
            is_forward = false;
            if (action == STANDING)
            {
                action = WALKING;
                vel_x = -4;
            }
            if (action == LYING)
            {
                action = CRAWLING;
                vel_x = -2;
                vel_y = 0;
            }
            if (action == JUMPING_UP || action == JUMPING_DOWN)
            {
                vel_x = -5;
            }
            if (action == CLIMBING_DOWN)
            {
                action = WALKING;
                is_forward = false;
            }
            break;
        }
    }
    else
    if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
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

            if (vel_y > 0) vel_y = 0;
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
            if (vel_x > 0) vel_x = 0;
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
            if (vel_x < 0) vel_x = 0;
            break;
        }
    }
}

void Character::move(int dx, int dy)
{
    if (is_forward)
    {
        pos.x = pos.x + dx;
    }
    else
    {
        pos.x = std::max(pos.x + dx, 0);
    }
    pos.y += dy;
    if (pos.y < 0) {pos.y = HEIGHT; action = STANDING;}
    if (pos.y > SCREEN_HEIGHT) pos.y = SCREEN_HEIGHT - HEIGHT;
}

void Character::setCamera(SDL_Rect& camera)
{
    //Center the camera
    camera.x = ( pos.x + WIDTH / 2 ) - SCREEN_WIDTH / 2;
    camera.y = ( pos.y + HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

    //Keep the camera in bounds
    if( camera.x < 0 )
    {
        camera.x = 0;
    }
    if( camera.y < 0 )
    {
        camera.y = 0;
    }
    if( camera.x > LEVEL_WIDTH - camera.w )
    {
        camera.x = LEVEL_WIDTH - camera.w;
    }
    if( camera.y > LEVEL_HEIGHT - camera.h )
    {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

void Character::controlAction(const std::vector<std::vector<int>>& tileValue, int TILE_ROW, int TILE_COL, GameState& gameState)
{
    move(vel_x, vel_y);
    switch (action)
    {
    case THROWING:
        if (textureClips[action].getCurrentFrame() / 4 == textureClips[action].getTotalFrames() - 1)
        {
            textureClips[action].resetFrame();
            action = STANDING;
            return;
        }
        break;
    case JUMPING_UP:
        if (textureClips[action].getCurrentFrame() / 4 == textureClips[action].getTotalFrames() - 1)
        {
            textureClips[action].resetFrame();
            action = JUMPING_DOWN;
        }
        break;
    case JUMPING_DOWN:
        move(0, -5);
        break;
    case CLIMBING_DOWN:
        move(0, -8);
        break;
    }

    for (int i = 1; i <= TILE_ROW; i++)
    {
        for (int j = 1; j <= TILE_COL; j++)
        {
            SDL_Rect tile_rect;
            tile_rect.x = (j - 1) * TILE_WIDTH;
            tile_rect.y = (TILE_ROW - i + 1) * TILE_HEIGHT;
            tile_rect.w = TILE_WIDTH;
            tile_rect.h = TILE_HEIGHT;

            SDL_Rect character_rect;
            character_rect.x = pos.x;
            character_rect.y = pos.y;
            character_rect.w = WIDTH;
            character_rect.h = HEIGHT;


            //Check tiles under character?
            if (math::checkCollision({pos.x, pos.y - TILE_HEIGHT, WIDTH, HEIGHT}, tile_rect))
            {
                //If it is a soil tile
                if (tiles::isSoil(tileValue[i][j]))
                {
                    if (action == JUMPING_DOWN)
                    {
                        action = STANDING;
                        pos.y = tile_rect.y + HEIGHT;
                        break;
                    }
                    if (action == CLIMBING_DOWN)
                    {
                        pos.y = tile_rect.y + HEIGHT;
                    }
                }
            }

            //Check into a door
            if (math::checkCollision({pos.x, pos.y, WIDTH, HEIGHT}, tile_rect))
            {
                if (tiles::isDoor(tileValue[i][j]))
                {
                    if (gameState == RUNNING_LEVEL_1)
                    {
                        gameState = RUNNING_LEVEL_2;
                    }
                    else if (gameState == RUNNING_LEVEL_2)
                    {
                        gameState = WINNING;
                    }
                    return;
                }
            }

            //Check in ladder or not?
            if (math::checkCenter(character_rect, tile_rect))
            {
                if (tiles::isLadder(tileValue[i][j]))
                {
                    if (action != CLIMBING_UP)
                    {
                        action = CLIMBING_DOWN;
                    }
                }
            }
        }
    }
}


void Character::renderAction(SDL_Renderer* gRenderer, SDL_Rect camera)
{
    SDL_RendererFlip flipType = (is_forward) ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    actionTexture[action].render(
            gRenderer, pos.x - camera.x, SCREEN_HEIGHT - pos.y - camera.y,
            &textureClips[action].clips[textureClips[action].getCurrentFrame() / 4],
            0.0, NULL, flipType);

    textureClips[action].nextFrame();

    if (textureClips[action].getCurrentFrame() / 4 == textureClips[action].getTotalFrames())
    {
        textureClips[action].resetFrame();
    }
}

