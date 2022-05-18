#ifndef TEXTURE_CLIPS_H__
#define TEXTURE_CLIPS_H__

#include <SDL.h>
#include <iostream>
#include <vector>

struct TextureClips {
    int total_frames;
    int current_frame;
    std::vector<SDL_Rect> clips;

    TextureClips();
    TextureClips(const int total_frames);

    //Get total frames
    int getTotalFrames();
    //Get current frame
    int getCurrentFrame();
    //Go to next frame
    void nextFrame();
    //Reset to the first frame
    void resetFrame();
};

#endif // TEXTURE_CLIPS_H__
