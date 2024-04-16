#ifndef __COMBAT_H__
#define __COMBAT_H__

//#include "../libs/commun.h"
/**
*
*\struct combattant_s
*\param nom prenom du combattant
*\param pv les pv du combattant
*\param vitesse vitesse du combattant
*\param nomATQ1 nom de l'attaque de base du combattant
*\param nomATQspe nom de l'attaque special du combattant dans le cauchemar
*\brief structure d'un combattant 
*/


struct combattant_s{
    char * nom;
    int * pv;
    int pvMax;
    int vitesse;
    int mort; //0 vivant, 1 mort
    int camp; //0 alliee, 1 ennemi
    int temps_recharge;
    int temps_recharge_max;
    int indice_portrait;
    int indice_sprite;
    int type;
    int status; //0 aucun effet ,1 passe leur tour
    int puissance;
    int forme; //0=slime faible,1=ennemi moyen, 2=ennemi fort, 3=boss alliee corrompu
};

struct combat_s{
    combattant_t * combattant[8];
    combattant_t * ennemi[4];
    combattant_t * allie[4];
    int nb_point;
    float mult;
    int indice_combattant;
    int indice_allie;
    int indice_ennemi;
    int nb_ennemi;
    int nb_allie;
    int num_tour;
    //barre de cauchemard
};

combattant_t * pre_init_combattant();
void remplir_combattant(combattant_t * c,char* nom,int pv,int vitesse,int camp,int indice_portrait,int indice_sprite,int type,int temps_recharge_max,int puissance,int forme);
int compare_vitesse_enc( const void * const combattant1 , const void * const combattant2 ) ;
int compare_vitesse(const combattant_t * const combattant1,const combattant_t * const combattant2);
int debut_combat(SDL_Event event,ennemi_t * ennemi,p_mv * pp,case_t * c);
int combat(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,ennemi_t * ennemi,p_mv * pp,map_t * map);
int attaque_allie(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,ennemi_t * ennemi,combattant_t *combattant,int Nbennemi,combat_t * combat,int allie,p_mv * personnage,map_t * map);
int attaque_ennemi(int nb_combattant,combat_t * combat);
int affiche_pv(int *we,int *he,SDL_Renderer * renderer,SDL_Rect r_GEcran,SDL_Rect r_DEcran,combat_t *combat,map_t * map);
int affiche_point(int *we, int *he, SDL_Renderer *renderer, SDL_Rect r_basEcran, combat_t * combat,map_t * map);
void erreur_sdl(const char * message,SDL_Window * fenetre,SDL_Renderer *renderer,SDL_Texture *Texture,SDL_Texture *Texture2);
void desctruction_combattant(combattant_t * combattant);
combattant_t *init_combattant(char* nom,int pv,int vitesse,int camp,int indice_portrait,int indice_sprite,int type,int temps_recharge_max,int puissance,int forme);
void aff(combattant_t * combattant);
int affichage_combat(int *we,int *he,SDL_Renderer * renderer,combat_t *combat,int etat,p_mv * personnage,map_t * map);
combat_t * init_combat();
void affVie(SDL_Renderer * renderer,int  he,int we,combattant_t * combattant,map_t * map);
void soin(combat_t * combat,SDL_Rect r_basEcran,SDL_Renderer * renderer,int * we,int * he,int allie,SDL_Event event,p_mv * personnage,map_t * map);
void barreCauchemard(p_mv * pmv,SDL_Renderer * renderer,map_t * map);
void debut_combat_carte(carte_t * cartec,SDL_Event event,p_mv * pp);
void combat_carte(carte_t * cartec,int *we,int *he,SDL_Event event,SDL_Renderer * renderer,p_mv * pp,map_t * map);
int forme_attaque(int nb_combattant,combat_t * combat);
void copier_combattant(combattant_t * combattant,combattant_t * combattantcopie);
#endif