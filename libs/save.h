#ifndef __SAVE_H__
#define __SAVE_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>

extern int save_settings(void);

extern int load_settings(int * lEcran,int * LEcran);

#endif