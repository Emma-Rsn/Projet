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

case_t creation_case(){
    case_t c;
    c.etat=1;
    c.Rectangle.x=0;
    c.Rectangle.y=0;
    c.Rectangle.w=64;
    c.Rectangle.h=64;
    c.ntexture = 0;
    return c;
}

grille_t creation_grille(int w, int h, int bord){
    grille_t g;
    int i,j;
    int taille=64;
    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            g.tabGrille[i][j]=creation_case();
            switch (bord){
                case 0 : if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;break;
                case 1 : if(j == 0 )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //N
                case 2 : if(i == (LONG-1) )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //E
                case 3 : if(j == (LARG-1) )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //S
                case 4 : if(i == 0 )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //O
                case 5 : if(j == 0 || i == (LONG-1) )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //NE
                case 6 : if(j == (LARG-1) || i == (LONG-1) )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //SE
                case 7 : if(j == (LARG-1) || i == 0 )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //SO
                case 8 : if(j == 0 || i == 0 )g.tabGrille[i][j].etat = 3; 
                else if(i == 0 || i == (LONG-1) || j == 0 || j == (LARG-1))g.tabGrille[i][j].etat = 2;
                break; //NO
                default: break;
            }
            g.tabGrille[i][j].Rectangle.x=taille*i;
            g.tabGrille[i][j].Rectangle.y=taille*j+56;
            g.tabGrille[i][j].x=i;
            g.tabGrille[i][j].y=j;
        }
    }
    return g;

}

carte_t creation_carte(int w, int h,int x,int y){
    carte_t carte;
    int bord = 0; //variable pour savoir si on est en bordure de map
    carte.xcarte=x;
    carte.ycarte=y;
    if(x == 0) bord = 1;
    if(x == (ROWS-1)) bord = 3;
    if(y == 0) bord = 4;
    if(y == (COLUMNS-1)) bord = 2;
    if(x == 0 && y == 0) bord = 8;
    if(x == 0 && y == (COLUMNS-1)) bord = 5;
    if(x == (ROWS-1) && y == 0) bord = 7;
    if(x == (ROWS-1) && y == (COLUMNS-1)) bord = 6;
    if(bord == 2 || bord == 5)printf("%d \n",bord);
    else if(bord == 6)printf("%d \nfin bord\n",bord);
    else printf("%d ",bord);
    carte.grille=creation_grille(w,h,bord);
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
    m.nbtextur = 0;
    m.tabTexture = NULL;
    for(i=0;i<ROWS;i++){
        for(j=0;j<COLUMNS;j++){
            m.tabMap[i][j]=creation_carte(w,h,i,j);
        }
    }
    return m;
}

//map pour test
int afficher_grille(grille_t grille, SDL_Renderer *renderer){
    int i,j;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            SDL_RenderDrawRect(renderer, &(grille.tabGrille[i][j].Rectangle));
            //zone de test
            if(grille.tabGrille[i][j].etat == 3)SDL_RenderFillRect(renderer, &(grille.tabGrille[i][j].Rectangle));

        }
    }
    return 0;
}

int betaAfficherMap(SDL_Renderer *renderer,map_t * map,carte_t * cartec){
    int i,j;
    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            if(cartec->grille.tabGrille[i][j].ntexture != 0){
                SDL_RenderCopy(renderer, map->tabTexture[cartec->grille.tabGrille[i][j].ntexture], NULL,&(cartec->grille.tabGrille[i][j].Rectangle));
            }
        }
    }
    return 0;
}

