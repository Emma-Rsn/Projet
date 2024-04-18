#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "src/musique.c"
#include "src/combat.c"
#include "src/map.c"
#include "src/OBJ.c"


int init_suite(void) {return 0;}
int clean_suite(void){return 0;}


// Tests pour la fonction creation_case()
void test_creation_case(void) {
    case_t c = creation_case();
    CU_ASSERT(c.etat == 1);
    CU_ASSERT(c.Rectangle.x == 0);
    CU_ASSERT(c.Rectangle.y == 0);
    CU_ASSERT(c.Rectangle.w == 64);
    CU_ASSERT(c.Rectangle.h == 64);
    CU_ASSERT(c.ntexture == 0);
}

// Tests pour la fonction creation_grille()
void test_creation_grille(void) {
    int width=30;
    int height=16;
    int bord = 0;
    grille_t grille = creation_grille(bord);

    // Vérifie si toutes les cases sont bien initialisées
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            CU_ASSERT(grille.tabGrille[i][j].etat == 1 || grille.tabGrille[i][j].etat == 2);
        }
    }
}

// Tests pour la fonction creation_carte()
void test_creation_carte(void) {
    int x=1, y=2;
    carte_t carte = creation_carte(x,y);

    // Vérifie si la carte est bien initialisée
    CU_ASSERT(carte.nZone == 0);
    CU_ASSERT(carte.xcarte == x);
    CU_ASSERT(carte.ycarte == y);
    CU_ASSERT(carte.etat_brouillard == 1);
    CU_ASSERT(carte.nbObj == 0);
    CU_ASSERT(carte.nrlayout == 0);
}

// Tests pour la fonction creation_map()
void test_creation_map(void) {
    int size=6;
    map_t map = creation_map();

    CU_ASSERT(map.tabTexture == NULL);
    CU_ASSERT(map.Nightmare == 0);
    CU_ASSERT(map.nvEquipe == 2);
    CU_ASSERT(map.bonusEquipeN == 3);
    CU_ASSERT(map.bonusZoneN == 1);
    CU_ASSERT(map.argent == 0);
    CU_ASSERT(map.Zone2 == 0);
    CU_ASSERT(map.Zone3 == 0);
    CU_ASSERT(map.Zone4 == 0);
    CU_ASSERT(map.Zone5 == 0);
    CU_ASSERT(map.nb_emplacement == 1);
    CU_ASSERT(map.prix_emplacement == 20);

    // Vérifie si toutes les cartes sont bien initialisées
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            CU_ASSERT(map.tabMap[i][j].xcarte == i || map.tabMap[i][j].ycarte == j);
        }
    }
}

// Tests pour la fonction creer_map()
void test_creer_map(void) {
    int size=6;
    map_t map = creation_map();
    creer_map(&map);

    // Vérifie si les zones de la carte sont bien initialisés
    for (int i = 0; i < size; i++){
        for(int j=0; j < size; j++){
            CU_ASSERT(map.tabMap[i][j].nZone != 0);
        }
    }
}

// Tests pour la fonction creer_map_layout()
void test_creer_map_layout(void) {
    int size=6;
    map_t map = creation_map();
    creer_map(&map);
    creer_map_layout(&map);

    // Vérifie si la carte est bien initialisée
    for (int i = 0; i < size; i++){
        for(int j=0; j < size; j++){
            CU_ASSERT(map.tabMap[i][j].nrlayout != 0);
        }
    }
}

// Tests pour la fonction remplir_combattant()
void test_remplir_combattant(void) {
    combattant_t *comb = pre_init_combattant();
    char *nom="alex";
    remplir_combattant(comb,nom,100,10,1,15,14,1,5,20,0);

    //verifie si le combattant est bien initialise
    CU_ASSERT(strcmp(nom,comb->nom)==0);
    CU_ASSERT(*comb->pv == 100);
    CU_ASSERT(comb->vitesse == 10);
    CU_ASSERT(comb->camp == 1);
    CU_ASSERT(comb->indice_portrait == 15);
    CU_ASSERT(comb->indice_sprite == 14);
    CU_ASSERT(comb->type == 1);
    CU_ASSERT(comb->temps_recharge_max == 5);
    CU_ASSERT(comb->puissance == 20);
    CU_ASSERT(comb->forme == 0);
}

