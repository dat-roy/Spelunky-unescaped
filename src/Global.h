#ifndef GLOBAL__H_
#define GLOBAL__H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>
#include <vector>

//Window properties
const std::string WINDOW_TITLE = "Unescaped";
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

//Level sizes
const int LEVEL_WIDTH = 1280 * 2;
const int LEVEL_HEIGHT = 960;

//Tile constants
const int TILE_WIDTH = 64;
const int TILE_HEIGHT = 64;
const int TILE_COUNT = 8;

//Math constants & methods
namespace math {
    const double PI = 3.14159265;
    double rad(double deg);
    double deg(double rad);
    bool checkCollision(SDL_Rect a, SDL_Rect b);
    bool checkCenter(SDL_Rect a, SDL_Rect b);
}

//Physics constants & methods
namespace physics {
    const double GRAVITY = 9.8;
}

//Tile types
namespace tiles {
    bool isSoil(int value);
    bool isTrap(int value);
    bool isLadder(int value);
    bool isDoor(int value);
}

//Game states
enum GameState {
    MAIN_MENU,
    INTRO,
    RUNNING_LEVEL_1,
    RUNNING_LEVEL_2,
    WINNING,
    GAMEOVER,
    QUITING
};

//Charater actions
enum ActionTypes {
    DYING,
    STANDING,
    WALKING,
    LYING,
    CRAWLING,
    THROWING,
    JUMPING_UP,
    JUMPING_DOWN,
    CLIMBING_UP,
    CLIMBING_DOWN,
    ATTACKING,
    ROARING
};


#endif // GLOBAL__H_
