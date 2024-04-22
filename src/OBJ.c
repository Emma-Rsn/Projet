/**
*\file OBJ.c
*\brief programme qui gere les objets du jeu
*\author Moreau Enzo
*\date  Avril 2024
*\version 1.0
*
*/

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
            n = 0;
            newObj->cas->etat = 0;
            break;
        case 1 : //cas d'un objet de décors sans collision
            n = 0;
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
        case 5 : //cas d'un loot apres boss
            n = 1;
            newObj->cas->etat = 0;
            break;
        case 6 : //cas d'une porte nécessitant la clé
            n = 0;
            newObj->cas->etat = 0;
        case 7 : //cas de la zone de plongée
            n = 0;
            newObj->cas->etat = 0;
        case 8 : //cas d'une porte nécessitant la clé
            n = 0;
            newObj->cas->etat = 0;
        case 9 : //cas de la zone de plongée
            n = 0;
            newObj->cas->etat = 0;
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

void debut_loot_carte(carte_t **cartec,SDL_Event event,p_mv * pp,map_t * map,int * etat_dialogue){
    int i;
    for(i=0;i<(*cartec)->nbObj;i++){
        if((*cartec)->tabObj[i]->typeObj==5){
            debut_loot(event,pp,(*cartec)->tabObj[i]->cas,map,(*cartec)->tabObj[i],etat_dialogue,(*cartec)->tabObj[i]->tabObj[0]);
        }else if((*cartec)->tabObj[i]->typeObj==6){
            if(boolcol((*cartec)->tabObj[i]->cas,pp)  && event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_e && map->cle == 1){
                (*cartec) = &map->tabMap[(*cartec)->xcarte][(*cartec)->ycarte+1];
                (*cartec)->etat_brouillard = 0;
                pp->c = &((*cartec)->grille.tabGrille[0][5]);
                 pp->r = pp->c->Rectangle;
            }
        }else if((*cartec)->tabObj[i]->typeObj==7){
            if(boolcol((*cartec)->tabObj[i]->cas,pp)  && event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_e && map->plongee == 1){
                (*cartec) = &map->tabMap[(*cartec)->xcarte+1][(*cartec)->ycarte];
                (*cartec)->etat_brouillard = 0;
                pp->c = &((*cartec)->grille.tabGrille[15][0]);
                pp->r = pp->c->Rectangle;
            }
        }else if((*cartec)->tabObj[i]->typeObj==8){
            if(boolcol((*cartec)->tabObj[i]->cas,pp)  && event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_e){
                (*cartec) = &map->tabMap[(*cartec)->xcarte][(*cartec)->ycarte-1];
                (*cartec)->etat_brouillard = 0;
                pp->c = &((*cartec)->grille.tabGrille[15][0]);
                pp->r = pp->c->Rectangle;
            }
        }else if((*cartec)->tabObj[i]->typeObj==9){
            if(boolcol((*cartec)->tabObj[i]->cas,pp)  && event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_e){
                (*cartec) = &map->tabMap[(*cartec)->xcarte-1][(*cartec)->ycarte];
                (*cartec)->etat_brouillard = 0;
                pp->c = &((*cartec)->grille.tabGrille[15][0]);
                pp->r = pp->c->Rectangle;
            }
        }
    }
}



void debut_loot(SDL_Event event,p_mv * pp,case_t * c,map_t * map,obj_t * obj,int * etat_dialogue,int num_dialogue){
    if(boolcol(c,pp)  && event.type == SDL_KEYDOWN && event.key.keysym.sym==SDLK_e){
        switch(num_dialogue){
            case 0 : map->plongee = 1;
            break;
            case 1 : map->cle = 1;
            break;
            case 2 : map->talisman = 1;
            break;
        }
        *etat_dialogue=1;
    } 
}


int load_obj(carte_t *c, char *namefile){
    int x,y,indText,type;
    FILE * file;
    int i;

    char nom[20];
    int pv,vitesse,camp,indice_portait,indice_sprite,typeE,temps_recharge_max,puissance,forme;
    int nbCombattant;
    int num_dialogue;

    file=fopen(namefile,"r");

    if(file){
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
                    ennemi_t * newEnnemi=init_ennemi(nom,pv,vitesse,camp,indice_portait,indice_sprite,typeE,temps_recharge_max,puissance,forme);
                    for(i=1;i<=nbCombattant;i++){
                        fscanf(file,"%s %d %d %d %d %d %d %d %d %d",nom,&pv,&vitesse,&camp,&indice_portait,&indice_sprite,&typeE,&temps_recharge_max,&puissance,&forme);
                        newEnnemi->combattant[i]=init_combattant(nom,pv,vitesse,camp,indice_portait,indice_sprite,typeE,temps_recharge_max,puissance,forme,pv);
                    }
                    c->tabObj[c->nbObj]=init_obj(&c->grille.tabGrille[x][y],indText,type,newEnnemi);
                    c->nbObj++;
                    break;
                case 3 :
                    fscanf(file,"%d",&num_dialogue);
                    c->tabObj[c->nbObj]=init_obj(&c->grille.tabGrille[x][y],indText,type,num_dialogue);
                    c->nbObj++; 
                    break;
                case 4 :
                    fscanf(file,"%d",&num_dialogue);
                    c->tabObj[c->nbObj]=init_obj(&c->grille.tabGrille[x][y],indText,type,num_dialogue);
                    c->nbObj++; 
                    break;
                case 5 :
                    fscanf(file,"%d",&num_dialogue);
                    c->tabObj[c->nbObj]=init_obj(&c->grille.tabGrille[x][y],indText,type,num_dialogue);
                    c->nbObj++; 
                    break;
                case 6 :
                    c->tabObj[c->nbObj]=init_obj(&c->grille.tabGrille[x][y],indText,type);
                    c->nbObj++; 
                    break;
                case 7 :
                    c->tabObj[c->nbObj]=init_obj(&c->grille.tabGrille[x][y],indText,type);
                    c->nbObj++; 
                    break;
                case 8 :
                    c->tabObj[c->nbObj]=init_obj(&c->grille.tabGrille[x][y],indText,type);
                    c->nbObj++; 
                    break;
                case 9 :
                    c->tabObj[c->nbObj]=init_obj(&c->grille.tabGrille[x][y],indText,type);
                    c->nbObj++; 
                    break;
            }
            fscanf(file,"\n");
        }
    }
    else{
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
    for(i = 0; i < carte->nbObj;i++){
        if(map.Nightmare == 1 && carte->tabObj[i]->typeObj < 3)n=map.nbN;
        else n=0;
        SDL_RenderCopy(renderer, map.tabTexture[(carte->tabObj[i]->indTexture)+n], NULL, &(carte->tabObj[i]->cas->Rectangle));
    }
}


