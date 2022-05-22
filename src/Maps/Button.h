#ifndef BUTTON__H_
#define BUTTON__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

#include "../Global.h"
#include "../Tools/Texture.h"

class Button {
    const SDL_Rect btn;
    Texture buttonTexture;

    bool selected = false;
public:

    Button();
    Button(SDL_Rect btn);
    ~Button();

    int getWidth();
    int getHeight();

    bool isSelected();
    void setSelected(bool selected);
    void handleEvent(SDL_Event& event, SDL_Point& mousePos);
    void loadTextures(SDL_Renderer* gRenderer);
    void renderButton(SDL_Renderer* gRenderer);

};

#endif // BUTTON__H_
