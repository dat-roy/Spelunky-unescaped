#include "Button.h"

Button::Button()
{
    buttonPos = {0, 0};
}

void Button::loadTextures(SDL_Renderer* gRenderer)
{
    buttonTexture.loadFromFile(gRenderer, "res/img/button.png");
}

void Button::renderButton(SDL_Renderer* gRenderer)
{
    //buttonTexture.render
}
