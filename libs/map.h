#ifndef __MAP2_H__
#define __MAP2_H__


//#include "../libs/commun.h"
#include "../libs/OBJ.h"

/**
*
*\struct case_s
*\param Rectangle Rectangle SDL de la taille de la case
*\param x Position x de la case dans la grille
*\param y Position x de la case dans la grille
*\param etat Présence ou non d'un obstacle dans la case (si 0 alors obstacle dans la case, 1 case libre, 2 case libre mais en bordure, 3 case libre mais en bordure finale)
*\param ntexture Numéro de la texture associée à la case
*\brief Structure d'une case
*/

struct case_s{
    SDL_Rect Rectangle;
    int x;
    int y;
    int etat;// si 0 alors obstacle dans la case 1 case libre 2 case libre mais en bordure 3 case libre mais en bordure finale
    int ntexture;
};

/**
*
*\struct grille_s
*\param tabGrille Matrice de cases pour former une carte
*\brief Structure d'une grille
*/
struct grille_s{
    case_t tabGrille[LONG][LARG];
};

/**
*
*\struct carte_s
*\param xcarte Position x de la carte dans la matrice de la map
*\param ycarte Position y de la carte dans la matrice de la map
*\param etat_brouillard Indique si la carte a été ou non explorée (si 1 alors la carte est couverte de brouillard, si 0 alors la carte a été explorée)
*\param nZone Zone à laquelle la carte appartient
*\param nbObj Nombre d'objets présents sur la carte
*\param nrlayout Numéro du layout chargé
*\param tabObj Tableau d'objets de la carte
*\param grille Grille de 30*16 cases
*\brief Structure d'une carte
*/
struct carte_s{
    int xcarte;
    int ycarte;
    int etat_brouillard; // si 1 alors la carte est couverte de brouillard(pas encore explorée), si 0 alors la carte a été explorée
    int nZone;
    int nbObj;
    int nrlayout; //numero du layout chargé
    obj_t * tabObj[50];
    grille_t grille; //quadrillage des cases dans une seule carte
};

/**
*
*\struct map_s
*\param tabMap Matrice des cartes d'une map
*\param tabPath Tableau des chemins de textures
*\param nbTexture Tableau du nombre de textures zone par zone
*\param tabTexture Tableau des textures courantes SDL
*\param zoneChargee Zone courante du joueur
*\param Nightmare Indique si on est en mode cauchemar ou non
*\param nbN Nombre de textures d'écart pour avoir la version corrompue dans le tableau de chemin de textures
*\param nvZone Niveau de la zone courante
*\param nvEquipe Niveau de l'équipe
*\param bonusEquipeN Bonus de l'équipe dans le mode cauchemar
*\param bonusZoneN Bonus de la zone dans le mode cauchemar
*\param argent Argent courant du joueur
*\param listeArtefact Tableau de tous les artefacts
*\param nb_emplacement Nombre d'emplacements d'artefact débloqués
*\param prix_emplacement Prix d'achat d'un emplacement d'artefact
*\param Zone2 Indique la zone 2 est finie ou non (si 0 zone non débloquée, si 1 le joueur est bloqué dans la zone, si 2 le boss de la zone a été vaincu)
*\param Zone3 Indique la zone 3 est finie ou non
*\param Zone4 Indique la zone 4 est finie ou non
*\param Zone5 Indique la zone 5 est finie ou non
*\brief Structure d'une map
*/
struct map_s{
    carte_t tabMap[ROWS][COLUMNS];
    char *** tabPath;
    int nbTexture[10];
    SDL_Texture ** tabTexture;
    int zoneChargee;
    int Nightmare;
    int nbN;
    int nvZone;
    int nvEquipe;
    float bonusEquipeN;
    int bonusZoneN;
    int argent;
    artefact_t * listeArtefact[10];
    int nb_emplacement;
    int prix_emplacement;
    //0 si pas rentrer dans la zone 1 si rentrer mais que le boss est vivant et 2 si le boss est mort
    int Zone2;
    int Zone3;
    int Zone4;
    int Zone5;
    int cle;
    int plongee;
    int talisman;
};

int load_layout_texture(map_t * map);
case_t creation_case();
grille_t creation_grille(int bord);
carte_t creation_carte(int x,int y);
map_t creation_map ();
int afficher_grille(grille_t grille, SDL_Renderer *renderer);
int afficher_carte(SDL_Renderer *renderer,map_t * map,carte_t * cartec);
int creer_map(map_t * map);
int sauvegarde_map(map_t * map);
int creer_map_layout(map_t * map);
int sauvegarde_map_layout(map_t * map);
int remplir_map(map_t *map);
float min(float a, float b);
int zone_fini(map_t map);
int zone_bloquer(int zone,map_t map);
int afficher_map(SDL_Event event,map_t map, SDL_Renderer *renderer, int *we, int *he, int *etat_map,carte_t * cartec);
int chargement_Zone(map_t * map,SDL_Renderer *renderer,int nZone,Mix_Music* gMusic);
void lumiere(SDL_Renderer *renderer,carte_t *cartec,case_t *c);
int load_layout(carte_t * c,char * namefile);
int detruire_tab_path(map_t *map);
int nb_texture_chargement(map_t *map, char* namefile);
int creation_tab_path(map_t *map,char * namefile);
int creation_tab_texture(map_t *map,SDL_Renderer *renderer,int nbZone,int free);
int sauvegarde_map_brouillard(map_t * map);
int load_brouillard(map_t *map);
int load_layout_obj(map_t * map);

#endif