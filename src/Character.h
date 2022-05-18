#ifndef CHARACTER__H_
#define CHARACTER__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include "Global.h"
#include "Texture.h"
#include "TextureClips.h"

class Character
{
    const int MAX_BLOOD = 1000;
    int posX, posY;
    int blood;
    bool is_forward;

    Texture standingTexture;
    Texture walkingTexture;
    Texture lyingTexture;
    Texture crawlingTexture;
    Texture throwingTexture;

    TextureClips walkingClips = TextureClips(9);
    TextureClips lyingClips = TextureClips(2);
    TextureClips crawlingClips = TextureClips(7);
    TextureClips throwingClips = TextureClips(7);

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
    Character(int posX, int posY, bool is_forward = true);
    ~Character();

    //Getter
    int getPosX();
    int getPosY();
    bool isForward();

    //Load textures
    void loadTextures(SDL_Renderer* &gRenderer);

    void handleAction(SDL_Event& event);
    void move(int dx, int dy);

    //Render graphics
    void renderStanding(SDL_Renderer* &gRenderer);
    void renderWalking(SDL_Renderer* &gRenderer);
    void renderLying(SDL_Renderer* &gRenderer);
    void renderCrawling(SDL_Renderer* &gRenderer);
    void renderThrowing(SDL_Renderer* &gRenderer);
};

#endif // CHARACTER__H_
