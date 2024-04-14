#ifndef __COMBAT_H__
#define __COMBAT_H__

//#include "../libs/commun.h"
/**
*
*\struct combattant_s
*\param nom prenom du combattant
*\param pv les pv du combattant
*\param pvMax les pv maximum du combattant
*\param vitesse vitesse du combattant
*\param mort mort du combattant (0=vivant,1=mort)
*\param camp camp du combattant (0=allie,1=ennemi)
*\param temps_recharge le temps de recharge du combattant
*\param temps_recharge_max le temps de recharge qu'il faut atteindre pour avoir son attaque special
*\param indice_portrait l'indice du portrait qu'on lit dans un fichier
*\param indice_sprite l'indice du sprite qu'on lit dans un fichier
*\param type les differente attaque special (0=une attaque puissante sur une cible,1=fait passer le tour a un ennemi,2=soigne le combattant choisi,3=attaque toute les personnes pas dans son camp)
*\param status status du combattant (0=aucun effet,1=passe son tour)
*\param puissance force d'attaque du combattant
*\param forme forme de l'ennemi (0=slime, 1=?,2=?,3=boss)
*\brief structure d'un combattant 
*/

struct combattant_s{
    char * nom;
    int pv;
    int pvMax;
    int vitesse;
    int mort; //0 vivant, 1 mort
    int camp; //0 allie, 1 ennemi
    int temps_recharge;
    int temps_recharge_max;
    int indice_portrait;
    int indice_sprite;
    int type;
    int status; //0 aucun effet ,1 passe leur tour
    int puissance;
    int forme; //0=slime faible,1=ennemi moyen, 2=ennemi fort, 3=boss alliee corrompu
};

/**
*
*\struct combat_s
*\param combattant tableau de tout les combbattant qui vont combattre
*\param ennemi tableau de combattant des ennemis
*\param allie tableau de combattant des allies
*\param nb_point nombre de point que l'on a pendant le combat
*\param mult multiplicateur des attaques
*\param indice_combattant indice du combattant qui va jouer du tableau combattant
*\param indice_allie indice de l'allie viser ou attaquer du tableau allie
*\param indice_ennemi indice de l'ennemi viser ou attaquer du tableau ennemi
*\param nb_ennemi nombre d'ennemi au debut du combat
*\param nb_allie nombre d'allie au debut du combat
*\param num_tour Numero du tour que l'on est
*\brief structure d'un combattant 
*/
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
};

int compare_vitesse_enc( const void * const combattant1 , const void * const combattant2 ) ;
int compare_vitesse(const combattant_t * const combattant1,const combattant_t * const combattant2);
int debut_combat(SDL_Event event,ennemi_t * ennemi,p_mv * pp,case_t * c);
int combat(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,ennemi_t * ennemi,p_mv * pp,map_t * map);
int attaque_allie(int *we,int *he,SDL_Event event,SDL_Renderer * renderer,int Nbennemi,combat_t * combat,int allie,p_mv * personnage,map_t * map);
int attaque_ennemi(int nb_combattant,combat_t * combat);
int affiche_pv(int *we,int *he,SDL_Renderer * renderer,SDL_Rect r_GEcran,SDL_Rect r_DEcran,combat_t *combat,map_t * map);
int affiche_point(int *we, int *he, SDL_Renderer *renderer, SDL_Rect r_basEcran, combat_t * combat,map_t * map);
void erreur_sdl(const char * message,SDL_Window * fenetre,SDL_Renderer *renderer,SDL_Texture *Texture,SDL_Texture *Texture2);
void desctruction_combattant(combattant_t * combattant);
combattant_t *init_combattant(char* nom,int pv,int vitesse,int camp,int indice_portrait,int indice_sprite,int type,int temps_recharge_max,int puissance,int forme);
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