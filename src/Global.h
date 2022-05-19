#ifndef GLOBAL__H_
#define GLOBAL__H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include <cmath>

//Window properties
const std::string WINDOW_TITLE = "Unescaped";
const int SCREEN_WIDTH = 1800;
const int SCREEN_HEIGHT = 720;

//Maths constants
const double PI = 3.14159265;

//Physics constants
const double GRAVITY = 9.8;

//Game states
enum GameState {
    MAIN_MENU,
    RUNNING,
    WINNING,
    LOSING,
    QUITING,
};

#endif // GLOBAL__H_
