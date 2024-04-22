#ifndef __PMOV_H__
#define __PMOV_H__

//#include "../libs/commun.h"



/**
*
*\struct personnage
*\param r taille du personnage
*\param d direction orienté{N,E,S,O}{0,1,2,3}
*\param e etat du personnage
*\param nom prenom du personnage
*\param equipe tableau de structure de combattant
*\param Nightmare variable pour savoir si le personnage est en cauchemar ou non (0=pas en cauchemar,1=en cauchemar)
*\param NightP point de cauchemar dans la barre de cauchemar
*\param NightMax maximum de la barre de cauchemar
*\param frame indiquateur du nombre de frame ecouler depuis le debut du deplacement du personnage
*\param lock variable pour bloquer le personnage (0=peut se deplacer,1=peut pas se deplacer)
*\brief structure de personnage
*/

struct personnage{
    //coordonées du personnage et taille dans un rect
    //carte_t * carte;
    case_t * c;
    SDL_Rect r;//{x,y,w,h}
    int * d; //direction orienté{N,E,S,W}{0,1,2,3}
    int e; //etat du personnage
    char * nom;
    combattant_t * equipe[4];
    int * Nightmare;
    int * NightP; //pointcauchemar
    int NightMax;
    int * frame;
    int lock;
    int nb_allie;
};

void pinput(p_mv * pmv,SDL_Event event,carte_t ** carte,map_t *map,SDL_Renderer * renderer,int * transi,Mix_Music* gMusic,int * toucheDeplacement);

int affp(p_mv * pmv,SDL_Renderer *renderer,SDL_Event event);

void col_p(SDL_Rect * obj_r,p_mv * pp);

void lower(char *input, char *output);

p_mv * initp();

void remplirp(p_mv * p,case_t * c,int leader);

void desctruction_p_eq(p_mv * p);

void transition(SDL_Renderer * renderer,int * transi,int we,int he) ;

#endif