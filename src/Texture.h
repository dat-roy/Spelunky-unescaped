#ifndef Texture__H_
#define Texture__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>


//Texture wrapper class
class Texture
{
public:
    Texture();
    Texture(int _total);
    ~Texture();

    //Loads image at specified path
    bool loadFromFile( SDL_Renderer* &gRenderer, std::string path );

    //Creates image from font string
    bool loadFromRenderedText(
                              SDL_Renderer* &gRenderer,
                              std::string textureText,
                              TTF_Font* gFont,
                              SDL_Color textColor
                              );

    //Deallocates texture
    void free();

    //Set color modulation
    void setColor( uint8_t red, uint8_t green, uint8_t blue );

    //Set blending
    void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
    void setAlpha( uint8_t alpha );

    //Renders texture at given point
    void render(
                SDL_Renderer* &gRenderer,
                int x,
                int y,
                SDL_Rect* clip = NULL,
                double angle = 0.0,
                SDL_Point* center = NULL,
                SDL_RendererFlip flip = SDL_FLIP_NONE
                );

    //Gets image dimensions
    int getWidth();
    int getHeight();

private:
    //The actual hardware texture
    SDL_Texture* mTexture;

    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif // Texture__H_



