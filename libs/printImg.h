#ifndef __PRINTIMG_H__
#define __PRINTIMG_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int print_bg(SDL_Window * w,SDL_Renderer* r);
void destroyBg(SDL_Texture* bgTexture,SDL_Renderer* rendererBg);

#endif