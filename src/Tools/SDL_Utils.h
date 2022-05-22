#ifndef SDL_UTILS__H_
#define SDL_UTILS__H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

#include "../Global.h"

namespace utils {
    bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont24, TTF_Font* &gFont32, TTF_Font* &gFont48);
    void close(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, TTF_Font* &gFont24, TTF_Font* &gFont32, TTF_Font* &gFont48);
}


#endif // SDL_UTILS__H_
