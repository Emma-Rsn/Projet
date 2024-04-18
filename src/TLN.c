//
//TLN.c
//Created by Moreau Enzo Rasson Emma Pasquier Lina 
//

/**
*\file TLN.c
*\brief programme principale
*\author Moreau Enzo Rasson Emma Pasquier Lina 
*\date  janvier 2024
*\version 0.0
*
*/

#include "../libs/commun.h"

int main(){
    srand(time(NULL));

    //initialisation variable menu

    int * etat_menu=malloc(sizeof(int));
    int * run=malloc(sizeof(int));
    int * etatoption=malloc(sizeof(int));
    int * toucheDeplacement=malloc(sizeof(int));
    *toucheDeplacement=0;
    *run=1;
    *etatoption=0;

     
    //resolution de l'ecran
    save_settings();
    int * hEcran = malloc(sizeof(int));
    int * wEcran = malloc(sizeof(int));
    load_settings(wEcran,hEcran);

     // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }
    // Initialisation de TTF
    if (TTF_Init() < 0) {
        fprintf(stderr, "Erreur d'initialisation de TTF : %s\n", SDL_GetError());
        return -1;
    }
    // Création de la fenêtre
    SDL_Window *window = SDL_CreateWindow("The Last Nightmare", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, *wEcran, *hEcran, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL) {
        fprintf(stderr, "Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }
    // Création du rendu
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Erreur de création du rendu : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    SDL_Surface * logo = IMG_Load("logo.png");
    SDL_SetWindowIcon(window,logo);
    SDL_FreeSurface(logo);
    //mode de transparence
    SDL_BlendMode blend = SDL_BLENDMODE_BLEND;
    SDL_SetRenderDrawBlendMode(renderer, blend);

    //IMG de fond
    //SDL_Texture* backgroundTexture = NULL;
    
    
    // Initialiser la map
    map_t map=creation_map();
    int *etat_map=malloc(sizeof(int));
    (*etat_map)=0;
    int ouigrille = 0;
    int ouilumiere = 0;
    int ouifps = 0;
    Mix_Music* gMusic = NULL;

    remplir_map(&map);
    nb_texture_chargement(&map, "save/texture.txt");
    creation_tab_path(&map, "save/texture.txt");
    //afficher_zone(map);

    map.listeArtefact[0]=init_artefact("artefact1",0,"augmente la force d'attaque",0,10,185);
    map.listeArtefact[1]=init_artefact("artefact1",0,"augmente la vitesse",1,10,186);
    map.listeArtefact[2]=init_artefact("artefact1",1,"qui augmente les Pv max",2,10,187);
    map.listeArtefact[3]=init_artefact("artefact1",1,"ressuscite tous les personnages avec la moitier de leur pv",3,10,188);
    map.listeArtefact[4]=init_artefact("artefact1",0,"augmente le nombre de point au debut d'un combat",4,10,189);
    map.listeArtefact[5]=init_artefact("artefact1",1,"l'effet de cet artefact est inconnu ",5,10,190);
    map.listeArtefact[6]=init_artefact("artefact1",0,"diminue l'augmentation du cauchemar",6,10,191);
    map.listeArtefact[7]=init_artefact("artefact1",0,"reduit le temps de recharde de 1 tour",7,10,192);
    map.listeArtefact[8]=init_artefact("artefact1",0,"permet de recuperer plus d'argent",8,10,193);
    map.listeArtefact[9]=init_artefact("artefact1",0,"permet de recuperer un niveau",9,10,194);

    //def spawn
    int q,s,ii,last;
    int * pv = malloc(sizeof(int));
    int * tabparam[26];
    for(ii = 0;ii<26;ii++){
        tabparam[ii] = malloc(sizeof(int));
    }
    p_mv * Alex = initp();
    Alex->equipe[0]=pre_init_combattant();

    int xp,yp;
    last = load_pos(&q,&s,&xp,&yp,&map,pv,Alex,tabparam,toucheDeplacement);
    if(last != 1){
        for(q = 0;q<ROWS;q++){
            for(s = 0;s<COLUMNS;s++){
                if(map.tabMap[q][s].nZone == 1){
                    break;
                }
            }
            if(map.tabMap[q][s].nZone == 1){
                    break;
            }
        }
        xp = 12,yp=5,*tabparam[0] = 0,*tabparam[1] = 0,*tabparam[2] = 0,*tabparam[3] = 0,*pv=100;
        if(last != 2)*tabparam[4] = 0,*tabparam[5] = 1;
        for(ii = 6;ii<26 && last != 2;ii++){
            *tabparam[ii] = 0;
        }
    }
    map.Zone2 = *tabparam[0],map.Zone3 = *tabparam[1],map.Zone4 = *tabparam[2],map.Zone5 = *tabparam[3],map.argent = *tabparam[4],map.nvEquipe = *tabparam[5];
    for(ii = 6;ii < 16;ii++){
        map.listeArtefact[ii-6]->equipe = *tabparam[ii];
    }
    for(ii = 16;ii < 26;ii++){
        map.listeArtefact[ii-16]->possession = *tabparam[ii];
    }
    map.Nightmare=*Alex->Nightmare;
    carte_t * cartec =&map.tabMap[q][s];
    remplirp(Alex,&(cartec->grille.tabGrille[xp][yp]),0);
    *Alex->equipe[0]->pv=*pv;

    cartec->etat_brouillard = 0;
    map.zoneChargee = cartec->nZone;
    free(pv);
    for(ii = 0;ii<26;ii++){
        free(tabparam[ii]);
    }
    chargement_Zone(&map,renderer,map.zoneChargee,gMusic);
    creer_map_layout(&map);

    int *etat_dialogue=malloc(sizeof(int));
    *etat_dialogue=0;
    /*obj_t * dial;
    dial=init_obj(&map.tabMap[cartec->xcarte][cartec->ycarte].grille.tabGrille[2][2],10,3,8);
    map.tabMap[cartec->xcarte][cartec->ycarte].tabObj[0] = dial;
    map.tabMap[cartec->xcarte][cartec->ycarte].nbObj = 1;
    

    ennemi_t * Slime1 = init_ennemi("Slime1",100,10,1,11,15,0,1,10,0);
    Slime1->combattant[1] = init_combattant("Lute1",100,10,1,11,10,0,1,10,0);
    obj_t * ObjSlime1 = init_obj(&map.tabMap[cartec->xcarte][cartec->ycarte].grille.tabGrille[4][5],15,2,Slime1);
    map.tabMap[cartec->xcarte][cartec->ycarte].tabObj[0] = ObjSlime1;
    map.tabMap[cartec->xcarte][cartec->ycarte].nbObj = 1;

    ennemi_t * Slime2 = init_ennemi("Boss",1,10,1,11,10,2,1,10,3);
    Slime2->combattant[1] = init_combattant("Lute2",1,10,1,11,10,3,1,10,0);
    obj_t * ObjSlime2 = init_obj(&map.tabMap[2][3].grille.tabGrille[3][2],10,2,Slime2);
    map.tabMap[2][3].tabObj[1] = ObjSlime2;
    map.tabMap[2][3].nbObj = 1;*/



  

    load_obj(&map.tabMap[2][3],"layoutbeachObj.txt");




    //creation personnage
    Alex->equipe[1]=init_combattant("Lou",50,60,0,1,14,1,0,10,0);
    //Alex->equipe[2]=init_combattant("Finn",50,45,0,1,1,2,0,8,0);
    //Alex->equipe[2]=init_combattant("Ada",100,45,0,1,1,3,3,14,0);


    //variable FPS
    int cmpfps = 0;
    int dfps = FPS;

    Uint32 * t0 = malloc(sizeof(Uint32));
    Uint32 * t1 = malloc(sizeof(Uint32));
    int * nfps = malloc(sizeof(int));
    *t0 = -1;

    
    //variable indique l'etat du prog
    int i;//brouillard debug
    int j;//brouillard debug

    int * transi = malloc(sizeof(int));
    *transi = 0;
    int tN = 1; //variable musique cauchemar

    SDL_Event event;
    //char * command = NULL;


    //menu d'ecran titre
    menu(wEcran,hEcran,event,renderer,run,etatoption,toucheDeplacement,&map);
    //boucle du programme
    while (*run) {
        //zone d'evenement
        while (SDL_PollEvent(&event) != 0) {
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_h)){
                if(ouigrille == 0){
                    ouigrille = 1;
                }else{
                    ouigrille = 0;
                }
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_l)){
                if(ouilumiere == 0){
                    ouilumiere = 1;
                }else{
                    ouilumiere = 0;
                    *Alex->equipe[0]->pv = 1;
                    map.argent++;
                }
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_3)){
                if(ouifps == 0){
                    ouifps = 1;
                }else{
                    ouifps = 0;
                }
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_m)){
                for(i = 0;i < ROWS;i++){
                    for(j = 0; j < COLUMNS; j++){
                        map.tabMap[i][j].etat_brouillard = 0;
                    }
                }
                map.Zone2 = 2;
                map.Zone3 = 2;
                map.Zone4 = 2;
                map.Zone5 = 2;
            }if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_1)){
                if(*(Alex->NightP) == 0){
                    *(Alex->NightP) = 100;
                    tN = 1;
                }else{
                    *(Alex->NightP) = 0;
                    tN = 1;
                }
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_x)){                
                (*etat_map)=1;
            }
            pinput(Alex,event,&cartec,&map,renderer,transi,gMusic,toucheDeplacement);
            pause(event,gMusic);

            //menu
            menu_option(wEcran,hEcran,event,renderer,run,etatoption,&map);
            //aller dans les options
            option(wEcran,hEcran,event,renderer,etatoption,toucheDeplacement,&map);
            debut_dialogue_carte(cartec,event,Alex,etat_dialogue);
            debut_combat_carte(cartec,event,Alex);
            if(*Alex->NightP == 100 && tN == 1){
                *Alex->Nightmare = 1;
                map.Nightmare = 1;
                tN = 0;
                newMusic(6,gMusic);
            }else if(tN == 1){
                *Alex->Nightmare = 0;
                map.Nightmare = 0;
                tN = 0;
                newMusic(map.zoneChargee,gMusic);
            }
            
        }
        
        //zone d'affichage
        //ajustement de dfps
        ajDFPS(&dfps,&cmpfps, nfps, t0, t1);
        //efface le rendu
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 245, 255);

        //affiche la grille
        betaAfficherMap(renderer,&map,cartec);
        if(ouigrille)afficher_grille(cartec->grille,renderer);

        //Affichage pnj
        //aff_pnj(Alex2,renderer,cartec);

        //Affiche un personnage
        affp(Alex,renderer,event);
        affTabObj(renderer,map,cartec);

        if(ouilumiere)lumiere(renderer,cartec,Alex->c);

        affHud(renderer,hEcran,wEcran,map,*Alex);

         //affiche les fps
        if(ouifps)aff_Fps(cmpfps,renderer);

        transition(renderer,transi,*wEcran,*hEcran);


        //afficher dialogue
        //pnj_dialogue (event,pAlex2,renderer,hEcran,wEcran);

        //afficher map
        afficher_map(event,map,renderer,wEcran,hEcran,etat_map,cartec);
        
        //Commence un combat
        combat_carte(cartec,wEcran,hEcran,event,renderer,Alex,&map);
        
        dialogue_carte(cartec,wEcran,hEcran,event,renderer,&map,etat_dialogue);



        //Partie perdu
         menu_gameOver(wEcran,hEcran,event,renderer,run,Alex,&map);
         



    
        // Mettre à jour le rendu
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/dfps);
    }

    // Libérer les ressources
    //combattant(pAlex);

    save_pos(cartec->xcarte,cartec->ycarte,*Alex,map,*toucheDeplacement);
    

    free(etat_map);
    free(nfps);
    free(t0);
    free(t1);
    free(etat_menu);
    free(run);
    free(transi);
    free(etatoption);
    free(toucheDeplacement);
    free(etat_dialogue);

    Mix_FreeMusic(gMusic);
    Mix_CloseAudio();

    
    dest_all_obj(&map);
    //SDL_DestroyTexture(backgroundTexture);
    creation_tab_texture(&map,renderer,1,1);
    detruire_tab_path(&map);

    desctruction_p_eq(Alex);
    //desctruction_combattant(Alex.equipe[0]);

    free(wEcran);
    free(hEcran);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    //nouvelle partie
    int res = 0;
    FILE * fichier = fopen("save/save.txt", "r+");
    fscanf(fichier, "%d", &res);
    fclose(fichier);
    if(res == 2){system("./bin/TLN");}
    if(res == 3){effacer_sauvg();system("./bin/TLN");}
    return 0;
}
