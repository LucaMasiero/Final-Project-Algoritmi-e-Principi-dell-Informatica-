#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

#define BLACK 'B'
#define RED 'R'

typedef struct vehicle_s {
    uint16_t quantity;           // number of vehicles with this autonomy
    uint32_t autonomy;           // autonomy of the vehicle(s)
    struct vehicle_s * next;     // pointer to next vehicle of the list
} vehicle;

typedef struct station_data_s {
    uint32_t dist;               // Distance from the beginning of the highway
    uint32_t max_autonomy;       // maximum autonomy between the entire fleet of vehicles
    uint32_t shortest_path;   // The shortest path found until this moment (Dijkstra)
    vehicle *fleet;              // RB-Tree of vehicles
    struct station_data_s *prev;   // Previous station in the shortest path (Dijkstra)
}station_data;

typedef struct station_node_s{
    uint8_t color;
    struct station_node_s * parent;
    struct station_node_s * left;
    station_data station;
    struct station_node_s * right;
} service_station;

/** CONDITIONAL FUNCTIONS **/

bool is_left_child(service_station* node){
    service_station* parentNode = node->parent;
    return parentNode != NULL && parentNode->left == node;
}

/** RELATIONS **/
service_station* grandparent_of(service_station* const node){
    service_station* parentNode = node->parent;
    return (parentNode != NULL) ? parentNode->parent : NULL;
}

service_station * tree_maximum(service_station * x){
    while(x->right != NULL){
        x = x->right;
    }
    return x;
}

service_station * tree_minimum(service_station * x){
    while(x->left != NULL){
        x = x->left;
    }
    return x;
}

service_station * predecessor(service_station * x){
    if(x->left != NULL){
        return tree_maximum(x->left);
    }

    service_station * y = x->parent;
    while(y != NULL && x == y->left){
        x = y;
        y = y->parent;
    }
    return  y;
}

service_station * successor(service_station * x){
    if(x->right != NULL){
        return tree_minimum(x->right);
    }

    service_station * y = x->parent;
    while(y != NULL && x == y->right){
        x = y;
        y = y->parent;
    }
    return y;
}

/** ROTATIONS **/
void leftRotate(service_station ** root, service_station * x){
    service_station* y = x->right;

    // Set right of x to left of y
    x->right = y->left;
    if(y->left) { y->left->parent = x; }

    // Set the y parent to x's parent
    y->parent = x->parent;
    if(y->parent == NULL){
        *root = y;
    }else if(is_left_child(x)){
        x->parent->left = y;
    }else{
        x->parent->right = y;
    }

    // Set the left of y to x (old root of the subtree)
    y->left = x;
    // Set parent of x to y
    x->parent = y;
}

void rightRotate(service_station ** root, service_station* x){
    service_station* y = x->left;

    // Set left of x to right of y
    x->left = y->right;
    if(y->right) { y->right->parent = x; }

    // Set the y parent to x's parent
    y->parent = x->parent;
    if(y->parent == NULL){
        *root = y;
    }else if(is_left_child(x)){
        x->parent->left = y;
    }else{
        x->parent->right = y;
    }

    // Set the right of y to x (old root of the subtree)
    y->right = x;
    // Set parent of x to y
    x->parent = y;
}

/** MAIN OPERATIONS **/
service_station * new_station(uint32_t d){
    service_station * x = malloc(sizeof(service_station));

    x->station.dist = d;
    x->station.fleet = NULL;
    x->station.max_autonomy = 0;
    x->station.shortest_path = INT_MAX;
    x->station.prev = NULL;

    x->right = NULL;
    x->left = NULL;
    x->parent = NULL;
    x->color = RED; // we do not want to change the tree balance

    return x;
}

service_station * search_station(service_station * root, uint32_t dist){
    while(root != NULL){
        if(dist < root->station.dist){
            root = root->left;
        }else if(dist > root->station.dist){
            root = root->right;
        }else{
            // We found the station
            return root;
        }
    }
    return NULL;
}

void fixTreeAfterInsert(service_station ** root, service_station * s){
    while (s != *root && s->parent->color == 1) {
        if (is_left_child(s->parent)) {
            service_station *grandParent = s->parent->parent,
                    *uncle = grandParent->right;

            if (uncle != NULL && uncle->color == 1) {
                s->parent->color = 0;
                uncle->color = 0;
                grandParent->color = 1;
                s = grandParent;
            } else {
                if (s == s->parent->right) {
                    s = s->parent;
                    leftRotate(root, s);
                }

                s->parent->color = 0;
                grandParent->color = 1;
                rightRotate(root, grandParent);
            }
        } else {
            service_station *grandParent = grandparent_of(s),
                    *uncle = grandParent->left;

            if (uncle != NULL && uncle->color == 1) {
                s->parent->color = 0;
                uncle->color = 0;
                grandParent->color = 1;
                s = grandParent;
            } else {
                if (s == s->parent->left) {
                    s = s->parent;
                    rightRotate(root, s);
                }

                s->parent->color = 0;
                grandParent->color = 1;
                leftRotate(root, grandParent);
            }
        }
    }

    (*root)->color = 0;
}

