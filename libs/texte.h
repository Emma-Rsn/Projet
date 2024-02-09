#ifndef __TEXTE_H__
#define __TEXTE_H__

extern SDL_Event event;
int affiche_texte(SDL_Renderer * rendu,char *mess,int dim,SDL_Color color);
void dialogue (SDL_Event event,int * etat);

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
};


Liste *initialisation();

void insertion(Liste *liste, char * nvMess);
void suppression(Liste *liste);
void afficherListe(Liste *liste);
void destruction(Liste * liste);
#endif
