#include "test.h"

void test_direct_path(){
    service_station * root = NULL;
    add_station(&root, 8);
    add_vehicle(search_station(root, 8), 100);

    add_station(&root, 10);
    add_vehicle(search_station(root, 10), 3);

    add_station(&root, 13);
    add_vehicle(search_station(root, 13), 3);

    add_station(&root, 16);
    add_vehicle(search_station(root, 16), 3);

    add_station(&root, 20);
    add_vehicle(search_station(root, 20), 7);

    printf("\n10 -> 20:\n");
    if(! find_direct_path(search_station(root, 10), search_station(root, 20)) ) { printf("PATH NOT FOUND!\n");}

    printf("\n8 -> 20:\n");
    if (! find_direct_path(search_station(root, 8), search_station(root, 20)) ) { printf("PATH NOT FOUND!\n");}

    free_tree(root);
}

void test_inverse_path(){
    service_station * root = NULL;
    add_station(&root, 20);
    add_station(&root, 45);
    add_station(&root, 30);
    add_station(&root, 50);

    add_vehicle(search_station(root, 20), 5);
    add_vehicle(search_station(root, 20), 10);
    add_vehicle(search_station(root, 20), 15);
    add_vehicle(search_station(root, 20), 25);

    add_vehicle(search_station(root, 30), 40);

    add_vehicle(search_station(root, 45), 30);

    add_vehicle(search_station(root, 50), 20);
    add_vehicle(search_station(root, 50), 25);

    printf("\n50 -> 20:\n");
    if(! find_inverse_path(search_station(root, 50), search_station(root, 20)) ) { printf("PATH NOT FOUND!\n"); }

    free_tree(root);
}