int afficher_texture(grille_t grille, SDL_Renderer *renderer){
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
    int i,j;
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
                //test
                if(map->tabMap[x][y].nZone==1 || map->tabMap[x][y].nZone==2 || map->tabMap[x][y].nZone==3){
                    for(i=0;i<LONG;i++){
                        for(j=0;j<LARG;j++){
                            map->tabMap[x][y].grille.tabGrille[i][j].ntexture = 1;//plus tard info dans un fichier
                        }
                    }
                }

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

int load_layout(carte_t * c,char * namefile){
    FILE * file;
    file=fopen(namefile,"r");
    char input;
    int i = 0,j = 0;
    if(file){
        while(!feof(file)){
            do{
                fscanf(file,"%c",&input);
                if(input != '\n'){
                    c->grille.tabGrille[i][j].ntexture = atoi(&input);
                    i++;
                }
            }while(input != '\n');
            i=0;
            j++;
        }
    }
    else{
        printf("Fichier inexistant\n");
        return 1;
    }
    printf("Fini!!!!!!!!!!!!\n");
    fclose(file);
    return 0;
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

int afficher_map(SDL_Event event,map_t map, SDL_Renderer *renderer, int *we, int *he, int *etat_map,carte_t * cartec){
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
                    if(map.tabMap[i][j].etat_brouillard != 1){
                        switch(map.tabMap[i][j].nZone){
                            case 1: SDL_SetRenderDrawColor(renderer, 206,206,206,255);break;
                            case 2: SDL_SetRenderDrawColor(renderer, 86,115,154,255);break;
                            case 3: SDL_SetRenderDrawColor(renderer, 153,81,43,255);break;
                            case 4: SDL_SetRenderDrawColor(renderer, 104,157,113,255);break;
                            case 5: SDL_SetRenderDrawColor(renderer, 115,8,0,255);break;
                            default: break;
                        }
                    }else{
                       SDL_SetRenderDrawColor(renderer, 0,0,0,255); 
                    }
                    if(cartec->ycarte == j && cartec->xcarte == i)SDL_SetRenderDrawColor(renderer, 255,255,0,255); 
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

int chargement_Zone(map_t * map,SDL_Renderer *renderer,int nZone){
    int i;
    SDL_Surface * surf;

    if(map->nbtextur != 0){
        for(i=0;i<map->nbtextur;i++){
            SDL_DestroyTexture(map->tabTexture[i]);
            map->tabTexture[i] = NULL;
        }
        free(map->tabTexture);
        map->tabTexture = NULL;
        map->nbtextur = 0;
    }

        switch (nZone)
        {
        case 1:
            map->nbtextur = 1;
            map->tabTexture = malloc(sizeof(SDL_Texture *)*map->nbtextur);
            surf = IMG_Load("texture/terre.png");
            map->tabTexture[i] = SDL_CreateTextureFromSurface(renderer,surf);
            SDL_FreeSurface(surf);
            for(i=1;i<=map->nbtextur;i++){
                surf = IMG_Load("texture/terre.png");//plus tard chercher le path dans un fichier
                map->tabTexture[i] = SDL_CreateTextureFromSurface(renderer,surf);
                SDL_FreeSurface(surf);
            }
            break;
        case 2:
            map->nbtextur = 1;
            map->tabTexture = malloc(sizeof(SDL_Texture *)*map->nbtextur);
            surf = IMG_Load("texture/terre.png");
            map->tabTexture[i] = SDL_CreateTextureFromSurface(renderer,surf);
            SDL_FreeSurface(surf);
            for(i=1;i<=map->nbtextur;i++){
                surf = IMG_Load("texture/terre_nightmare.png");//plus tard chercher le path dans un fichier
                map->tabTexture[i] = SDL_CreateTextureFromSurface(renderer,surf);
                SDL_FreeSurface(surf);
            }
            break;
        case 3:
            //test tab path
            char * tab[5] = {"texture/terre.png","texture/birch_planks_s.png","texture/black_stained_glass.png","texture/blue_glazed_terracotta.png","texture/budding_amethyst.png"};
            //fin test
            map->nbtextur = 4;
            map->tabTexture = malloc(sizeof(SDL_Texture *)*map->nbtextur);
            for(i=0;i<=map->nbtextur;i++){
                surf = IMG_Load(tab[i]);//plus tard chercher le path dans un fichier
                map->tabTexture[i] = SDL_CreateTextureFromSurface(renderer,surf);
                SDL_FreeSurface(surf);
            }
            break;
        
        default:
            map->nbtextur = 0;
            map->tabTexture = NULL;
            break;
        }
    return 0;
}

void lumiere(SDL_Renderer *renderer,carte_t *cartec,case_t *c){
    int i,j;
    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            SDL_SetRenderDrawColor(renderer, 0,0,0,255); 
            if(cartec->grille.tabGrille[i][j].x == c->x && cartec->grille.tabGrille[i][j].y == c->y){
               SDL_SetRenderDrawColor(renderer, 0,0,0,0);  
            }
            else if((cartec->grille.tabGrille[i][j].x == c->x+1 || cartec->grille.tabGrille[i][j].x == c->x-1 || cartec->grille.tabGrille[i][j].x == c->x) && (cartec->grille.tabGrille[i][j].y == c->y+1 || cartec->grille.tabGrille[i][j].y == c->y-1 || cartec->grille.tabGrille[i][j].y == c->y)){
                SDL_SetRenderDrawColor(renderer, 0,0,0,100); 
            }else if((cartec->grille.tabGrille[i][j].x == c->x+2 || cartec->grille.tabGrille[i][j].x == c->x-2 || cartec->grille.tabGrille[i][j].y == c->y+2 || cartec->grille.tabGrille[i][j].y == c->y-2) && ((cartec->grille.tabGrille[i][j].y > c->y-2 && cartec->grille.tabGrille[i][j].y < c->y+2) || (cartec->grille.tabGrille[i][j].x > c->x-2 && cartec->grille.tabGrille[i][j].x < c->x+2))){
                SDL_SetRenderDrawColor(renderer, 0,0,0,170); 
            }else if((cartec->grille.tabGrille[i][j].x == c->x+3 || cartec->grille.tabGrille[i][j].x == c->x-3 || cartec->grille.tabGrille[i][j].y == c->y+3 || cartec->grille.tabGrille[i][j].y == c->y-3) && (cartec->grille.tabGrille[i][j].y == c->y || cartec->grille.tabGrille[i][j].x == c->x)){
                SDL_SetRenderDrawColor(renderer, 0,0,0,220);
            }
            SDL_RenderFillRect(renderer, &(cartec->grille.tabGrille[i][j].Rectangle));
        }
    }
}