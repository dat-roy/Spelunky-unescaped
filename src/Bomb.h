#ifndef BOMB__H_
#define BOMB__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "Global.h"
#include "Texture.h"
#include "TextureClips.h"
#include "Character.h"

class Bomb {
    int initPosX, initPosY;
    int posX, posY;
    int velX, velY;
    int initVel;
    double alpha;
    double time;
    double maxTime;
    bool is_moving = false;

    Texture bombTexture;
    Texture arrowTexture;
    Texture explodeTexture;

    TextureClips explodeClips = TextureClips(6);

public:
    const int BOMB_WIDTH = 30;
    const int BOMB_HEIGHT = 30;
    //Gravity constant
    const double GRAVITY = 9.8;
    //Maximum initial velocity
    const int MAX_INIT_VELOCITY = 120;

    //Constructors & Destructors
    Bomb();
    Bomb(int posX, int posY, int velX = 0, int velY = 0, int initVel = 0);
    ~Bomb();
    //Getters
    int getPosX();
    int getPosY();
    int getVelX();
    int getVelY();
    bool isMoving();
    double getTime();
    double getTimeOfMotion();
    //Setters
    void setInitPosX(int initPosX);
    void setInitPosY(int initPosY);
    void setAlpha(double alpha);
    void setMoving(bool is_moving);
    void resetTime();

    //Load textures
    void loadTextures(SDL_Renderer* &gRenderer);

    void handleEvent(SDL_Event& event, int& mouseX, int& mouseY, bool& mouseDown, bool& mousePressed);
    void computeTimeOfMotion();
    void projectileMotion(SDL_Renderer* &gRenderer);
    void updateState();
    void updateTime(double dt);
    void renderBomb(SDL_Renderer* &gRenderer);
    void renderArrow(SDL_Renderer* &gRenderer, int& mouseX, int& mouseY);
    void renderExplosion(SDL_Renderer* &gRenderer);
};

#endif // bomb__H_
