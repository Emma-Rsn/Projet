#ifndef __PNJ_H__
#define __PNJ_H__

//#include "../libs/commun.h"

struct pnj_s{
    char * nom;
    case_t * c;
    int xcarte;
    int ycarte;
    Liste * dial;
    SDL_Surface * po;
    SDL_Surface * perso;
    int combat;
    int pv;
    combattant_t * combattant[4];
};

int boolcol (case_t * obj_c,p_mv * pp);
pnj_t init_pnj(char * nom,char * emp_po, char * emp_perso,case_t * c,carte_t * carte);
void debut_dialogue(SDL_Event event,pnj_t * pnj,p_mv * pp);
void pnj_dialogue (SDL_Event event,pnj_t * pnj,SDL_Renderer * renderer,int * he,int * we);
void dest_pnj(pnj_t * pnj);
void aff_pnj(pnj_t pnj, SDL_Renderer *renderer,carte_t * carte);

#endif