#include "../libs/commun.h"

obj_t init_obj(case_t * c,int indText,int type,...){
    obj_t newObj;
    newObj.cas = c;
    newObj.indTexture = indText;
    newObj.typeObj = type;
    va_list args;
    va_start(args, type);
    int n; //nombre d'éléments propre a l'objets
    int i;
    switch(type){
        case 0 : //cas d'un objet de décors avec collision
            n = -1;
            newObj.cas->etat = 0;
            break;
        case 1 : //cas d'un objet de décors sans collision
            n = -1;
            newObj.cas->etat = 1;
            break;
        case 2 : //cas d'un ennemi
            n = 1;
            newObj.cas->etat = 0;
            break;
        default://cas d'un objet inconnu
            n = -1;
            break;
    }
    for (i = 0; i < n; i++) {
        newObj.tabObj[i] = va_arg(args, void *);
    }
    va_end(args);
    return newObj;
}

void affObj(SDL_Renderer *renderer,obj_t o,map_t map){
    SDL_RenderCopy(renderer, map.tabTexture[o.indTexture], NULL, &(o.cas->Rectangle));
}

void affTabObj(SDL_Renderer *renderer,map_t map,carte_t * carte){
    int i;
    int n = 0;
    if(map.Nightmare == 1)n=map.nbN;
    for(i = 0; i < carte->nbObj;i++){
        SDL_RenderCopy(renderer, map.tabTexture[(carte->tabObj[i].indTexture)+n], NULL, &(carte->tabObj[i].cas->Rectangle));
    }
}

ennemi_t init_ennemi(char * nom,int indice_portrait,int indice_sprite,map_t * map,int pv,int vitesse,int type,int temps_recharge_max,int puissance,int forme){
    ennemi_t en;
    en.nom = malloc(strlen(nom)+1);
    strcpy(en.nom,nom);
    en.combat=0;
    en.pv=pv;
    en.type=type;
    en.vitesse=vitesse;
    en.mort=0;
    en.temps_recharge_max=temps_recharge_max;
    en.status=0;
    int i;
    for(i=0;i<4;i++){
        en.combattant[i]=NULL;
    }
    en.combattant[0]=init_combattant(nom,en.pv,en.vitesse,1,indice_portrait,indice_sprite,type,1,en.temps_recharge_max,puissance,forme);
    en.indice_portrait=indice_portrait;
    en.indice_sprite=indice_sprite;
    en.forme=forme;
    return en;
}


void dest_ennemi(ennemi_t * en){
    int i;
    int nb_ennemi=0;
    for (i=0;i<4;i++){
        if(en->combattant[i]!=NULL){
            nb_ennemi++;
        }
    }

    for(i=0;i<nb_ennemi;i++){
        desctruction_combattant(en->combattant[i]); 
    }

    free(en->nom);
}



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
    if(pp->c->x+1 == obj_c->x && pp->c->y == obj_c->y){ //verifie case droite
        return 1;
    }else if(pp->c->x-1 == obj_c->x && pp->c->y == obj_c->y){ //verifie case gauche
        return 1;
    }else if(pp->c->y+1 == obj_c->y && pp->c->x == obj_c->x){ //verifie case bas
        return 1;
    }else if(pp->c->y-1 == obj_c->y && pp->c->x == obj_c->x){ //verifie case haut
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
        if(pnj->combattant[i]!=NULL){
            nb_ennemi++;
        }
    }

    for(i=0;i<nb_ennemi;i++){
        desctruction_combattant(pnj->combattant[i]); 
    }

    free(pnj->nom);
    liste_destruction(pnj->dial);
    SDL_FreeSurface(pnj->perso);
    SDL_FreeSurface(pnj->po);
}