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
#include <map>

#include "Global.h"
#include "Texture.h"
#include "TextureClips.h"

class Character
{
    SDL_Point pos;
    bool is_forward;
    int HEIGHT = 117;
    int WIDTH = 117;

    std::map<ActionTypes, Texture> actionTexture =
    {
        { DYING, Texture() },
        { STANDING, Texture() },
        { WALKING, Texture() },
        { LYING, Texture() },
        { CRAWLING, Texture() },
        { THROWING, Texture() },
        { JUMPING_UP, Texture() },
        { JUMPING_DOWN, Texture() },
        { CLIMBING_UP, Texture() },
        { CLIMBING_DOWN, Texture() }
    };

    std::map<ActionTypes, TextureClips> textureClips =
    {
        { DYING, TextureClips(1) },
        { STANDING, TextureClips(1) },
        { WALKING, TextureClips(9) },
        { LYING, TextureClips(1) },
        { CRAWLING, TextureClips(7) },
        { THROWING, TextureClips(10) },
        { JUMPING_UP, TextureClips(6) },
        { JUMPING_DOWN, TextureClips(6) },
        { CLIMBING_UP, TextureClips(10) },
        { CLIMBING_DOWN, TextureClips(1) }
    };

public:
    ActionTypes action;

    //Constructors & Destructors
    Character();
    Character(SDL_Point pos, bool is_forward = true);
    ~Character();

    //Getter
    SDL_Point getPos();
    bool isForward();
    int getWidth();
    int getHeight();

    //Setter
    void setPos(SDL_Point pos);

    //Load textures
    void loadTextures(SDL_Renderer* gRenderer);

    void handleEvent(SDL_Event& event);
    void move(int dx, int dy);

    //Centers the camera
    void setCamera(SDL_Rect& camera);

    //Render graphics
    void renderAction(SDL_Renderer* gRenderer);
};

#endif // CHARACTER__H_
