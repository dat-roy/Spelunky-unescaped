#ifndef ENEMY__H_
#define ENEMY__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "Global.h"
#include "LTexture.h"

const int SNAKE_CRAWLING_FRAME_TOTAL = 11;
const int SNAKE_ATTACKING_FRAME_TOTAL = 7;
class Enemy
{
    const int MAX_BLOOD = 1000;
    int posX, posY;
    int blood;
    bool is_forward;

    LTexture snakeTexture;
    SDL_Rect snakeCrawlingClips[SNAKE_CRAWLING_FRAME_TOTAL];
    int current_snake_crawling_frame;
    SDL_Rect snakeAttackingClips[SNAKE_ATTACKING_FRAME_TOTAL];
    int current_snake_attacking_frame;
public:
    enum CharacterAction {
        CRAWLING,
        ATTACKING
    };
    CharacterAction action = CRAWLING;

    //Constructors & Destructors
    Enemy();
    Enemy(int _posX, int _posY, bool _is_forward = true);
    ~Enemy();

    //Getters
    int getPosX();
    int getPosY();
    int getBlood();

    //Setters
    void setFirstPosition(int _posX, int _posY, bool _is_forward = true);

    //Load textures
    void loadTextures(SDL_Renderer* &gRenderer);

    //
    void move(int dx, int dy);
    void updateBlood(int db);

    //Render graphics
    void renderSnakeCrawling(SDL_Renderer* &gRenderer);
    void renderSnakeAttacking(SDL_Renderer* &gRenderer);
};

#endif // ENEMY__H_
