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
    //mode de transparence
    SDL_BlendMode blend = SDL_BLENDMODE_BLEND;
    SDL_SetRenderDrawBlendMode(renderer, blend);

    //IMG de fond
    //SDL_Texture* backgroundTexture = NULL;
    
    
    // Initialiser la map
    map_t map=creation_map((*wEcran),(*hEcran));
    int *etat_map=malloc(sizeof(int));
    (*etat_map)=0;
    int ouigrille = 0;
    int ouilumiere = 0;
    int ouifps = 0;
    Mix_Music* gMusic = NULL;

    remplir_map(&map);
    nb_texture_chargement(&map, "save/texture.txt");
    creation_tab_path(&map, "save/texture.txt");
    afficher_zone(map);
    //def spawn
    int q,s,xp,yp;
    if(!load_pos(&q,&s,&xp,&yp)){
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
        xp = 12,yp=5;
    }
    carte_t * cartec = &(map.tabMap[q][s]);
    cartec->etat_brouillard = 0;
    map.zoneChargee=cartec->nZone;
    chargement_Zone(&map,renderer,map.zoneChargee,gMusic);
    creer_map_layout(&map);

    //temporaire
    ennemi_t Slime1 = init_ennemi("Slime1",10,11,&map,100,100,0,2,20,0);

    Slime1.combattant[1] = init_combattant("Lute1",100,10,1,11,10,0,1,10,0);
    ennemi_t * PSlime1 = &Slime1;
    obj_t ObjSlime1 = init_obj(&map.tabMap[5][5].grille.tabGrille[4][5],10,2,PSlime1);
    map.tabMap[5][5].tabObj[0] = ObjSlime1;

    obj_t ObjCaillou = init_obj(&map.tabMap[5][5].grille.tabGrille[15][5],9,0);
    map.tabMap[5][5].tabObj[1] = ObjCaillou;

    ennemi_t Boss = init_ennemi("Alex",27,27,&map,100,100,0,2,17,3);
    Boss.combattant[1] = init_combattant("Lute",100,10,1,11,10,1,1,5,0);
    Boss.combattant[2] = init_combattant("Lute2",100,10,1,11,10,2,1,5,0);
    Boss.combattant[3] = init_combattant("Lute3",100,10,1,11,10,4,1,5,0);
    ennemi_t * PBoss = &Boss;
    obj_t ObjBoss = init_obj(&map.tabMap[5][5].grille.tabGrille[10][5],27,2,PBoss);
    map.tabMap[5][5].tabObj[2] = ObjBoss;

    map.tabMap[5][5].nbObj = 3;

    int tN = 0;

    //fin temporaire


    //variable FPS
    int cmpfps = 0;
    int dfps = FPS;
    Uint32 * t0 = malloc(sizeof(Uint32));
    Uint32 * t1 = malloc(sizeof(Uint32));
    int * nfps = malloc(sizeof(int));
    *t0 = -1;

    //creation personnage
	p_mv Alex;
	Alex = initp(cartec,&(cartec->grille.tabGrille[xp][yp]),&map);
    Alex.equipe[1]=init_combattant("Lou",100,60,0,1,14,1,0,10,0);
    Alex.equipe[2]=init_combattant("Finn",100,45,0,1,1,2,0,8,0);
    Alex.equipe[3]=init_combattant("Ada",100,45,0,1,1,3,3,14,0);
	p_mv * pAlex = &Alex;

    

    //creation d'un pnj
    pnj_t Alex2;
    Alex2 = init_pnj("Alex2","sprite/alexdial.png", "sprite/alexface2.png",&(map.tabMap[0][0].grille.tabGrille[14][9]),&map.tabMap[0][0]);
    pnj_t * pAlex2 = &Alex2;
    insertion(Alex2.dial, "Bonjour");
    insertion(Alex2.dial, "Test");

    //creation ennemi 


    ennemi_t Slime = init_ennemi("Slime",11,10,&map,100,100,0,2,17,0);
    Slime.combattant[1] = init_combattant("Lute",100,10,1,11,10,0,1,5,0);
    ennemi_t * PSlime = &Slime;
    obj_t ObjSlime = init_obj(&map.tabMap[3][3].grille.tabGrille[4][5],10,2,PSlime);
    map.tabMap[3][3].tabObj[1] = ObjSlime;
    map.tabMap[3][3].nbObj = 1;
    

    //variable indique l'etat du prog
    int i;//brouillard
    int j;//brouillard

    int * transi = malloc(sizeof(int));
    *transi = 0;

    SDL_Event event;
    //char * command = NULL;


    //menu d'ecran titre
    menu(wEcran,hEcran,event,renderer,run,etatoption,toucheDeplacement);

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
            }if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_1)){
                if(pAlex->NightP == 0){
                    pAlex->NightP = 100;
                    tN = 1;
                }else{
                    pAlex->NightP = 0;
                    tN = 1;
                }
            }
            if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_x)){                
                (*etat_map)=1;
                /*if(ind_map==1){
                    ind_map=2;
                }
                if(ind_map==2){
                    ind_map=3;
                }
                if(ind_map==3){
                    ind_map=0;
                }*/
            }
            pinput(pAlex,event,&cartec,&map,renderer,transi,gMusic,toucheDeplacement);
            pause(event,gMusic);

            //menu
            //console_command(event,command);
            menu_option(wEcran,hEcran,event,renderer,run,etatoption);
            //aller dans les options
            option(wEcran,hEcran,event,renderer,etatoption,toucheDeplacement);
            debut_dialogue(event,pAlex2,pAlex);
            debut_combat_carte(cartec,event,pAlex);
            if(pAlex->NightP == 100 && tN == 1){
                pAlex->Nightmare = 1;
                map.Nightmare = 1;
                tN = 0;
                newMusic(6,gMusic);
            }else if(tN == 1){
                pAlex->Nightmare = 0;
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
        aff_pnj(Alex2,renderer,cartec);

        //Affiche un personnage
        affp(pAlex,renderer,event);
        affTabObj(renderer,map,cartec);

        if(ouilumiere)lumiere(renderer,cartec,pAlex->c);

        affHud(renderer,hEcran,wEcran,map,*pAlex);

         //affiche les fps
        if(ouifps)aff_Fps(cmpfps,renderer);

        transition(renderer,transi,*wEcran,*hEcran);


        //afficher dialogue
        pnj_dialogue (event,pAlex2,renderer,hEcran,wEcran);

        //afficher map
        afficher_map(event,map,renderer,wEcran,hEcran,etat_map,cartec);
        
        //Commence une combat
        combat_carte(cartec,wEcran,hEcran,event,renderer,pAlex,&map);


        //Partie perdu
         menu_gameOver(wEcran,hEcran,event,renderer,run,pAlex,&map);



    
        // Mettre à jour le rendu
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/dfps);
    }

    // Libérer les ressources
    //combattant(pAlex);

    save_pos(cartec->xcarte,cartec->ycarte,pAlex->c->x,pAlex->c->y);

    free(etat_map);
    free(nfps);
    free(t0);
    free(t1);
    free(etat_menu);
    free(run);
    free(transi);
    free(etatoption);
    free(toucheDeplacement);

    Mix_FreeMusic( gMusic );

    

    //SDL_DestroyTexture(backgroundTexture);
    creation_tab_texture(&map,renderer,1,1);
    detruire_tab_path(&map);

    dest_pnj(pAlex2);
    desctruction_p_eq(pAlex);
    dest_ennemi(&Slime);
    dest_ennemi(&Slime1);
    dest_ennemi(&Boss);
    free(wEcran);
    free(hEcran);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
