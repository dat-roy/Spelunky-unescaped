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

class Bullet {
    int initPosX, initPosY;
    int posX, posY;
    int velX, velY;
    int initVel;
public:
    //The dimensions of the dot
    const int BULLET_WIDTH = 30;
    const int BULLET_HEIGHT = 30;
    //Gravity constant
    const double GRAVITY = 9.8;
    //Maximum initial velocity
    const int MAX_INIT_VELOCITY = 100;

    Bullet();
    Bullet(int _posX, int _posY, int _velX = 0, int _velY = 0, int _initVel = 0);
    void handleEvent(SDL_Renderer* &gRenderer, LTexture &gPointerTexture, SDL_Event& e, int& mouseX, int& mouseY, bool& mouseDown, bool& mousePressed);

    double getTimeOfMotion(const double &alpha);
    void projectileMotion(SDL_Renderer* &gRenderer, LTexture &gBulletTexture,
                          double &alpha, double &time,
                          bool& quitGame);
    void updateState(double alpha, double time);
    void render(SDL_Renderer* &gRenderer, LTexture &gBulletTexture, double alpha);

    int getPosX() {return posX;}
    int getPosY() {return posY;}
    int getVelX() {return velX;}
    int getVelY() {return velY;}
};

#endif // MY_DOT__H_
