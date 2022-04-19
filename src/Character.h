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

class Character
{
    const int MAX_BLOOD = 1000;
    int posX, posY;
    int blood;
    bool is_forward;
    //bool is_walking;
    //bool is_idle;
public:
    enum CharacterAction {
        STANDING,
        WALKING,
        JUMPING
    };
    CharacterAction action = STANDING;

    Character();
    Character(int _posX, int _posY, bool _is_forward = true);
    void handleAction(SDL_Event& event);
    void move(int dx, int dy);

    int getPosX();
    int getPosY();
    bool isForward();
};

#endif // CHARACTER__H_
