#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "src/map.c" 
#include "src/musique.c"

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

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

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("map_test_suite", init_suite, clean_suite);

    CU_add_test(suite, "test creation_case()", test_creation_case);
    CU_add_test(suite, "test creation_grille()", test_creation_grille);
    CU_add_test(suite, "test creation_carte()", test_creation_carte);
    CU_add_test(suite, "test creation_map()", test_creation_map);
    CU_add_test(suite, "test creer_map()", test_creer_map);
    CU_add_test(suite, "test creer_map_layout()", test_creer_map_layout);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}