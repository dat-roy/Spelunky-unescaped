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

//Tile types

enum TileTypes {

};
enum TileBorderTypes {

};

//Maths constants
const double PI = 3.14159265;

//Physics constants
const double GRAVITY = 9.8;

//Game states
enum GameState {
    MAIN_MENU,
    INTRO,
    RUNNING_LEVEL_1,
    RUNNING_LEVEL_2,
    WINNING,
    LOSING,
    QUITING,
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
};


#endif // GLOBAL__H_
