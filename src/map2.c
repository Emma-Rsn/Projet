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
            g.tabGrille[i][j]=creation_case(w,h);
            g.tabGrille[i][j].Rectangle.x=taille*i;
            g.tabGrille[i][j].Rectangle.y=taille*j+56;
        }
    }
    return g;

}

carte_t creation_carte(int w, int h){
    carte_t carte;
    carte.grille=creation_grille(w,h);
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

int remplir_map(map_t *map){
    FILE * file;

    int x=0;
    int y=0;
    char numZone;

    file=fopen("save/map.txt","r");
    if(file){
        fscanf(file,"%c",&numZone);

        while(!feof(file)){
            if(numZone=='\n'){
                x++;
                y=0;
            }
            else if(numZone>='1'&&numZone<='5'){
                map->tabMap[x][y].nZone=numZone - '0';
                y++;
            }
            fscanf(file,"%c",&numZone);
        }
        fclose(file);
        return 0;
    }
    else{
        printf("Fichier inexistant\n");
        return 1;
    }
}


int afficher_zone (map_t map){
    int i,j;
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLUMNS;j++){
            printf("%d ",map.tabMap[i][j].nZone);
        }
        printf("\n");
    }
    return 0;

}

float min(float a, float b) {
    return (a < b) ? a : b;
}

int afficher_map(SDL_Event event,map_t map, SDL_Renderer *renderer, int *we, int *he, int *etat_map){
    int i, j;
    //printf("we=%d he=%d",(*we),(*he));
    /*int firstX=(*we)/4;
    int firstY=(*he)/(53/23);
    SDL_Rect Rectangle;
    Rectangle.x=firstX;
    Rectangle.y=firstY;
    Rectangle.w=Rectangle.x/3;
    Rectangle.h=Rectangle.y/3;

    int firstX=510;
    int firstY=60;
    SDL_Rect Rectangle;
    Rectangle.x=firstX;
    Rectangle.y=firstY;
    Rectangle.w=160;
    Rectangle.h=160;*/

    SDL_Rect Rectangle;

    // Marges
    float margeX = (*we) * 0.1;
    float margeY = (*he) * 0.1;

    // Largeur et hauteur utilisables
    float largeurUtilisable = (*we) - 2 * margeX;
    float hauteurUtilisable = (*he) - 2 * margeY;

    // Taille de chaque carré
    float taille_carre = min(largeurUtilisable, hauteurUtilisable) / 6;

    // Coordonnées du premier carré
    float firstX = margeX + ((*we) - 2 * margeX - taille_carre * 6) / 2;
    float firstY = margeY + ((*he) - 2 * margeY - taille_carre * 6) / 2;
    Rectangle.x = (int)firstX;
    Rectangle.y = (int)firstY;
    Rectangle.w = (int)taille_carre;
    Rectangle.h = (int)taille_carre;

    if((*etat_map) == 1){

        SDL_Surface* surface = SDL_CreateRGBSurface(0, *we, *he, 32,0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        // Copie les pixels du rendu actuel dans la surface
        SDL_RenderReadPixels(renderer, NULL, surface->format->format, surface->pixels, surface->pitch);
        // Créer une texture à partir de la surface
        SDL_Texture* targetTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        SDL_Rect tecran = {0,0,*we,*he};

        while((*etat_map) < 2){
            while (SDL_PollEvent(&event) != 0) {
                if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_x)){
                    (*etat_map)=2;
                }
            }
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, targetTexture, NULL, NULL);
            SDL_SetRenderDrawColor(renderer,0,0,0,100);
            SDL_RenderFillRect(renderer, &tecran);
            for(i=0;i<ROWS;i++){
                Rectangle.y = (int)(firstY + i * taille_carre);
                for(j=0;j<COLUMNS;j++){
                    switch(map.tabMap[i][j].nZone){
                        case 1: SDL_SetRenderDrawColor(renderer, 206,206,206,255);break;
                        case 2: SDL_SetRenderDrawColor(renderer, 86,115,154,255);break;
                        case 3: SDL_SetRenderDrawColor(renderer, 153,81,43,255);break;
                        case 4: SDL_SetRenderDrawColor(renderer, 104,157,113,255);break;
                        case 5: SDL_SetRenderDrawColor(renderer, 115,8,0,255);break;
                        default: break;
                    }
                    Rectangle.x = (int)(firstX + j * taille_carre);
                    SDL_RenderFillRect(renderer, &Rectangle);
                }
            }
            SDL_RenderPresent(renderer);
            SDL_Delay(100);
        }
        (*etat_map) = 0;
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, targetTexture, NULL, NULL);
        SDL_RenderPresent(renderer);
        SDL_DestroyTexture(targetTexture);
    }
    return 0;
}