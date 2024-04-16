#include "../libs/commun.h"

obj_t * init_obj(case_t * c,int indText,int type,...){
    obj_t * newObj = malloc(sizeof(obj_t));
    newObj->cas = c;
    newObj->indTexture = indText;
    newObj->typeObj = type;
    va_list args;
    va_start(args, type);
    int n; //nombre d'éléments propre a l'objets
    int i;
    switch(type){
        case 0 : //cas d'un objet de décors avec collision
            n = -1;
            newObj->cas->etat = 0;
            break;
        case 1 : //cas d'un objet de décors sans collision
            n = -1;
            newObj->cas->etat = 1;
            break;
        case 2 : //cas d'un ennemi
            n = 1;
            newObj->cas->etat = 0;
            break;
        case 3 : //cas d'un objet avec dialogue avec collision
            n = 1;
            newObj->cas->etat = 0;
            break;
        case 4 : //cas d'un objet avec dialogue sans collision
            n = 1;
            newObj->cas->etat = 1;
            break;
        default://cas d'un objet inconnu
            n = -1;
            break;
    }
    for (i = 0; i < n; i++) {
        newObj->tabObj[i] = va_arg(args, void *);
    }
    va_end(args);
    return newObj;
}

int load_obj(carte_t *c, char *namefile){
    int x,y,indText,type;
    FILE * file;
    int i;

    char nom[20];
    int pv,vitesse,camp,indice_portait,indice_sprite,typeE,temps_recharge_max,puissance,forme;
    int nbCombattant;

    file=fopen(namefile,"r");

    if(file){
        /*fscanf(file,"%d %d %d %d ",&x,&y,&indText,&type);
        printf("%d %d %d %d \n",x,y,indText,type);*/
        while(fscanf(file,"%d %d %d %d ",&x,&y,&indText,&type)!= EOF){
            switch(type){
                case 0 :
                    c->tabObj[c->nbObj]=init_obj(&c->grille.tabGrille[x][y],indText,type);
                    c->nbObj++; 
                    break;
                case 1 :
                    c->tabObj[c->nbObj]=init_obj(&c->grille.tabGrille[x][y],indText,type);
                    c->nbObj++; 
                    break;
                case 2 :
                    fscanf(file,"%s %d %d %d %d %d %d %d %d %d %d ",nom,&pv,&vitesse,&camp,&indice_portait,&indice_sprite,&typeE,&temps_recharge_max,&puissance,&forme,&nbCombattant);
                    //printf("%s %d %d %d %d %d %d %d %d %d %d\n",nom,pv,vitesse,camp,indice_portait,indice_sprite,typeE,temps_recharge_max,puissance,forme,nbCombattant);
                    ennemi_t * newEnnemi=init_ennemi(nom,pv,vitesse,camp,indice_portait,indice_sprite,typeE,temps_recharge_max,puissance,forme);
                    for(i=1;i<=nbCombattant;i++){
                        fscanf(file,"%s %d %d %d %d %d %d %d %d %d",nom,&pv,&vitesse,&camp,&indice_portait,&indice_sprite,&typeE,&temps_recharge_max,&puissance,&forme);
                        newEnnemi->combattant[i]=init_combattant(nom,pv,vitesse,camp,indice_portait,indice_sprite,typeE,temps_recharge_max,puissance,forme);
                    }
                    c->tabObj[c->nbObj]=init_obj(&c->grille.tabGrille[x][y],indText,type,newEnnemi);
                    c->nbObj++;
                    break;
            }
            fscanf(file,"\n");
        }
    }
    else{
        printf("Fichier inexistant\n");
        fclose(file);
        return 1;
    }
    fclose(file);
    return 0;


}

void affObj(SDL_Renderer *renderer,obj_t * o,map_t map){
    SDL_RenderCopy(renderer, map.tabTexture[o->indTexture], NULL, &(o->cas->Rectangle));
}

void affTabObj(SDL_Renderer *renderer,map_t map,carte_t * carte){
    int i;
    int n = 0;
    if(map.Nightmare == 1)n=map.nbN;
    for(i = 0; i < carte->nbObj;i++){
        SDL_RenderCopy(renderer, map.tabTexture[(carte->tabObj[i]->indTexture)+n], NULL, &(carte->tabObj[i]->cas->Rectangle));
    }
}

ennemi_t * init_ennemi(char* nom,int pv,int vitesse,int camp,int indice_portrait,int indice_sprite,int type,int temps_recharge_max,int puissance,int forme){
    ennemi_t * en = malloc(sizeof(ennemi_t));
    en->nom = malloc(strlen(nom)+1);
    strcpy(en->nom,nom);
    en->combat=0;
    en->pv=pv;
    en->type=type;
    en->vitesse=vitesse;
    en->mort=0;
    en->temps_recharge_max=temps_recharge_max;
    en->status=0;
    int i;
    for(i=0;i<4;i++){
        en->combattant[i]=NULL;
    }
    en->combattant[0]=init_combattant(en->nom,en->pv,en->vitesse,1,indice_portrait,indice_sprite,type,en->temps_recharge_max,puissance,forme);
    en->indice_portrait=indice_portrait;
    en->indice_sprite=indice_sprite;
    en->forme=forme;
    return en;
}

