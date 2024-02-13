#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../libs/texte.h"
#include "../libs/Pmov.h"

typedef struct pnj_s pnj_t;
struct pnj_s{
    char * nom;
    SDL_Rect r;
    Liste * dial;
    SDL_Surface * po;
    SDL_Surface * perso;
};

int boolcolbeta (SDL_Rect * obj_r,p_mv * pp);
pnj_t init_pnj(char * nom,int x, int y,char * emp_po, char * emp_perso);
void debut_dialogue(SDL_Event event,Liste * liste,SDL_Rect * obj_r,p_mv * pp);
void pnj_dialogue (SDL_Event event,pnj_t * pnj,SDL_Renderer * renderer,int * he,int * we);
void dest_pnj(pnj_t * pnj);
void aff_pnj(pnj_t pnj, SDL_Renderer *renderer);

