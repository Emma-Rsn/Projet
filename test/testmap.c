#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "src/map.c" // Include your map.c file

// Test Suite setup and cleanup functions
int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

// Test case for creation_case()
void test_creation_case(void) {
    case_t my_case = creation_case();
    CU_ASSERT(my_case.etat == 1);
    CU_ASSERT(my_case.Rectangle.x == 0);
    CU_ASSERT(my_case.Rectangle.y == 0);
    CU_ASSERT(my_case.Rectangle.w == 64);
    CU_ASSERT(my_case.Rectangle.h == 64);
    CU_ASSERT(my_case.ntexture == 0);
}

// Test case for creation_grille()
void test_creation_grille(void) {
    int width = 10; // Example width
    int height = 10; // Example height
    int bord = 0; // Example border type
    grille_t my_grille = creation_grille(width, height, bord);

    // Check if all cells are initialized correctly
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            CU_ASSERT(my_grille.tabGrille[i][j].etat == 1 || my_grille.tabGrille[i][j].etat == 2);
        }
    }
}

// Main function: Sets up the CUnit test registry and adds all the tests
int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("map_test_suite", init_suite, clean_suite);

    CU_add_test(suite, "test of creation_case()", test_creation_case);
    CU_add_test(suite, "test of creation_grille()", test_creation_grille);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}