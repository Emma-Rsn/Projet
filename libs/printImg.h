#ifndef __PRINTIMG_H__
#define __PRINTIMG_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int print_bg(SDL_Texture* backgroundTexture,SDL_Renderer* r,int LE, int lE);

int NB_Fps(int *nfps,Uint32 * t0,Uint32 * t1);

void aff_Fps(int cmpfps,SDL_Renderer *renderer);

#endif