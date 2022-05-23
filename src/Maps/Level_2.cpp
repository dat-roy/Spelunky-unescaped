#include "Level_2.h"

Level_2::Level_2() {};
Level_2::~Level_2() {};

void Level_2::display(SDL_Renderer* gRenderer, GameState& gameState, TTF_Font* gFont24, TTF_Font* gFont32, TTF_Font* gFont48)
{

    ///Camera
    SDL_Rect camera;
    camera.x = 0;
    camera.y = 0;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;

    ///Characters
    Character character({100, 64 * 2 + 117}, true);
    character.loadTextures(gRenderer);

    ///Weapon
    Bomb bomb(character.getPos());
    bomb.loadTextures(gRenderer);

    ///Enemies
    std::vector<Snake*> snakes;
    for (int i = 0; i < 5; i++) snakes.push_back(new Snake);
    snakes[0]->setFirstPosition({500, 64 * 2 + 95 - 5}, true);
    snakes[1]->setFirstPosition({900, 64 * 2 + 95 - 5}, false);
    snakes[2]->setFirstPosition({1000, 64 * 2 + 95 - 5}, true);
    snakes[3]->setFirstPosition({1300, 64 * 2 + 95 - 5}, false);
    snakes[4]->setFirstPosition({1500, 64 * 2 + 95 - 5}, true);

    for (auto &snake : snakes)
    {
        snake->loadTextures(gRenderer, "res/sprites/enemy/snake.png");
    }

    Yetis yetis;
    yetis.setFirstPosition({2000, 64 * 2 + 166 - 5}, false);
    yetis.loadTextures(gRenderer, "res/sprites/enemy/yetis.png");

    ///Level 2
    Map level_2;
    level_2.setBackgroundPath("res/img/bg9.jpg");
    level_2.setTilesetPath("res/map/tileset_2.png");
    level_2.loadTextures(gRenderer);
    level_2.loadTiles(gRenderer, "res/map/tileset_2.map");

    SDL_Event event;

    ///Mouse position
    SDL_Point mousePos = {0, 0};
    bool mouseDown = false;
    bool mousePressed = false;

    while (gameState == RUNNING_LEVEL_2)
    {
        if (character.action == DYING)
        {
            gameState = GAMEOVER;
            return;
        }
        while( SDL_PollEvent( &event ) != 0 && ! bomb.isMoving())
        {
            if (event.type == SDL_QUIT)
            {
                gameState = QUITING;
                break;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_a) {
                    gameState = MAIN_MENU;
                }
            }
            character.handleEvent(event);
            bomb.handleEvent(event, mousePos, mouseDown, mousePressed);
        }

        level_2.renderBackground(gRenderer);
        level_2.renderTiles(gRenderer, camera);
        level_2.renderBorder(gRenderer, camera);


        character.controlAction(level_2.tileValue, level_2.TILE_ROW, level_2.TILE_COL, gameState);

        character.setCamera(camera);
        character.renderAction(gRenderer, camera);

        yetis.renderAction(gRenderer);
        if (yetis.meet({character.getPos().x, character.getPos().y, character.getWidth() - 50, character.getHeight() - 50}))
        {
            character.action = DYING;
        }

        for (auto &snake : snakes)
        {
            if (snake == nullptr) continue;

            snake->renderAction(gRenderer);
            if (snake->meet({character.getPos().x, character.getPos().y, character.getWidth() - 50, character.getHeight() - 50}))
            {
                character.action = DYING;
            }
        }

        ///Bomb controller
        if (mouseDown && mousePressed)
        {
            character.action = STANDING;
        }
        if (!mouseDown && mousePressed && ! bomb.isMoving())
        {
            character.action = THROWING;
        }

        if (mousePressed == true && mouseDown == false && !bomb.isMoving())
        {
            bomb.setInitPos(character.getPos());

            double alpha = atan(1.0 * std::abs(mousePos.y - SCREEN_HEIGHT + character.getPos().y) / std::abs(mousePos.x - character.getPos().x));
            bomb.setAlpha(alpha);

            bomb.resetTime();
            //bomb.computeTimeOfMotion();
            bomb.setMoving(true);
        }

        if (mousePressed == true && mouseDown == false && bomb.isMoving())
        {
            bomb.updateTime(0.15);
//            if (bomb.getTime() > bomb.getTimeOfMotion())
//            {
//                bomb.setMoving(false);
//                bomb.resetTime();
//                character.action = STANDING;
//                mousePressed = false;
//            }

            if (bomb.meetBarrier(level_2.tileValue, level_2.TILE_ROW, level_2.TILE_COL))
            {
                bomb.setMoving(false);
                bomb.resetTime();
                character.action = STANDING;
                mousePressed = false;
            }
            if (bomb.isMoving() == false)
            {
                bomb.renderExplosion(gRenderer, camera);
            }

            for (auto &snake : snakes)
            {
                if (snake == nullptr) continue;
                if (snake->meet({bomb.getPos().x, bomb.getPos().y, bomb.WIDTH, bomb.HEIGHT}))
                {
                        bomb.renderExplosion(gRenderer, camera);
                        delete snake;
                        snake = nullptr;
                }
            }
            /*if (std::count(snakes.begin(), snakes.end(), nullptr) == (int)snakes.size())
            {
                //gameState = WINNING;
                //return;
            }
            else
            */
                bomb.projectileMotion(gRenderer, camera);

        }
        SDL_RenderPresent(gRenderer);
    }
}
