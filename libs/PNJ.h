#ifndef __PNJ_H__
#define __PNJ_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../libs/texte.h"
#include "../libs/Pmov.h"
#include "../libs/map2.h"

typedef struct pnj_s pnj_t;
struct pnj_s{
    char * nom;
    case_t * c;
    Liste * dial;
    SDL_Surface * po;
    SDL_Surface * perso;
    int combat;
    int pv;
};

int boolcol (case_t * obj_c,p_mv * pp);
pnj_t init_pnj(char * nom,char * emp_po, char * emp_perso,case_t * c);
void debut_dialogue(SDL_Event event,pnj_t * pnj,p_mv * pp);
void pnj_dialogue (SDL_Event event,pnj_t * pnj,SDL_Renderer * renderer,int * he,int * we);
void dest_pnj(pnj_t * pnj);
void aff_pnj(pnj_t pnj, SDL_Renderer *renderer);

#endif