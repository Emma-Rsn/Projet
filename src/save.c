//
//save.c
//Created by Moreau Enzo
//

/**
*\file save.c
*\brief programme pour la sauvegarde 
*\author Moreau Enzo
*\date  09 Fevrier 2024
*\version 1.0
*
*/



#include "../libs/commun.h"


/**
*
*\fn int save_settings(void)
*\brief fonction de sauvegarde des parametres
*
*/

//fonction de sauvegarde des parametres
int save_settings(void){
    FILE* fichier = NULL;
    fichier = fopen("save/settings.txt","r+");
    if(fichier == NULL){
        printf("Erreur a l'ouerture du fichier\n");
    }
    fprintf(fichier, "1920 1080 \n");
    fclose(fichier);
    return 0;
}

/**
*
*\fn int load_settings(int * lEcran,int * LEcran)
*\param lEcran Largeur de l'ecran
*\param LEcran Longueur de l'ecran
*\brief fonction de sauvegarde des parametres
*
*/

int load_settings(int * wEcran,int * hEcran){
    FILE* fichier = NULL;
    fichier = fopen("save/settings.txt","r+");
    if(fichier == NULL){
        printf("Erreur a l'ouerture du fichier\n");
    }
    fscanf(fichier, "%d %d",wEcran,hEcran);
    fclose(fichier);
    return 0;
}

int save_pos(int xcarte,int ycarte,p_mv pmv,map_t map){
    FILE* fichier = NULL;
    fichier = fopen("save/save.txt","r+");
    if(fichier == NULL){
        printf("Erreur a l'ouerture du fichier\n");
        return -1;
    }
    else if (fichier != NULL) {
        //int count = 0; 
        int value;   
        //long int pos; 

        fscanf(fichier, "%d", &value);
        if (value == 0) {
            rewind(fichier);
            fprintf(fichier, "%d", 1);
        }
        fprintf(fichier, " %d %d %d %d %d %d %d\n", xcarte,ycarte,pmv.c->x,pmv.c->y,*(pmv.d),*(pmv.NightP),*pmv.equipe[0]->pv);
        fprintf(fichier, "%d %d %d %d %d %d", map.Zone2,map.Zone3,map.Zone4,map.Zone5,map.argent,map.nvEquipe);

        fclose(fichier);
    }
    return 0;
}


int load_pos(int * xcarte,int * ycarte,int * xpos,int * ypos,map_t * map,int * pv,p_mv * pmv,int ** tabparam){
    FILE* fichier = NULL;
    int last = 0;
    fichier = fopen("save/save.txt","r+");
    if(fichier == NULL){
        printf("Erreur a l'ouerture du fichier\n");
    }
    fscanf(fichier, "%d",&last);
    if(last){
        fscanf(fichier, " %d %d %d %d %d %d %d\n",xcarte,ycarte,xpos,ypos,pmv->d,pmv->NightP,pv);
        fscanf(fichier, "%d %d %d %d %d %d", tabparam[0],tabparam[1],tabparam[2],tabparam[3],tabparam[4],tabparam[5]);
    }
    fclose(fichier);
    return last;
}

/*
new load layout  test

save :
    equipe
        pv equipe
    leader
    azerty qwerty fleche
    ennemi mort
    relique
    verif cauchemar carte / perso?
    variable d'exploration

obj :
    transition :
        sous marine
        manoir
        grotte


afficher niv Zone dans la carte !

finir generalisation save & load

chargement layout objet + cas particulier

choix leader (dans le game over)(Lina ?)

malloc save load in pmv map

*/