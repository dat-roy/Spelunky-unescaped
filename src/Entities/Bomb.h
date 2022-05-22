#ifndef BOMB__H_
#define BOMB__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "../Global.h"
#include "../Tools/Texture.h"
#include "../Tools/TextureClips.h"
#include "../Entities/Character.h"

class Bomb {
    SDL_Point pos;
    SDL_Point initPos;
    int velX, velY;
    int initVel;
    double alpha;
    double time;
    double maxTime;
    bool is_moving = false;

    Texture bombTexture;
    Texture explodeTexture;

    TextureClips explodeClips = TextureClips(6);

public:
    const int WIDTH = 10;
    const int HEIGHT = 10;

    //Constructors & Destructors
    Bomb();
    Bomb(SDL_Point pos, int initVel = 100);
    ~Bomb();

    //Getters
    SDL_Point getPos();
    int getVelX();
    int getVelY();
    bool isMoving();
    double getTime();
    double getTimeOfMotion();

    //Setters
    void setInitPos(SDL_Point initPos);
    void setAlpha(double alpha);
    void setMoving(bool is_moving);
    void resetTime();

    //Load textures
    void loadTextures(SDL_Renderer* gRenderer);

    void handleEvent(SDL_Event& event, SDL_Point& mousePos, bool& mouseDown, bool& mousePressed);
    void computeTimeOfMotion();
    void projectileMotion(SDL_Renderer* gRenderer);
    void updateState();
    void updateTime(double dt);
    void renderBomb(SDL_Renderer* gRenderer);
    void renderExplosion(SDL_Renderer* gRenderer);
};

#endif // bomb__H_
