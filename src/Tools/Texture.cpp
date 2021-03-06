#include "Texture.h"

Texture::Texture()
{
    //Initialize
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture()
{
    //Deallocate
    free();
}

bool Texture::loadFromFile( SDL_Renderer* gRenderer, std::string path )
{
    //Get rid of preexisting texture
    free();
    //The final texture
    SDL_Texture* newTexture = NULL;
    try
    {
        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );

        if( loadedSurface == NULL )
        {
            throw path.c_str();
            throw IMG_GetError();
        }
        //Color key image
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 255, 192, 203 ) );
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );

        if( newTexture == NULL )
        {
            throw path.c_str();
            throw SDL_GetError();
        }
        //Get image dimensions
        mWidth = loadedSurface->w;
        mHeight = loadedSurface->h;
        //Get rid of old loaded surface
        SDL_FreeSurface( loadedSurface );
        mTexture = newTexture;
        return true;
    }
    catch (const char* error)
    {
        std::cerr << "In Texture::loadFromFile(): " << path << ": " << error << std::endl;
        return false;
    }
}

bool Texture::loadFromRenderedText(
    SDL_Renderer* gRenderer,
    std::string textureText,
    TTF_Font* gFont,
    SDL_Color textColor
)
{
    //Get rid of preexisting texture
    free();
    try
    {
        //Render text surface
        SDL_Surface* textSurface = TTF_RenderText_Solid(
                                       gFont,
                                       textureText.c_str(),
                                       textColor
                                   );
        if (textSurface == NULL)
        {
            throw TTF_GetError();
        }
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if (mTexture == NULL)
        {
            throw SDL_GetError();
        }
        //Get image dimensions
        mWidth = textSurface->w;
        mHeight = textSurface->h;

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
        return true;
    }
    catch (const char* error)
    {
        std::cerr << "In Texture::loadFromRenderedText(): " << textureText << ": " << error << std::endl;
        return false;
    }
}

void Texture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
    //Modulate texture rgb
    SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( mTexture, blending );
}

void Texture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void Texture::render(
    SDL_Renderer* gRenderer,
    int x,
    int y,
    SDL_Rect* clip,
    double angle,
    SDL_Point* center,
    SDL_RendererFlip flip
)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int Texture::getWidth()
{
    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
    return mWidth;
}

int Texture::getHeight()
{
    SDL_QueryTexture(mTexture, NULL, NULL, &mWidth, &mHeight);
    return mHeight;
}