/**
*
*\fn artefact_t * init_artefact(char* nom, int possession,char * descriptif,int indice,int prix,int indice_texture)
*\param nom nom de l'ennemi
*\param pv nombre de pv de l'ennemi
*\param vitesse vitesse de l'ennemi
*\param camp camp de l'ennemi (1)
*\param indice_portrait indice du portrait de l'ennemi
*\param indice_sprite l'indice du sprite de l'ennemi
*\param type type de l'ennemi
*\param temps_recharge_max temps de recharge de l'ennemi
*\param puissance puissance de l'ennemi
*\param forme forme de l'ennemi
*\brief fonction qui initialise un ennemi
*/
//fonction qui initialise un ennemi
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
    if(en->combattant[0] != NULL)desctruction_combattant(en->combattant[0]);
    en->combattant[0]=init_combattant(en->nom,en->pv,en->vitesse,1,indice_portrait,indice_sprite,type,en->temps_recharge_max,puissance,forme,pv);
    en->indice_portrait=indice_portrait;
    en->indice_sprite=indice_sprite;
    en->forme=forme;
    return en;
}

int newLeader(p_mv pp){
    if(!pp.equipe[1])return pp.equipe[0]->type;
    srand( time( NULL ) );
    int i;
    do{
        i = rand()%3+1;
    }while(!pp.equipe[i]);
    return pp.equipe[i]->type;
}

void Boss(obj_t * boss,p_mv * Leader){
    if(boss->typeObj == 2){
        if(((ennemi_t *)boss->tabObj[0])->forme == 3){
            srand( time( NULL ) );
            int type = ((ennemi_t *)boss->tabObj[0])->type;
            int i,y,j,combat = ((ennemi_t *)boss->tabObj[0])->combat;
            for(y = 0;Leader->equipe[y] && y < 4;y++);
            if(y==4)return;
            combattant_t * tab[y];
            if(y>0){
                for(j=1;j<y;j++){
                    tab[j-1] = ((ennemi_t *)boss->tabObj[0])->combattant[j];
                }
            }
            for(i = 0;Leader->equipe[i] && Leader->equipe[i]->type != type;i++);
            if(!Leader->equipe[i])return;
            if(Leader->equipe[i]->type == type){
                do{
                    type = rand()%4;
                }while(BoolTypein(type,Leader));
            }
            dest_ennemi((boss->tabObj[0]));
            switch (type)
            {
            case 0://Alex
            boss->indTexture = 0;
            boss->tabObj[0]=init_ennemi("Alex",190,60,0,136,135,0,2,27,0);
                break;

            case 1://Lou
            boss->indTexture = 0;
            boss->tabObj[0]=init_ennemi("Lou",180,75,0,138,137,1,3,23,0);
                break;

            case 2://Finn
            boss->indTexture = 0;
            boss->tabObj[0]=init_ennemi("Finn",230,70,0,140,139,2,3,15,0);
                break;

            case 3://Ada
            boss->indTexture = 0;
            boss->tabObj[0]=init_ennemi("Ada",135,65,0,142,141,3,2,36,0);
                break;
            
            default:
                break;
            }
            ((ennemi_t *)boss->tabObj[0])->combat = combat;
            if(y>0){
                for(j=1;j<y;j++){
                    ((ennemi_t *)boss->tabObj[0])->combattant[j] = tab[j-1];
                }
            }
        }
    }
}



int BoolTypein(int type,p_mv * Leader){
    int nballie,i;
    for(nballie=0;Leader->equipe[nballie] && nballie < 4;nballie++);
    for(i =0;i<nballie;i++){
        if(Leader->equipe[i]->type == type){
            return 1;
        }
    }
    return 0;
}

void dest_obj(carte_t * c,int ind){

    if(c->nbObj > 0){
        switch(c->tabObj[ind]->typeObj){
            case 2 : dest_ennemi(((ennemi_t *)(c->tabObj[ind]->tabObj[0])));
            c->tabObj[ind]->cas->etat=1;
            break;


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

void dest_all_obj(map_t *m){
    int i,j;
    for(i = 0;i<ROWS;i++){
        for(j = 0;j < COLUMNS;j++){
            while(m->tabMap[i][j].nbObj){
                dest_obj(&m->tabMap[i][j],0);
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