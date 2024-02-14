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
/*
case_t c creation_case(void){
    case_t c;
    c.etat=0;
    return c;
}

grille_t creation_grille(void){
    grille_t g;
    int i,j;

    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            g.tabGrille[i][j]=creation_case();
        }
    }
    return g;

}*/

carte_t creation_carte(void){
    carte_t carte;
    //carte.grille=creation_grille();
    carte.etat_brouillard=1;
    carte.r=0;
    carte.g=0;
    carte.b=0;
    carte.a=0;
}

carte_t color_carte(carte_t c, Uint8 red, Uint8 gre, Uint8 blu, Uint8 al){
    c.r=red;
    c.g=gre;
    c.b=blu;
    c.a=al;
    return c;
}

map_t creation_map (void){
    map_t m;
    int i,j;
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLUMNS;j++){
            m.tabMap[i][j]=creation_carte();
        }
    }
    return m;
}