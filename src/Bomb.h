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
    double maxTime;
    bool endMove = false;

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
    const int MAX_INIT_VELOCITY = 100;

    //Constructors & Destructors
    Bomb();
    Bomb(int _posX, int _posY, int _velX = 0, int _velY = 0, int _initVel = 0);
    ~Bomb();
    //Getters
    int getPosX();
    int getPosY();
    int getVelX();
    int getVelY();
    bool getEndMove();
    double getTimeOfMotion();
    //Setters
    void setInitPosX(int _initPosX);
    void setInitPosY(int _initPosY);
    void setEndMove(bool _endMove);

    //Load textures
    void loadTextures(SDL_Renderer* &gRenderer);

    void handleEvent(SDL_Event& event, int& mouseX, int& mouseY, bool& mouseDown, bool& mousePressed);
    void computeTimeOfMotion(const double &alpha);
    void projectileMotion(SDL_Renderer* &gRenderer, double &alpha, double &time);
    void updateState(double alpha, double time);
    void renderbomb(SDL_Renderer* &gRenderer, double alpha);
    void renderArrow(SDL_Renderer* &gRenderer, int& mouseX, int& mouseY);
    void renderExplosion(SDL_Renderer* &gRenderer);
};

#endif // bomb__H_
