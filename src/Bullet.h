#ifndef BULLET__H_
#define BULLET__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <cmath>

#include "Global.h"
#include "LTexture.h"
#include "Character.h"

const int EXPLOSION_FRAME_TOTAL = 6;
class Bullet {
    int initPosX, initPosY;
    int posX, posY;
    int velX, velY;
    int initVel;
    double maxTime;
    bool endMove = false;

    LTexture bulletTexture;
    LTexture arrowTexture;
    LTexture explodeTexture;
    SDL_Rect explodeClips[EXPLOSION_FRAME_TOTAL];
    int current_explosion_frame;
public:
    const int BULLET_WIDTH = 30;
    const int BULLET_HEIGHT = 30;
    //Gravity constant
    const double GRAVITY = 9.8;
    //Maximum initial velocity
    const int MAX_INIT_VELOCITY = 100;

    //Constructors & Destructors
    Bullet();
    Bullet(int _posX, int _posY, int _velX = 0, int _velY = 0, int _initVel = 0);
    ~Bullet();
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
    void renderBullet(SDL_Renderer* &gRenderer, double alpha);
    void renderArrow(SDL_Renderer* &gRenderer, int& mouseX, int& mouseY);
    void renderExplosion(SDL_Renderer* &gRenderer);
};

#endif // BULLET__H_