void fixTreeAfterDelete(service_station ** root, service_station * s){
    if(!s) { return; }

    while (s != *root && s->color == BLACK) {
        if (s == s->parent->left) {
            service_station * w = s->parent->right;

            if (w->color == RED) {
                w->color = BLACK;
                s->parent->color = RED;
                leftRotate(root, s->parent);
                w = s->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                s = s->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = s->parent->right;
                }
                w->color = s->parent->color;
                s->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(root, s->parent);
                s = *root;       // so that we exit the while-loop
            }
        } else {
            service_station * w = s->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                s->parent->color = RED;
                rightRotate(root, s->parent);
                w = s->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                s = s->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = s->parent->left;
                }

                w->color = s->parent->color;
                s->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, s->parent);
                s = *root;       // so that we exit the while-loop
            }
        }
        s->color = BLACK;
    }
}

service_station * add_station(service_station ** root, uint32_t dist){
    // Create and initialize new node
    service_station * s = new_station(dist);

    // Find the position
    service_station * x = *root;
    service_station * y = NULL;
    while(x != NULL){
        y = x;
        if(s->station.dist > x->station.dist){
            x = x->right;
        }else if(s->station.dist < x->station.dist){
            x = x->left;
        }else{
            // There is already a service_station at the specified distance
            return NULL;
        }
    }

    // Insert new node
    if(y == NULL){
        // It's the first node we insert
        *root = s;
    }else if(s->station.dist > y->station.dist){
        y->right = s;
    }else{
        y->left =s;
    }
    s->parent = y;
    fixTreeAfterInsert(root, s);
    return s;
}

bool demolish_station(service_station ** root, service_station * z){
    if(z == NULL){ return false; }

    service_station * y = NULL,
            * x = NULL;
    // y is the node physically deleted
    if(z->left == NULL || z->right == NULL){
        y = z;
    }else{
        y = successor(z);
    }
    // x is the child of y
    if(y->left != NULL){
        x = y->left;
    }else{
        x = y->right;
    }
    if(x != NULL){ x->parent = y->parent;}
    if(y->parent == NULL){
        *root = x;
    }else if(y == y->parent->left){
        y->parent->left = x;
    }else{
        y->parent->right = x;
    }

    if(y != z){
        // copy y's data in z
        z->station.dist = y->station.dist;
        z->station.fleet = y->station.fleet;
        z->station.max_autonomy = y->station.max_autonomy;
        z->station.shortest_path = y->station.shortest_path;
        z->station.prev = y->station.prev;
    }
    // if black balance has changed
    if(y->color == BLACK){
        fixTreeAfterDelete(root, x);
    }

    free(y);

    return true;
}

void free_tree(service_station * root){
    if(root == NULL){ return; }
    free_tree(root->left);
    free_tree(root->right);
    vehicle * v = root->station.fleet, * tmp;
    while(v){
        tmp = v->next;
        free(v);
        v = tmp;
    }
    free(root);
}

vehicle * new_vehicle(uint32_t a){
    vehicle * x = malloc(sizeof(vehicle));
    x->next = NULL;
    x->autonomy = a;
    x->quantity = 1;

    return x;
}

// Before calling this function remember to check if the station exists
bool add_vehicle(service_station * station, uint32_t a){
    if(station == NULL) { return false; }

    /* Add new vehicle to the fleet
        1. There are other vehicles with the same autonomy
        2. It's the first vehicle with this autonomy
     */
    vehicle * x = station->station.fleet,
            * y = NULL;

    while(x && x->autonomy > a){
        y = x;
        x = x->next;
    }

    if(x && x->autonomy == a){
        // Case 1
        x->quantity ++;
    }else{
        // Case 2
        vehicle * v = new_vehicle(a);
        v->next = x;
        if(y){
            y->next = v;
        }else{
            station->station.fleet = v;
            // Update max autonomy
            station->station.max_autonomy = a;
        }
    }
    return true;
}

bool demolish_vehicle(service_station * station, uint32_t a){
    if(station == NULL) { return false; }

    // Look for the vehicle
    vehicle * x = station->station.fleet,
            * y = NULL;

    while(x && x->autonomy > a){
        y = x;
        x = x->next;
    }

    if(!x || x->autonomy < a){
        return false;
    }

    // x is the node with the autonomy we want to delete
    x->quantity --;
    if(x->quantity == 0){
        // Delete node
        if(!y){
            // ... if it's the head
            station->station.fleet = x->next;

            // update max autonomy of the station
            x->next ? (station->station.max_autonomy = x->next->autonomy)
                    : (station->station.max_autonomy = 0);
        }else{
            y->next = x->next;
        }

        // free node
        free(x);
    }
    return true;
}

void print_path(station_data * s){
    if(s == NULL) { return; }
    print_path(s->prev);
    printf("%u ", s->dist);
}