void Boss(obj_t * boss,p_mv * Leader){
    if(boss->typeObj == 2){
        printf("blabla\n");
        if(((ennemi_t *)boss->tabObj[0])->forme == 3){
            srand( time( NULL ) );
            int type = ((ennemi_t *)boss->tabObj[0])->type;
            int i;
            for(i = 0;Leader->equipe[i]->type != type && Leader->equipe[i];i++){
                printf("test\n");
            }
            if(Leader->equipe[i]->type != type){
                do{
                    type = rand()%4;
                }while(Leader->equipe[i]->type == type);
            }
            dest_ennemi((boss->tabObj[0]));
            switch (type)
            {
            case 0://Alex
            boss->indTexture = 0;
            boss->tabObj[0]=init_ennemi("Alex",100,50,0,13,12,0,2,15,0);
                break;

            case 1://Lou
            boss->indTexture = 0;
            boss->tabObj[0]=init_ennemi("Lou",100,50,0,13,12,0,2,15,0);
                break;

            case 2://Finn
            boss->indTexture = 0;
            boss->tabObj[0]=init_ennemi("Finn",100,50,0,13,12,0,2,15,0);
                break;

            case 3://Ada
            boss->indTexture = 0;
            boss->tabObj[0]=init_ennemi("Ada",100,50,0,13,12,0,2,15,0);
                break;
            
            default:
                break;
            }
        }
    }
}

void dest_obj(carte_t * c,int ind){
    if(c->nbObj > 0){
        switch(c->tabObj[ind]->typeObj){
            case 2 : dest_ennemi(((ennemi_t *)(c->tabObj[ind]->tabObj[0])));break;

            default : break;

        }
        if(c->nbObj == 1){
            free(c->tabObj[ind]);
            c->tabObj[ind] = NULL;
            c->nbObj--;
        }else{
            free(c->tabObj[ind]);
            int i;
            for(i=ind;i<c->nbObj-1;i++){
                c->tabObj[i] = c->tabObj[i+1];
            }
            c->nbObj--;
        }
    }
}

void dest_all_obj(map_t m){
    int i,j;
    for(i = 0;i<ROWS;i++){
        for(j = 0;j < COLUMNS;j++){
            while(m.tabMap[i][j].nbObj){
                dest_obj(&m.tabMap[i][j],0);
            }
        }
    }
}


void dest_ennemi(ennemi_t * en){
    int i;
    int nb_ennemi=0;
    for (i=0;i<4;i++){
        if(en->combattant[i]!=NULL){
            nb_ennemi++;
        }
    }

    for(i=0;i<nb_ennemi;i++){
        desctruction_combattant(en->combattant[i]); 
    }

    free(en->nom);
    free(en);
}





int boolcol (case_t * obj_c,p_mv * pp){
    if(pp->c->x+1 == obj_c->x && pp->c->y == obj_c->y){ //verifie case droite
        return 1;
    }else if(pp->c->x-1 == obj_c->x && pp->c->y == obj_c->y){ //verifie case gauche
        return 1;
    }else if(pp->c->y+1 == obj_c->y && pp->c->x == obj_c->x){ //verifie case bas
        return 1;
    }else if(pp->c->y-1 == obj_c->y && pp->c->x == obj_c->x){ //verifie case haut
        return 1;
    }
    return 0;
}






/**
*
*\fn artefact_t * init_artefact(char* nom, int possession,char * descriptif,int indice,int prix,int indice_texture)
*\param nom nom de l'artefact
*\param possession entier pour savoir si 'lon possede ou non l'artefact
*\param descriptif dexcription de l'artefact
*\param indice indice de l'artefact dans le tableau dans la structure map
*\param prix prix de l'artefact
*\param indice_texture l'indice de la texture de l'artefact pour le lire dans le fichier
*\brief fonction qui initialise un artefact
*/
//fonction qui initialise un artefact
artefact_t * init_artefact(char* nom, int possession,char * descriptif,int indice,int prix,int indice_texture){
    artefact_t * artefact = malloc(sizeof(artefact_t));
    artefact->nom = malloc(strlen(nom)+1);
    strcpy(artefact->nom,nom);
    artefact->descriptif = malloc(strlen(descriptif)+1);
    strcpy(artefact->descriptif,descriptif);
    artefact->possession=possession;
    artefact->indice=indice;
    artefact->prix=prix;
    artefact->indice_texture=indice_texture;
    artefact->equipe=0;
    return artefact;
}
/**
*\fn void destruction_artefact(artefact_t * artefact)
*\param artefact structure d'artefact 
*\brief fonction qui detruit l'artefact
*/
void destruction_artefact(artefact_t * artefact){
    free(artefact->nom);
    free(artefact->descriptif);
    free(artefact);

}