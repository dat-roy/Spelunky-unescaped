#include "TextureClips.h"

TextureClips::TextureClips()
{
    total_frames = 1;
    current_frame = 0;
}

TextureClips::TextureClips(const int total_frames) : total_frames(total_frames)
{
    current_frame = 0;
}

//Get total frames
int TextureClips::getTotalFrames()
{
    return total_frames;
}
//Get current frame
int TextureClips::getCurrentFrame()
{
    return current_frame;
}
//Go to next frame
void TextureClips::nextFrame()
{
    current_frame++;
}
//Reset to the first frame
void TextureClips::resetFrame()
{
    current_frame = 0;
}
