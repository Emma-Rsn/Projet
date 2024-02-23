#ifndef __PMOV_H__
#define __PMOV_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../libs/map2.h"

typedef struct personnage_equipe p_eq;
struct personnage_equipe{
    //coordonées du personnage et taille dans un rect
    SDL_Rect r;//{x,y,w,h}
    char * nom;
    int pv;
    char * nomATQ1;
    char * nomATQ2;
    char * nomATQ3;
    
    
};

typedef struct personnage p_mv;
struct personnage{
    //coordonées du personnage et taille dans un rect
    case_t c;
    SDL_Rect r;//{x,y,w,h}
    int d; //direction orienté{N,E,S,W}{0,1,2,3}
    int e; //etat du personnage
    char * nom;
    int pv;
    p_eq *equipe[3];

};

void pinput(p_mv * pmv,SDL_Event event,grille_t grille);

int affp(p_mv * pmv,SDL_Renderer *renderer);

void col_p(SDL_Rect * obj_r,p_mv * pp);

p_mv initp(case_t c);

#endif