bool find_direct_path(service_station * start, service_station * finish){
    bool found = false;
    service_station * x, * t = NULL;

    start->station.shortest_path = 0;
    x = start;
    while(!found && x->station.shortest_path < INT_MAX){

        t = x;
        while(t && x->station.max_autonomy >= t->station.dist - x->station.dist){
            if(t->station.shortest_path > x->station.shortest_path + 1){
                // we found a BETTER PATH for t
                t->station.shortest_path = x->station.shortest_path + 1;
                t->station.prev = &(x->station);
            }

            if(t == finish){
                // PATH DISCOVERED
                print_path(t->station.prev);
                printf("%u\n", t->station.dist);    // print last station
                found = true;
                break;
            }

            t = successor(t);
        }
        x = successor(x);
    }

    // Reinitialize nodes
    x = start;
    while(x && x->station.shortest_path != INT_MAX){
        x->station.shortest_path = INT_MAX;
        x->station.prev = NULL;
        x = successor(x);
    }

    return found;
}

bool find_inverse_path(service_station * start, service_station * finish){
    bool found = false;
    service_station * x, * t = NULL;

    start->station.shortest_path = 0;
    x = start;
    while(x->station.shortest_path < INT_MAX){

        t = x;
        while(x->station.max_autonomy >= x->station.dist - t->station.dist){
            if(t->station.shortest_path >= x->station.shortest_path + 1){
                // we found a BETTER PATH for t
                t->station.shortest_path = x->station.shortest_path + 1;
                t->station.prev = &(x->station);
            }

            if(t == finish) {
                found = true;
                break;
            }
            t = predecessor(t);
        }
        if(x == finish){ break; }
        x = predecessor(x);
    }

    if(found){
        // PATH DISCOVERED
        print_path(x->station.prev);
        printf("%u\n", x->station.dist);    // print last station
    }

    // Reinitialize nodes
    x = start;
    while(x && x->station.shortest_path != INT_MAX){     // otherwise when doing the comparisons we use the previous path values
        x->station.shortest_path = INT_MAX;
        x->station.prev = NULL;
        x = predecessor(x);
    }

    return found;
}

uint8_t strlen_m(char * str){
    char * end = str;
    for( ; *end != '\0'; end++){}
    return end - str;
}


int main(){

    service_station * root = NULL;
    char input[5666];
    char *token;
    uint8_t len;

    while( fgets(input, sizeof(input), stdin) ){
        token = strtok(input, " ");     // Read the command
        len = strlen_m(token);

        /******** AGGIUNGI-STAZIONE ********/
        if (len == 17){
            token = strtok(NULL, " ");
            service_station * s = add_station(&root, strtol(token, NULL, 10));

            if (s){
                printf("aggiunta\n");

                token = strtok(NULL, " ");      // read number of vehicles to add
                //uint16_t n_vehicles = strtol(token, NULL, 10);
                while ( (token = strtok(NULL, " ")) ){
                    add_vehicle(s, strtol(token, NULL, 10));
                }
            }else{
                printf("non aggiunta\n");
            }
            continue;
        }
        /******** AGGIUNGI-AUTO ********/
        if (len == 13){
            uint32_t dist, autonomy;

            token = strtok(NULL, " ");
            dist = strtol(token, NULL, 10);

            token = strtok(NULL, " ");
            autonomy = strtol(token, NULL, 10);
            if ( add_vehicle(search_station(root, dist), autonomy) ){
                printf("aggiunta\n");
            }else{
                printf("non aggiunta\n");
            }
            continue;
        }
        /******** ROTTAMA-AUTO ********/
        if (len == 12){
            uint32_t dist, autonomy;

            token = strtok(NULL, " ");
            dist = strtol(token, NULL, 10);

            token = strtok(NULL, " ");
            autonomy = strtol(token, NULL, 10);
            if ( demolish_vehicle(search_station(root, dist), autonomy) ){
                printf("rottamata\n");
            }else{
                printf("non rottamata\n");
            }
            continue;
        }
        /******** DEMOLISCI-STAZIONE : len=18 chars ********/
        if(input[0] == 'd'){
            token = strtok(NULL, " ");

            if ( demolish_station(&root, search_station(root, strtol(token, NULL, 10))) ){
                printf("demolita\n");
            }else{
                printf("non demolita\n");
            }
            continue;
        }
        /******** PIANIFICA-PERCORSO : len=18 chars ********/
        if (input[0] == 'p'){
            uint32_t start_dist, finish_dist;
            token = strtok(NULL, " ");
            start_dist = strtol(token, NULL, 10);

            token = strtok(NULL, " ");
            finish_dist = strtol(token, NULL, 10);

            if(start_dist < finish_dist){
                if( ! find_direct_path(search_station(root, start_dist), search_station(root, finish_dist)) ){
                    printf("nessun percorso\n");
                }
            }else{
                if( ! find_inverse_path(search_station(root, start_dist), search_station(root, finish_dist)) ){
                    printf("nessun percorso\n");
                }
            }
        }
    }

    free_tree(root);

    return 0;
}
