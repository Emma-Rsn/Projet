//
//map.c
//Created by Moreau Enzo Rasson Emma
//

/**
*\file map.c
*\brief programme pour les maps
*\author Moreau Enzo Rasson Emma
*\date  Fevrier 2024
*\version 1.0
*
*/


#include "../libs/map2.h"

case_t creation_case(int we, int he){
    case_t c;
    c.etat=0;
    c.Rectangle.x=0;
    c.Rectangle.y=0;
    c.Rectangle.w=64;
    c.Rectangle.h=64;
    return c;
}

grille_t creation_grille(int w, int h){
    grille_t g;
    int i,j;
    int taille=64;
    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            printf("oui3 %d %d\n",i,j);
            g.tabGrille[i][j]=creation_case(w,h);
            g.tabGrille[i][j].Rectangle.x=taille*i;
            g.tabGrille[i][j].Rectangle.y=taille*j+56;
        }
    }
    return g;

}

carte_t creation_carte(int w, int h){
    printf("oui2\n");
    carte_t carte;
    carte.grille=creation_grille(w,h);
    printf("oui6\n");
    carte.etat_brouillard=1;
    carte.r=255;
    carte.g=255;
    carte.b=255;
    carte.a=255;
    return carte;
}

map_t creation_map (int w, int h){
    map_t m;
    int i,j;
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLUMNS;j++){
            printf("oui %d %d\n",i,j);
            m.tabMap[i][j]=creation_carte(w,h);
        }
    }
    return m;
}

int afficher_grille(grille_t grille, SDL_Renderer *renderer){
    int i,j;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            SDL_RenderDrawRect(renderer, &(grille.tabGrille[i][j].Rectangle));
        }
    }
    return 0;
}