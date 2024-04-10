#ifndef __PRINTIMG_H__
#define __PRINTIMG_H__

//#include "../libs/commun.h"

int print_bg(SDL_Texture* backgroundTexture,SDL_Renderer* r,int LE, int lE);

int NB_Fps(int *nfps,Uint32 * t0,Uint32 * t1);

int aff_Fps(int cmpfps,SDL_Renderer *renderer);

void ajDFPS(int * dfps,int * cmpfps,int *nfps,Uint32 * t0,Uint32 * t1);

void  affHud(SDL_Renderer * renderer,int * he,int * we,map_t map,p_mv pmv);

#endif