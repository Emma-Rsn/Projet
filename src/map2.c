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


#include "../libs/commun.h"

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
    carte.nZone=0;
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
    carte.nbObj = -1;
    return carte;
}

map_t creation_map (int w, int h){
    map_t m;
    int i,j;
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
            SDL_RenderCopy(renderer, map->tabTexture[cartec->grille.tabGrille[i][j].ntexture], NULL,&(cartec->grille.tabGrille[i][j].Rectangle));
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

int creer_map(map_t * map){
    FILE * file;
    int x,y;
    int cpt_z2,cpt_z3,cpt_z4,cpt_z5;
    int choix,choix2;
    srand( time( NULL ) );


    int xZone1 = rand() % 2 + 2;
    int yZone1 = rand() % 2 + 2;

    printf("zone 1 x:%d y:%d\n",xZone1,yZone1);
    map->tabMap[xZone1][yZone1].nZone=1;
    printf("%d\n",map->tabMap[xZone1][yZone1].nZone);

    //Initialisation des zones dans les coins de la map
    map->tabMap[0][0].nZone=5;
    map->tabMap[0][1].nZone=5;
    map->tabMap[1][0].nZone=5;
    map->tabMap[1][1].nZone=5;
    cpt_z5=4;

    map->tabMap[4][0].nZone=4;
    map->tabMap[4][1].nZone=4;
    map->tabMap[5][0].nZone=4;
    map->tabMap[5][1].nZone=4;
    cpt_z4=4;

    map->tabMap[0][4].nZone=3;
    map->tabMap[0][5].nZone=3;
    map->tabMap[1][4].nZone=3;
    map->tabMap[1][5].nZone=3;
    cpt_z3=4;

    map->tabMap[4][4].nZone=2;
    map->tabMap[4][5].nZone=2;
    map->tabMap[5][4].nZone=2;
    map->tabMap[5][5].nZone=2;
    cpt_z2=4;

    map->tabMap[3][0].nZone=4;


    //Cas particulier de la génération où la zone 3 du manoir n'est pas dans le coin en haut à droite
    if(xZone1==3&&yZone1==2){
        
        //Remplissage "logique" des zones en fonction du cas particulier
        map->tabMap[0][2].nZone=5;

        map->tabMap[0][3].nZone=3;
        map->tabMap[1][3].nZone=3;
        map->tabMap[2][2].nZone=3;

        map->tabMap[0][5].nZone=2;
        map->tabMap[1][5].nZone=2; 
        map->tabMap[2][4].nZone=2;
        map->tabMap[2][5].nZone=2;
        map->tabMap[3][3].nZone=2;
        map->tabMap[3][4].nZone=2;
        map->tabMap[3][5].nZone=2;

        map->tabMap[3][1].nZone=4;

        //Choix pour les cartes du manoir (zone 3)
        choix=rand() % 2;
        if(!choix){
            map->tabMap[1][2].nZone=3;
            map->tabMap[2][3].nZone=2;
        }
        else{
            map->tabMap[1][2].nZone=5;
            map->tabMap[2][3].nZone=3;
        }
        //Choix pour les cartes adjacentes de la plage ou de la foret (zone 2 et zone 4)
        choix=rand() % 3;
        switch(choix){
            //Cas si on rempli 1 case de la zone plage et 3 de la zone foret
            case 0:
            choix2=rand() % 2;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=4;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=4;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            
            break;
            //Cas si on rempli 2 cases de la zone plage et 2 de la zone foret
            case 1:
            choix2=rand() % 3;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=4;
                map->tabMap[4][2].nZone=2;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else if(choix2==1){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            //Troisième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=4;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=2;

            }
            break;
            //Cas si on rempli 3 cases de la zone plage et 1 de la zone foret
            case 2:
            choix2=rand() % 2;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=2;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=2;
 
            }
            break;
        }
        //Choix pour les cartes adjacentes de la foret et de la grotte (zone 4 et zone 5)
        choix=rand() % 2;
        if(map->tabMap[2][2].nZone==1){
            choix=1;
        }
        if(choix==0){
            map->tabMap[2][1].nZone=5;
            map->tabMap[2][0].nZone=4;
        }
        else{
            map->tabMap[2][1].nZone=4;
            map->tabMap[2][0].nZone=5;
        }
    }





    //Cas général
    else{
        map->tabMap[xZone1-1][yZone1].nZone=3;
        cpt_z3++;
        map->tabMap[xZone1][yZone1-1].nZone=4;
        cpt_z4++;
        map->tabMap[xZone1][yZone1+1].nZone=2;
        cpt_z2++;

        map->tabMap[3][1].nZone=4;
        cpt_z4++;
        
        choix=rand() % 2;
        if(choix==0){
            map->tabMap[xZone1+1][yZone1].nZone=2;
            cpt_z2++;
        }
        else{
            map->tabMap[xZone1+1][yZone1].nZone=4;
            cpt_z4++;
        }

        if(xZone1==2&&yZone1==2){
            map->tabMap[3][3].nZone=2;
            cpt_z2++;
        }


        //Remplissage des cases adjacentes la zone manoir et grotte (zone 3 et 5)
        if(xZone1==2&&yZone1==3){
            map->tabMap[0][3].nZone=3;
        }
        else{
            map->tabMap[1][3].nZone=3;
        }
        for(x=2;x>=0;x--){
            for(y=3;y>=0;y--){
                if(map->tabMap[x][y].nZone==0){
                    map->tabMap[x][y].nZone=5;
                    cpt_z5++;
                }
            }
        }

        //Remplissage des cases adjacentes la zone manoir et plage (zone 3 et 2)
        for(x=2;x<=3;x++){
            for(y=3;y<=5;y++){
                if(map->tabMap[x][y].nZone==0){
                    map->tabMap[x][y].nZone=2;
                    cpt_z2++;
                }
            }
        }

        //Choix pour les cartes adjacentes de la plage ou de la foret (zone 2 et zone 4)
        choix=rand() % 3;
        switch(choix){
            //Cas si on rempli 1 case de la zone plage et 3 de la zone foret
            case 0:
            choix2=rand() % 2;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=4;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=4;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            
            break;
            //Cas si on rempli 2 cases de la zone plage et 2 de la zone foret
            case 1:
            choix2=rand() % 3;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=4;
                map->tabMap[4][2].nZone=2;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else if(choix2==1){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=4;

            }
            //Troisième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=4;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=2;

            }
            break;
            //Cas si on rempli 3 cases de la zone plage et 1 de la zone foret
            case 2:
            choix2=rand() % 2;
            //Première possibilité de remplissage
            if(choix2==0){
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=2;
                map->tabMap[5][2].nZone=4;

            }
            //Deuxième possibilité de remplissage
            else{
                map->tabMap[4][3].nZone=2;
                map->tabMap[5][3].nZone=2;
                map->tabMap[4][2].nZone=4;
                map->tabMap[5][2].nZone=2;
 
            }
            break;
        }
        //Choix pour les cartes adjacentes de la foret et de la grotte (zone 4 et zone 5)
        choix=rand() % 2;
        if(map->tabMap[2][2].nZone==1)choix=1;
        if(choix==0){
            map->tabMap[2][1].nZone=5;
            map->tabMap[2][0].nZone=4;
        }
        else{
            map->tabMap[2][1].nZone=4;
            map->tabMap[2][0].nZone=5;
        }
    }

    //Sauvegarde de la map dans un fichier
    file=fopen("save/map.txt","w");
    if(file){
        for(x=0;x<ROWS;x++){
            for(y=0;y<COLUMNS;y++){
                fprintf(file,"%d",map->tabMap[x][y].nZone);
                if(y!=COLUMNS-1){
                    fprintf(file," ");
                }
                
            }
            fprintf(file,"\n");
        }

        


        fclose(file);
        return 0;
    }
    else{
        printf("Fichier inexistant\n");
        return 1;
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
                            map->tabMap[x][y].grille.tabGrille[i][j].ntexture = 0;//plus tard info dans un fichier
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
        creer_map(map);
        return 0;
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
    printf("\n");
    return 0;

}

