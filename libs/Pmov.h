#ifndef __PMOV_H__
#define __PMOV_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../libs/map2.h"

/**
*
*\struct personnage_equipe
*\param nom prenom du personnage
*\param pv les pv du personnage
*\param nomATQ1 nom de l'attaque de base du personnage
*\param nomATQ2 nom de l'attaque particuliere de personnage
*\param nomATQspe nom de l'attaque special du personnage dans le cauchemar
*\brief structure de personnage de l'equipe
*/

typedef struct personnage_equipe p_eq;
struct personnage_equipe{
    //coordonées du personnage et taille dans un rect
    char * nom;
    int pv;
    char * nomATQ1;
    char * nomATQ2;
    char * nomATQspe;
};

/**
*
*\struct personnage
*\param r taille du personnage
*\param d direction orienté{N,E,S,O}{0,1,2,3}
*\param e etat du personnage
*\param nom prenom du personnage
*\brief structure de personnage
*/

typedef struct personnage p_mv;
struct personnage{
    //coordonées du personnage et taille dans un rect
    carte_t * carte;
    case_t * c;
    SDL_Rect r;//{x,y,w,h}
    int d; //direction orienté{N,E,S,W}{0,1,2,3}
    int e; //etat du personnage
    char * nom;
    p_eq *equipe[4];

};

void pinput(p_mv * pmv,SDL_Event event,carte_t ** carte,map_t *map,SDL_Renderer * renderer,int * transi);

int affp(p_mv * pmv,SDL_Renderer *renderer);

void col_p(SDL_Rect * obj_r,p_mv * pp);

p_mv initp(carte_t * carte,case_t * c);

p_eq *initp_eq(char* nom,int pv,char * nomATQ1,char * nomATQ2,char * nomATQspe);

void desctruction_p_eq(p_mv * p);

void transition(SDL_Renderer * renderer,int * transi,int we,int he) ;

#endif