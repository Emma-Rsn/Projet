#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>

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

int load_settings(int * lEcran,int * LEcran){
    FILE* fichier = NULL;
    fichier = fopen("save/settings.txt","r+");
    if(fichier == NULL){
        printf("Erreur a l'ouerture du fichier\n");
    }
    fscanf(fichier, "%d %d",lEcran,LEcran);
    fclose(fichier);
    return 0;
}