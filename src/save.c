//
// save.c
// Created by Moreau Enzo
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

// fonction de sauvegarde des parametres
int save_settings(void)
{
    FILE *fichier = NULL;
    fichier = fopen("save/settings.txt", "r+");
    if (fichier == NULL)
    {
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

int load_settings(int *wEcran, int *hEcran)
{
    FILE *fichier = NULL;
    fichier = fopen("save/settings.txt", "r+");
    if (fichier == NULL)
    {
        printf("Erreur a l'ouerture du fichier\n");
    }
    fscanf(fichier, "%d %d", wEcran, hEcran);
    fclose(fichier);
    return 0;
}

int save_pos(int xcarte, int ycarte, p_mv pmv, map_t map)
{
    FILE *fichier = NULL;
    fichier = fopen("save/save.txt", "r+");
    if (fichier == NULL)
    {
        printf("Erreur a l'ouerture du fichier\n");
        return -1;
    }
    else if (fichier != NULL)
    {
        // int count = 0;
        int value;
        // long int pos;

        fscanf(fichier, "%d", &value);
        if (value == 0)
        {
            rewind(fichier);
            fprintf(fichier, "%d", 1);
        }
        fprintf(fichier, " %d %d %d %d %d %d %d\n", xcarte, ycarte, pmv.c->x, pmv.c->y, *(pmv.d), *(pmv.NightP), *pmv.equipe[0]->pv);
        fprintf(fichier, "%d %d %d %d %d %d\n", map.Zone2, map.Zone3, map.Zone4, map.Zone5, map.argent, map.nvEquipe);
        fprintf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", map.listeArtefact[0]->equipe, map.listeArtefact[1]->equipe, map.listeArtefact[2]->equipe, map.listeArtefact[3]->equipe, map.listeArtefact[4]->equipe, map.listeArtefact[5]->equipe, map.listeArtefact[6]->equipe, map.listeArtefact[7]->equipe, map.listeArtefact[8]->equipe, map.listeArtefact[9]->equipe);
        fprintf(fichier, "%d %d %d %d %d %d %d %d %d %d", map.listeArtefact[0]->possession, map.listeArtefact[1]->possession, map.listeArtefact[2]->possession, map.listeArtefact[3]->possession, map.listeArtefact[4]->possession, map.listeArtefact[5]->possession, map.listeArtefact[6]->possession, map.listeArtefact[7]->possession, map.listeArtefact[8]->possession, map.listeArtefact[9]->possession);

        fclose(fichier);
    }
    return 0;
}

int load_pos(int *xcarte, int *ycarte, int *xpos, int *ypos, map_t *map, int *pv, p_mv *pmv, int **tabparam)
{
    FILE *fichier = NULL;
    int last = 0;
    fichier = fopen("save/save.txt", "r+");
    if (fichier == NULL)
    {
        printf("Erreur a l'ouerture du fichier\n");
    }
    fscanf(fichier, "%d", &last);
    if (last)
    {
        fscanf(fichier, " %d %d %d %d %d %d %d\n", xcarte, ycarte, xpos, ypos, pmv->d, pmv->NightP, pv);
        fscanf(fichier, "%d %d %d %d %d %d\n", tabparam[0], tabparam[1], tabparam[2], tabparam[3], tabparam[4], tabparam[5]);
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", tabparam[6], tabparam[7], tabparam[8], tabparam[9], tabparam[10], tabparam[11], tabparam[12], tabparam[13], tabparam[14], tabparam[15]);
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d", tabparam[16], tabparam[17], tabparam[18], tabparam[19], tabparam[20], tabparam[21], tabparam[22], tabparam[23], tabparam[24], tabparam[25]);
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

chargement layout objet + cas particulier

choix leader (dans le game over)(Lina ?)

malloc save load in pmv map

*/