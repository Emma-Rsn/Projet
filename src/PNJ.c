#include "../libs/commun.h"

pnj_t init_pnj(char * nom,char * emp_po, char * emp_perso,case_t * c,carte_t * carte){
    pnj_t pnj;
    pnj.nom = malloc(strlen(nom)+1);
    strcpy(pnj.nom,nom);
    pnj.c = c;
    pnj.c->etat=0;
    pnj.xcarte=carte->xcarte;
    pnj.ycarte=carte->ycarte;
    pnj.dial = initialisation();
    if(emp_po != NULL)pnj.po = IMG_Load(emp_po);
    pnj.perso = IMG_Load(emp_perso);
    pnj.combat=0;
    pnj.pv=100;
    int i;
    for(i=0;i<4;i++){
        pnj.combatant[i]=NULL;
    }
    return pnj;
}

void aff_pnj(pnj_t pnj, SDL_Renderer *renderer,carte_t * carte){
    if(pnj.xcarte == carte->xcarte && pnj.ycarte == carte->ycarte){
        SDL_Texture * tperso = SDL_CreateTextureFromSurface(renderer, pnj.perso);
        SDL_RenderCopy(renderer, tperso, NULL, &(pnj.c->Rectangle));
        SDL_DestroyTexture(tperso);
    }
}


int boolcol (case_t * obj_c,p_mv * pp){
    if(pp->c->x+1 == obj_c->x){ //verifie case droite
        return 1;
    }else if(pp->c->x-1 == obj_c->x){ //verifie case gauche
        return 1;
    }else if(pp->c->y+1 == obj_c->y){ //verifie case bas
        return 1;
    }else if(pp->c->y-1 == obj_c->y){ //verifie case haut
        return 1;
    }
    return 0;
}

void debut_dialogue(SDL_Event event,pnj_t * pnj,p_mv * pp){
    if(boolcol(pnj->c,pp)) dialogue (event,pnj->dial);
}

void pnj_dialogue (SDL_Event event,pnj_t * pnj,SDL_Renderer * renderer,int * he,int * we){
    if(pnj->dial->etat == 1){

        SDL_Surface* surface = SDL_CreateRGBSurface(0, *we, *he, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        // Copie les pixels du rendu actuel dans la surface
        SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
        // Créer une texture à partir de la surface
        SDL_Texture* targetTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        SDL_Rect tecran = {0,0,*we,*he};

        while(pnj->dial->etat < 2){
            while (SDL_PollEvent(&event) != 0) {
                dialogue (event,pnj->dial);
            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, targetTexture, NULL, NULL);
            SDL_SetRenderDrawColor(renderer,0,0,0,100);
            SDL_RenderFillRect(renderer, &tecran);
            aff_boite_dia(renderer,pnj->dial,pnj->po,*(we),*(he));
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
        }
        pnj->dial->etat = 0;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, targetTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(targetTexture);
    }
}

void dest_pnj(pnj_t * pnj){
    int i;
    int nb_ennemi=0;
    for (i=0;i<4;i++){
        if(pnj->combatant[i]!=NULL){
            nb_ennemi++;
        }
    }

    for(i=0;i<nb_ennemi;i++){
        free(pnj->combatant[i]);
    }

    free(pnj->nom);
    liste_destruction(pnj->dial);
    SDL_FreeSurface(pnj->perso);
    SDL_FreeSurface(pnj->po);
}