#ifndef __OBJ_H__
#define __OBJ_H__

//#include "../libs/commun.h"

struct obj_s{
    case_t * cas;
    int indTexture;
    int typeObj;
    void * tabObj[20];
};

struct ennemi_s{
    char * nom;
    int indice_portrait;
    int indice_sprite;
    int combat; //1 en combat 0 pas en combat
    int pv;
    combattant_t * combattant[4];
    case_t * c;
    int type;
    int status;
    int vitesse;
    int mort;
    int temps_recharge_max;
    int forme;
};



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
};

struct artefact_s{
    char * nom;
    int possession; //si -1 artefact bloque,0 on l'a pas, 1 on l'a
    int indice; //indice dans le tableau de la map
    char * descriptif;
};

obj_t * init_obj(case_t * c,int indText,int type,...);
int load_obj(carte_t *c, char *namefile);
void affObj(SDL_Renderer *renderer,obj_t * o,map_t map);
void affTabObj(SDL_Renderer *renderer,map_t map,carte_t * carte);
ennemi_t * init_ennemi(char* nom,int pv,int vitesse,int camp,int indice_portrait,int indice_sprite,int type,int temps_recharge_max,int puissance,int forme);
int boolcol (case_t * obj_c,p_mv * pp);
pnj_t init_pnj(char * nom,char * emp_po, char * emp_perso,case_t * c,carte_t * carte);
void debut_dialogue(SDL_Event event,pnj_t * pnj,p_mv * pp);
void pnj_dialogue (SDL_Event event,pnj_t * pnj,SDL_Renderer * renderer,int * he,int * we);
void dest_pnj(pnj_t * pnj);
void aff_pnj(pnj_t pnj, SDL_Renderer *renderer,carte_t * carte);
void dest_ennemi(ennemi_t * en);
void dest_obj(carte_t * c,int ind);
void dest_all_obj(map_t m);

#endif