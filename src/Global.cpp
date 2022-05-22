#include "Global.h"

double math::rad(double deg)
{
    return deg * PI / 180;
}

double math::deg(double rad)
{
    return 180.0 * rad / PI;
}

bool math::checkCollision(SDL_Rect a, SDL_Rect b)
{
    int leftA = a.x;
    int rightA = a.x + a.w;
    int topA = a.y;
    int bottomA = a.y + a.h;

    int leftB = b.x;
    int rightB = b.x + b.w;
    int topB = b.y;
    int bottomB = b.y + b.h;

    if (bottomA <= topB)
    {
        return false;
    }
    if (topA >= bottomB)
    {
        return false;
    }
    if (rightA <= leftB)
    {
        return false;
    }
    if (leftA >= rightB)
    {
        return false;
    }
    return true;
}

bool math::checkCenter(SDL_Rect a, SDL_Rect b)
{
    return (std::abs((a.x + (a.w / 2)) - (b.x + (b.w / 2))) <= 3);
}

bool tiles::isSoil(int value)
{
    return (value >= 9 && value <= 12) || (value >= 17 && value <= 20);
}

bool tiles::isTrap(int value)
{
    return (value >= 53 && value <= 56);
}

bool tiles::isLadder(int value)
{
    return (value == 4 || value == 3);
}

bool tiles::isDoor(int value)
{
    return value == 64;
}
