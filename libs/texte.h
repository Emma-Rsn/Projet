#ifndef __TEXTE_H__
#define __TEXTE_H__



typedef struct mess_t mess_s;
struct mess_t
{
    char * message;
    mess_s *suivant;
};

typedef struct Liste Liste;
struct Liste
{
    mess_s * premier;
    mess_s * ec;
    int etat; //0 = pas d'affichage debut liste 1 == affichage premier 2 == affichage element 3 == affichage dernier
};

extern SDL_Event event;

int affiche_texte(SDL_Renderer * rendu,Liste *mess,int dim);
int aff_boite_dia(SDL_Renderer * rendu,Liste *liste,SDL_Surface * po,int le,int LE);
void dialogue (SDL_Event event,Liste * liste);
int liste_vide(Liste * liste);
void liste_premier(Liste * liste);
void liste_suivant(Liste * liste);
Liste *initialisation();
void insertion(Liste *liste, char * nvMess);
void liste_suppression(Liste *liste);
void afficherListe(Liste *liste);
void liste_destruction(Liste * liste);
#endif
