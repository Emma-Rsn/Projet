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

int save_pos(int xcarte, int ycarte, p_mv pmv, map_t map,int touche)
{
    int i,y;
    for(i = 0;pmv.equipe[i] && i < 4;i++);
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
            value = 1;

            
        }
        if(value == 2){//rejoue
            int leader = newLeader(pmv); 
            fprintf(fichier," %d %d %d %d\n",map.argent,map.nvEquipe,touche,leader);
            fprintf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", map.listeArtefact[0]->equipe, map.listeArtefact[1]->equipe, map.listeArtefact[2]->equipe, map.listeArtefact[3]->equipe, map.listeArtefact[4]->equipe, map.listeArtefact[5]->equipe, map.listeArtefact[6]->equipe, map.listeArtefact[7]->equipe, map.listeArtefact[8]->equipe, map.listeArtefact[9]->equipe);
            fprintf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", map.listeArtefact[0]->possession, map.listeArtefact[1]->possession, map.listeArtefact[2]->possession, map.listeArtefact[3]->possession, map.listeArtefact[4]->possession, map.listeArtefact[5]->possession, map.listeArtefact[6]->possession, map.listeArtefact[7]->possession, map.listeArtefact[8]->possession, map.listeArtefact[9]->possession);
        }if(value == 1){//sauvegarde classique
            fprintf(fichier, " %d %d %d %d %d %d %d\n", xcarte, ycarte, pmv.c->x, pmv.c->y, *(pmv.d), *(pmv.NightP), *pmv.equipe[0]->pv);
            fprintf(fichier, "%d %d %d %d %d %d %d %d\n", map.Zone2, map.Zone3, map.Zone4, map.Zone5, map.argent, map.nvEquipe,touche,pmv.equipe[0]->type);
            fprintf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", map.listeArtefact[0]->equipe, map.listeArtefact[1]->equipe, map.listeArtefact[2]->equipe, map.listeArtefact[3]->equipe, map.listeArtefact[4]->equipe, map.listeArtefact[5]->equipe, map.listeArtefact[6]->equipe, map.listeArtefact[7]->equipe, map.listeArtefact[8]->equipe, map.listeArtefact[9]->equipe);
            fprintf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", map.listeArtefact[0]->possession, map.listeArtefact[1]->possession, map.listeArtefact[2]->possession, map.listeArtefact[3]->possession, map.listeArtefact[4]->possession, map.listeArtefact[5]->possession, map.listeArtefact[6]->possession, map.listeArtefact[7]->possession, map.listeArtefact[8]->possession, map.listeArtefact[9]->possession);
            fprintf(fichier,"%d",i);
            for(y = 1;y<i;y++){
                fprintf(fichier," %d %d",pmv.equipe[y]->type,*pmv.equipe[y]->pv);
            }
            fprintf(fichier,"\n");
            fprintf(fichier,"%d %d %d\n",map.plongee,map.cle,map.talisman);

        }
        
        fclose(fichier);
    }
    return 0;
}

int load_pos(int *xcarte, int *ycarte, int *xpos, int *ypos, map_t *map, int *pv, p_mv *pmv, int **tabparam,int * touche,int * leader)
{
    int y;
    FILE *fichier = NULL;
    int last = 0;
    fichier = fopen("save/save.txt", "r+");
    if (fichier == NULL)
    {
        printf("Erreur a l'ouerture du fichier\n");
    }
    fscanf(fichier, "%d", &last);
    if (last == 1)
    {
        fscanf(fichier, " %d %d %d %d %d %d %d\n", xcarte, ycarte, xpos, ypos, pmv->d, pmv->NightP, pv);
        fscanf(fichier, "%d %d %d %d %d %d %d %d\n", tabparam[0], tabparam[1], tabparam[2], tabparam[3], tabparam[4], tabparam[5],touche,leader);
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", tabparam[6], tabparam[7], tabparam[8], tabparam[9], tabparam[10], tabparam[11], tabparam[12], tabparam[13], tabparam[14], tabparam[15]);
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", tabparam[16], tabparam[17], tabparam[18], tabparam[19], tabparam[20], tabparam[21], tabparam[22], tabparam[23], tabparam[24], tabparam[25]);
        fscanf(fichier, "%d",tabparam[26]);
        for(y = 0;y<((*tabparam[26]-1)*2);y=y+2){//32 max
            fscanf(fichier," %d %d",tabparam[27+y],tabparam[28+y]);
        }
        fscanf("\n%d %d %d\n",tabparam[33],tabparam[34],tabparam[35]);
    }else if(last == 2){
        fscanf(fichier, "%d %d %d %d\n", tabparam[4], tabparam[5],touche,leader);
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", tabparam[6], tabparam[7], tabparam[8], tabparam[9], tabparam[10], tabparam[11], tabparam[12], tabparam[13], tabparam[14], tabparam[15]);
        fscanf(fichier, "%d %d %d %d %d %d %d %d %d %d\n", tabparam[16], tabparam[17], tabparam[18], tabparam[19], tabparam[20], tabparam[21], tabparam[22], tabparam[23], tabparam[24], tabparam[25]);
        rewind(fichier);
        fprintf(fichier, "%d", 0);
    }
    fclose(fichier);
    return last;
}

void save_ennemi(carte_t cartec,obj_t ennemi){
    if(ennemi.typeObj == 2 && (boolTousMort((ennemi_t *)ennemi.tabObj[0]))){
        FILE *fichier = NULL;
        fichier = fopen("save/ennemi.txt", "a");
        if (fichier == NULL)
        {
            printf("Erreur a l'ouerture du fichier\n");
            return;
        }
        fprintf(fichier,"%d %d %d %d\n",cartec.xcarte,cartec.ycarte,ennemi.cas->x,ennemi.cas->y);
        fclose(fichier);
    }
}
void load_ennemi(map_t * map){
    FILE *fichier = NULL;
    fichier = fopen("save/ennemi.txt", "r+");
    if (fichier == NULL)
    {
        fclose(fichier);
        return;
    }
    int xc,yc,x,y,i;
    while(fscanf(fichier,"%d %d %d %d\n",&xc,&yc,&x,&y) != EOF){
        for(i = 0 ;i < (*map).tabMap[xc][yc].nbObj && !boolMemeCase(*(*map).tabMap[xc][yc].tabObj[i]->cas,(*map).tabMap[xc][yc].grille.tabGrille[x][y]) ;i++);
        if(i < (*map).tabMap[xc][yc].nbObj){
            dest_obj(&(*map).tabMap[xc][yc],i);
        }
    }
    fclose(fichier);
}

//param = 1 pour garder la progression et = 0 pour effacer la progression
void nouvelle_partie(int param){
    FILE *fichier = fopen("save/save.txt", "w");
    if(param == 1){
        fprintf(fichier, "%d", 2);
    }else{
        fprintf(fichier, "%d", 3);
    }
    system("rm save/ennemi.txt");
    fclose(fichier);
}

void effacer_sauvg(){
    FILE *fichier = fopen("save/save.txt", "w");
    fprintf(fichier, "%d", 0);
    fclose(fichier);
}



    /*
new load layout  test

save :
    ennemi mort
    layout obj et load texture

boss boss /2

chargement layout objet + cas particulier

rejouer :
    bug artefact
    bug layout texture

bug plusieurs loot sur la carte

*/