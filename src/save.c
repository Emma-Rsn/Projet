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

int save_pos(int xcarte,int ycarte,int xpos,int ypos){
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
        fprintf(fichier, " %d %d %d %d ", xcarte,ycarte,xpos,ypos);
        /*while (fscanf(fichier, "%d", &value) != EOF) {
            count++;
            if (count >= 2 && count <= 5) {
                pos = ftell(fichier);
                fseek(fichier, pos - sizeof(int), SEEK_SET);
                if (count == 2)
                    fprintf(fichier, "%d", xcarte);
                else if (count == 3)
                    fprintf(fichier, "%d", ycarte);
                else if (count == 4)
                    fprintf(fichier, "%d", xpos);
                else if (count == 5)
                    fprintf(fichier, "%d", ypos);
                fseek(fichier, pos, SEEK_SET);
                break;
            }
        }*/

        fclose(fichier);
    }
    return 0;
}


int load_pos(int * xcarte,int * ycarte,int * xpos,int * ypos){
    FILE* fichier = NULL;
    int last = 0;
    fichier = fopen("save/save.txt","r+");
    if(fichier == NULL){
        printf("Erreur a l'ouerture du fichier\n");
    }
    fscanf(fichier, "%d",&last);
    if(last)fscanf(fichier, "%d %d %d %d",xcarte,ycarte,xpos,ypos);
    fclose(fichier);
    return last;
}