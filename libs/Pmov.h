#ifndef __PMOV_H__
#define __PMOV_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct personnage p_mv;
struct personnage{
    //coordonées du personnage et taille dans un rect
    SDL_Rect r;//{x,y,w,h}
    int d; //direction orienté{N,E,S,W}{0,1,2,3}
    int e; //etat du personnage
    char * nom;
    int pv;
};

void pinput(p_mv * pmv,SDL_Event event);

void affp(p_mv * pmv,SDL_Renderer *renderer);

void col_p(SDL_Rect * obj_r,p_mv * pp);

p_mv initp(int x,int y);

#endif