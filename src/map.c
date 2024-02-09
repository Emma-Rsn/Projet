#include "../libs/map.h"

//fonction de creation de case

case_t * creation_case(){
    case_t *c=malloc(sizeof(case_t));
    c->etat=0;
    return c;
}

//fonction de creation de carte
carte_t * creation_carte(){
    carte_t *c=malloc(sizeof(carte_t));
    c->etat_brouillard=1;
    c->nord=NULL;
    c->sud=NULL;
    c->est=NULL;
    c->ouest=NULL;
    return c;
}

//fonction qui attribue une couleur à une carte

int color_carte(carte_t*c,SDL_Color Color){
    c->bgColor=Color;
    return 0;
}

//fonction créant les liens entre les cartes
int lien_carte(carte_t map[ROW][COLUMN]){
    int x,y;
    for(x=0;x<ROW;x++){
        for(y=0;y<COLUMN;y++){
            if(y!=0){
                map[x][y].ouest=&(map[x][y-1]);
            }
            if(y!=COLUMN-1){
                map[x][y].est=&(map[x][y+1]);
            }
            if(x!=0){
                map[x][y].nord=&(map[x-1][y]);
            }
            if(x!=ROW-1){
                map[x][y].sud=&(map[x+1][y]);
            }
        }
    }
    return 0;
}

//fonction de creation de la matrice de cartes

int creation_matrice(carte_t map[ROW][COLUMN]){
    int i,j;

    for(i=0;i<ROW;i++){
        for(j=0;j<COLUMN;j++){
            map[i][j]=*(creation_carte());
        }
    }
    return 0;

}

//fonction de destruction d'une case

int destroy_case(case_t* c){
    free(c);
    c=NULL;
    return 0;
}

//fonction de destruction d'une carte
 
 int destroy_carte(carte_t*carte){
    int i,j;
    for(i=0;i<LONG;i++){
        for(j=0;j<LARG;j++){
            destroy_case(&(carte->grille[i][j]));
        }
    }
    free (carte);
    carte=NULL;
    return 0;
 }

//fontion de destruction de la matrice de carte

int destroy_map(carte_t map[ROW][COLUMN]){
    int i,j;
    for(i=0;i<ROW;i++){
        for(j=0;j<COLUMN;j++){
            destroy_carte(&(map[i][j]));
        }
    }
    return 0;
}

//fonction d'affichage du bg de la carte actuelle au format cadriallge



//fonction qui gere la transition entre 2 carte de la matrice


//fonction d'affichage de la matrice de carte