#include "Button.h"

Button::Button() : btn({0,0,0,0}) {};

Button::Button(const SDL_Rect btn) : btn(btn) {};

Button::~Button()
{
    buttonTexture.free();
}


void Button::handleEvent(SDL_Event& event, SDL_Point& mousePos)
{
    //If mouse event happened
    if( event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP )
    {
        SDL_GetMouseState( &mousePos.x, &mousePos.y );

        //Mouse is left of the button
        if( mousePos.x < btn.x )
        {
            selected = false;
        }
        //Mouse is right of the button
        else if( mousePos.x > btn.x + btn.w )
        {
            selected = false;
        }
        //Mouse above the button
        else if( mousePos.y < SCREEN_HEIGHT - btn.y )
        {
            selected = false;
        }
        //Mouse below the button
        else if( mousePos.y > SCREEN_HEIGHT - btn.y + btn.h )
        {
            selected = false;
        } else {
            selected = true;
        }
    }
}

bool Button::isSelected()
{
    return selected;
}

void Button::setSelected(bool selected)
{
    this->selected = selected;
}

void Button::loadTextures(SDL_Renderer* gRenderer)
{
    buttonTexture.loadFromFile(gRenderer, "res/img/button.png");
}

void Button::renderButton(SDL_Renderer* gRenderer)
{
    buttonTexture.render(gRenderer, btn.x, SCREEN_HEIGHT - btn.y);
}