int load_layout(carte_t *c, char *namefile) {
    FILE *file;
    file = fopen(namefile, "r");
    char input;
    int i = 0, j = 0;
    int res; // Pour stocker le résultat de fscanf

    if (file) {
        while ((res = fscanf(file, "%c", &input)) != EOF) { // Utilise le résultat de fscanf pour contrôler la boucle
            if (input != '\n') {
                if (i < LONG && j < LARG) { 
                    c->grille.tabGrille[i][j].ntexture = input - '0';
                    i++;
                }
            } else {
                i = 0;
                j++;
                if (j >= LARG) break; // Sort de la boucle si on dépasse la limite de lignes
            }
        }
    } else {
        printf("Fichier inexistant\n");
        return 1;
    }
    fclose(file);
    return 0;
}

float min(float a, float b) {
    return (a < b) ? a : b;
}

int afficher_map(SDL_Event event,map_t map, SDL_Renderer *renderer, int *we, int *he, int *etat_map,carte_t * cartec){
    int i, j;

    SDL_Rect Rectangle;
    SDL_Rect Rectanglep;

    // Marges
    float margeX = (*we) * 0.1;
    float margeY = (*he) * 0.1;

    // Largeur et hauteur utilisables
    float largeurUtilisable = (*we) - 2 * margeX;
    float hauteurUtilisable = (*he) - 2 * margeY;

    // Taille de chaque carré
    float taille_carre = min(largeurUtilisable, hauteurUtilisable) / 6;

    //Taille du petit carré de l'emplacement actuel
    float taille_pcarre = taille_carre/3;

    // Coordonnées du premier carré
    float firstX = margeX + ((*we) - 2 * margeX - taille_carre * 6) / 2;
    float firstY = margeY + ((*he) - 2 * margeY - taille_carre * 6) / 2;
    Rectangle.x = (int)firstX;
    Rectangle.y = (int)firstY;
    Rectangle.w = (int)taille_carre;
    Rectangle.h = (int)taille_carre;

    //Initialisation du petit carré de l'emplacement actuel
    Rectanglep.x = (int)firstX + (taille_pcarre);
    Rectanglep.y = (int)firstY + (taille_pcarre);
    Rectanglep.w=(int)taille_pcarre;
    Rectanglep.h=(int)taille_pcarre;

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
                    Rectangle.x = (int)(firstX + j * taille_carre);
                    SDL_RenderFillRect(renderer, &Rectangle);
                    if(cartec->ycarte == j && cartec->xcarte == i){
                        SDL_SetRenderDrawColor(renderer, 255,255,0,255);
                        Rectanglep.x = Rectangle.x+taille_pcarre;
                        Rectanglep.y = Rectangle.y+taille_pcarre;;
                        SDL_RenderFillRect(renderer, &Rectanglep); 
                    }
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
        switch (nZone)
        {
        case 1:
            creation_tab_texture(map,renderer,1,0);
            break;
        case 2:
            printf("2 %d\n",nZone);
            creation_tab_texture(map,renderer,2,0);
            break;
        case 3:
            creation_tab_texture(map,renderer,3,0);
            break;
        case 4:
            creation_tab_texture(map,renderer,4,0);
            break;
        case 5:
            creation_tab_texture(map,renderer,5,0);
            break;
        
        default:
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

int nb_texture_chargement(map_t *map, char* namefile){
    FILE * file;
    int nb_zone[5] = {0,0,0,0,0};
    char line[80];
    int i=-1;

    //check = regcomp(&rx,"^[:number:]N[:number:]", 0);

    file=fopen(namefile,"r");

    if(file){
        while (fgets(line, 80, file)){
            if(line[0]>='0'&&line[0]<='5') {
                i=atoi(line)-1;
                fgets(line, 80, file);
                nb_zone[i]=atoi(line);
            }     
        }

        for(i=0;i<5;i++){
            map->nbTexture[i]=nb_zone[i];
        }
    }
    else{
        printf("Fichier inexistant\n");
        return 1;
    }
    fclose(file);
    return 0;
}

int detruire_tab_path(map_t *map){
    int i,k;
    if(map->tabPath!=NULL){
        for (i=0;i<NB_ZONE;i++){
            for(k=0;k<map->nbTexture[i];k++){
                free(map->tabPath[i][k]);
            }
            free(map->tabPath[i]);
        }
        free(map->tabPath);
        map->tabPath=NULL;
    }
    return 0;
}

int creation_tab_path(map_t *map,char * namefile){
    FILE * file;
    int i = 0;
    int j,k=-1;
    char line[40];

    map->tabPath = malloc(sizeof(char ** )*NB_ZONE);
    for (i=0;i<NB_ZONE;i++){
        map->tabPath[i] = malloc(sizeof(char *)*map->nbTexture[i]);
    }
    file=fopen(namefile,"r");
    i=-1;

    if(file){
        while (fgets(line, 40, file)){
            if(line[0]>='0'&&line[0]<='5') {
                i=atoi(line)-1;
                k=-1;
                fgets(line, 80, file);
            }
            else{
                if(i >= 0 && i < NB_ZONE && k < map->nbTexture[i] - 1){
                    k++;
                    for(j=0; line[j]!='\n' && j < 39; j++){}
                    line[j]='\0';
                    map->tabPath[i][k]=malloc(sizeof(char)*strlen(line)+1);
                    strcpy(map->tabPath[i][k],line);
                }
            }
        }
    }
    else{
        printf("Fichier inexistant\n");
        return 1;
    }
    fclose(file);
    return 0;


}

int creation_tab_texture(map_t *map, SDL_Renderer *renderer, int nbZone, int eop) {
    int i = 0;
    SDL_Surface *surf;

    if(nbZone < 1 || nbZone > NB_ZONE) {
        printf("Erreur : nbZone hors limites\n");
        return 1;
    }

    // Libération des textures précédentes si elles existent
    if(map->tabTexture != NULL) {
        int nbTexturesToDestroy = eop == 1 ? NB_ZONE : map->nbTexture[map->zoneChargee-1];
        for(i = 0; i < nbTexturesToDestroy; i++) {
            if(map->tabTexture[i] != NULL) {
                SDL_DestroyTexture(map->tabTexture[i]);
                map->tabTexture[i] = NULL;
            }
        }
        free(map->tabTexture);
        map->tabTexture = NULL;
    }

    if(eop != 1) {
        map->zoneChargee = nbZone;
        map->tabTexture = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * map->nbTexture[nbZone-1]);

        if(map->tabTexture == NULL) {
            printf("Erreur d'allocation mémoire pour map->tabTexture\n");
            return 1;
        }

        for(i = 0; i < map->nbTexture[map->zoneChargee-1]; i++) {
            surf = IMG_Load(map->tabPath[map->zoneChargee-1][i]);
            if (surf == NULL) {
                fprintf(stderr, "Erreur de chargement de l'image : %s\n", SDL_GetError());
            }
            map->tabTexture[i] = SDL_CreateTextureFromSurface(renderer, surf);
            SDL_FreeSurface(surf);
        }
    }
    return 0;
}