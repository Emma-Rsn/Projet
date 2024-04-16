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



/**
*
*\struct artefact_s
*\param nom nom de l'artefact
*\param possession variable pour savoir si 'lon possede l'artefact (0=non,1=oui,-1=artefact bloque)
*\param indice indice de l'artefact dans le tableau d'artefact de la structure map
*\param descriptif description de l'artefact
*\param prix prix de l'artefact
*\param indice_texture indice de la texture de l'artefact
*\param equipe variable pour savoir si l'artefact est equipe (0=pas equipe,1=equipe)
*\brief structure d'un artefact
*/
struct artefact_s{
    char * nom;
    int possession; //si -1 artefact bloque,0 on l'a pas, 1 on l'a
    int indice; //indice dans le tableau de la map
    char * descriptif;
    int prix;
    int indice_texture;
    int equipe;
};

obj_t * init_obj(case_t * c,int indText,int type,...);
int load_obj(carte_t *c, char *namefile);
void affObj(SDL_Renderer *renderer,obj_t * o,map_t map);
void affTabObj(SDL_Renderer *renderer,map_t map,carte_t * carte);
ennemi_t * init_ennemi(char* nom,int pv,int vitesse,int camp,int indice_portrait,int indice_sprite,int type,int temps_recharge_max,int puissance,int forme);
int boolcol (case_t * obj_c,p_mv * pp);
void dest_ennemi(ennemi_t * en);
void dest_obj(carte_t * c,int ind);
void dest_all_obj(map_t m);
void destruction_artefact(artefact_t * artefact);
artefact_t * init_artefact(char* nom, int possession,char * descriptif,int indice,int prix,int indice_texture);

#endif