// Tests pour la fonction init_combattant()
void test_init_combattant(void) {
    combattant_t *comb;
    char *nom="alex";
    comb=init_combattant(nom,100,10,1,15,14,1,5,20,0);

    //verifie si le combattant est bien initialise
    CU_ASSERT(strcmp(nom,comb->nom)==0);
    CU_ASSERT(*comb->pv == 100);
    CU_ASSERT(comb->vitesse == 10);
    CU_ASSERT(comb->camp == 1);
    CU_ASSERT(comb->indice_portrait == 15);
    CU_ASSERT(comb->indice_sprite == 14);
    CU_ASSERT(comb->type == 1);
    CU_ASSERT(comb->temps_recharge_max == 5);
    CU_ASSERT(comb->puissance == 20);
    CU_ASSERT(comb->forme == 0);
}

// Tests pour la fonction init_combattant()
void test_attaque_ennemi(void) {
    int test;
    combattant_t * comb=init_combattant("alex",100,10,1,15,14,1,5,20,0);
    combattant_t * en=init_combattant("alex",100,10,1,15,14,1,5,20,0);
    combat_t * combat=init_combat();
    combat->combattant[0]=comb;
    combat->combattant[1]=en;
    combat->allie[0]=comb;
    combat->ennemi[0]=en;
    test=attaque_ennemi(1,combat);
    //verifie si l'ennemi attaque bien
    CU_ASSERT(test==0);

}

// Tests pour la fonction compare_vitesse()
void test_compare_vitesse(void) {
    int test;
    combattant_t * comb=init_combattant("alex",100,10,1,15,14,1,5,20,0);
    combattant_t * en=init_combattant("alex",100,15,1,15,14,1,5,20,0);
    test=compare_vitesse(comb,en);
    //verifie si l'ennemi est plus rapide que le combattant
    CU_ASSERT(test==1);
}

// Tests pour la fonction init_combat()
void test_init_combat(void) {
    combat_t * combat;

    combat=init_combat();
    //verifie si la structure combat est bien initialise
    CU_ASSERT_FALSE(combat->nb_allie);
    CU_ASSERT_FALSE(combat->nb_ennemi);
    CU_ASSERT_FALSE(combat->mult);
    CU_ASSERT_FALSE(combat->nb_point);
    CU_ASSERT_FALSE(combat->indice_ennemi);
    CU_ASSERT_FALSE(combat->indice_combattant);
    CU_ASSERT_FALSE(combat->num_tour);
}

// Tests pour la fonction copier_combattant()
void test_copier_combattant(void) {
    combattant_t * comb=init_combattant("alex",100,10,0,12,13,0,1,15,1);
    combattant_t * en=init_combattant("test",100,15,1,15,14,1,5,20,0);
    copier_combattant(comb,en);
    //verifie si l'ennemi est plus rapide que le combattant
    CU_ASSERT_STRING_EQUAL(comb->nom,en->nom);
    CU_ASSERT(*comb->pv==*en->pv);
    CU_ASSERT(comb->vitesse==en->vitesse);
    CU_ASSERT(comb->camp==en->camp);
    CU_ASSERT(comb->indice_portrait==en->indice_portrait);
    CU_ASSERT(comb->indice_sprite==en->indice_sprite);
    CU_ASSERT(comb->type==en->type);
    CU_ASSERT(comb->temps_recharge_max==en->temps_recharge_max);
    CU_ASSERT(comb->puissance==en->puissance);
    CU_ASSERT(comb->forme==en->forme);
}



int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("map_test_suite", init_suite, clean_suite);

     printf("\n TEST MAP : \n");
    CU_add_test(suite, "test creation_case()", test_creation_case);
    CU_add_test(suite, "test creation_grille()", test_creation_grille);
    CU_add_test(suite, "test creation_carte()", test_creation_carte);
    CU_add_test(suite, "test creation_map()", test_creation_map);
    CU_add_test(suite, "test creer_map()", test_creer_map);
    CU_add_test(suite, "test creer_map_layout()", test_creer_map_layout);


    printf("\n TEST COMBAT : \n");
    CU_add_test(suite, "test remplir_combattant()", test_remplir_combattant);
    CU_add_test(suite, "test test_init_combattant()", test_init_combattant);
    CU_add_test(suite, "test test_attaque_ennemi()", test_attaque_ennemi);
    CU_add_test(suite, "test test_compare_vitesse()", test_compare_vitesse);
    CU_add_test(suite, "test test_init_combat()", test_init_combat);
    CU_add_test(suite, "test test_copier_combattant()", test_copier_combattant);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}