#ifndef CHARACTER__H_
#define CHARACTER__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "Global.h"
#include "LTexture.h"

const int WALKING_FRAME_TOTAL = 9;
const int LYING_FRAME_TOTAL = 2;
const int CRAWLING_FRAME_TOTAL = 7;
const int THROWING_FRAME_TOTAL = 7;

class Character
{
    const int MAX_BLOOD = 1000;
    int posX, posY;
    int blood;
    bool is_forward;

    LTexture standingTexture;
    LTexture walkingTexture;
    SDL_Rect walkingClips[WALKING_FRAME_TOTAL];
    int current_walking_frame;
    LTexture lyingTexture;
    SDL_Rect lyingClips[LYING_FRAME_TOTAL];
    int current_lying_frame;
    LTexture crawlingTexture;
    SDL_Rect crawlingClips[CRAWLING_FRAME_TOTAL];
    int current_crawling_frame;
    LTexture throwingTexture;
    SDL_Rect throwingClips[THROWING_FRAME_TOTAL];
    int current_throwing_frame;

public:
    enum CharacterAction {
        STANDING,
        WALKING,
        LYING,
        CRAWLING,
        THROWING
    };
    CharacterAction action = STANDING;

    //Constructors & Destructors
    Character();
    Character(int _posX, int _posY, bool _is_forward = true);
    ~Character();

    //Getter
    int getPosX();
    int getPosY();
    bool isForward();

    //Load textures
    void loadTextures(SDL_Renderer* &gRenderer);

    void handleAction(SDL_Event& event);
    void move(int dx, int dy);

    void renderStanding(SDL_Renderer* &gRenderer);
    void renderWalking(SDL_Renderer* &gRenderer);
    void renderLying(SDL_Renderer* &gRenderer);
    void renderCrawling(SDL_Renderer* &gRenderer);
    void renderThrowing(SDL_Renderer* &gRenderer);
};

#endif // CHARACTER__H_
