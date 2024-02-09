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
    mess_s *premier;
    mess_s * ec;
    int  test;
};

extern SDL_Event event;
int affiche_texte(SDL_Renderer * rendu,Liste *mess,int dim,int * etat);
void dialogue (SDL_Event event,int * etat,Liste * liste);


Liste *initialisation();

void insertion(Liste *liste, char * nvMess);
void suppression(Liste *liste);
void afficherListe(Liste *liste);
void destruction(Liste * liste);
#endif
