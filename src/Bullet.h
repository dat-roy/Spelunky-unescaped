#ifndef MY_DOT__H_
#define MY_DOT__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "Global.h"
#include "LTexture.h"
#include "Character.h"

class Bullet {
    int initPosX, initPosY;
    int posX, posY;
    int velX, velY;
    int initVel;
    bool endMove = false;
public:
    const int BULLET_WIDTH = 30;
    const int BULLET_HEIGHT = 30;
    //Gravity constant
    const double GRAVITY = 9.8;
    //Maximum initial velocity
    const int MAX_INIT_VELOCITY = 100;

    Bullet();
    Bullet(int _posX, int _posY, int _velX = 0, int _velY = 0, int _initVel = 0);
    void handleEvent(SDL_Event& event, int& mouseX, int& mouseY, bool& mouseDown, bool& mousePressed);

    double getTimeOfMotion(const double &alpha);
    void projectileMotion(SDL_Renderer* &gRenderer, LTexture &gBulletTexture,
                          double &alpha, double &time);
    void updateState(double alpha, double time);
    void render(SDL_Renderer* &gRenderer, LTexture &gArrowTexture, double alpha);
    void renderArrow(SDL_Renderer* &gRenderer, LTexture &gArrowTexture, int& mouseX, int& mouseY);

    int getPosX();
    int getPosY();
    int getVelX();
    int getVelY();
    bool getEndMove();

    void setInitPosX(int _initPosX);
    void setInitPosY(int _initPosY);
    void setEndMove(bool _endMove);
};

#endif // MY_DOT__H_
