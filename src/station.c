#include "station.h"

/** CONDITIONAL FUNCTIONS **/
bool is_red(service_station * node){
    return (node != NULL) ? node->color == RED : false;
}

bool is_left_child(service_station* node){
    service_station* parentNode = node->parent;
    return parentNode != NULL && parentNode->left == node;
}

bool is_right_child(service_station* node){
    service_station* parentNode = node->parent;
    return parentNode != NULL && parentNode->right == node;
}

bool has_parent(service_station* node){
    // If node==NULL the parentOf() will return NULL
    return node->parent;
}

/** RELATIONS **/
service_station* grandparent_of(service_station* const node){
    service_station* parentNode = node->parent;
    return (parentNode != NULL) ? parentNode->parent : NULL;
}

service_station* uncle_of(service_station* const node){
    service_station* grandParentNode = grandparent_of(node);
    if(grandParentNode != NULL){
        service_station* parentNode = node->parent;
        if(is_left_child(parentNode)){
            return grandParentNode->right;
        }else{
            return grandParentNode->left;
        }
    }
    return NULL;
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
    while(is_red(s->parent)){
        // If parentNode is red then I'm sure node has a grandparent because the root can't be red
        service_station * parent = s->parent;
        service_station * grandParent = grandparent_of(s);
        service_station * uncle = uncle_of(s);

        if(is_red(uncle)){
            parent->color = BLACK;
            uncle->color = BLACK;
            grandParent->color = RED;

            s = grandParent;
        }else{
            // If parent is left
            if(is_left_child(parent)){
                // If node is innerChild
                if(is_right_child(s)){
                    leftRotate(root, parent);

                    s = parent; // So that at the next loop we exit because parent (the curr "node") will be black
                }
                s->parent->color = BLACK; // The node which was previously "node" and is now root of the subtree is colored black
                grandParent->color = RED;
                rightRotate(root, grandParent); // The order of rotation and coloring is not important
            }
                // If parent is right
            else{
                // If node is innerChild
                if(is_left_child(s)){
                    rightRotate(root, parent);

                    s = parent;
                }
                s->parent->color = BLACK;
                grandParent->color = RED;
                leftRotate(root, grandParent);
            }
        }
    }
    if(!has_parent(s)){ s->color = BLACK;}
}

void fixTreeAfterDelete(service_station ** root, service_station * s){
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
    }
    if(s) { s->color = BLACK; }
}

bool add_station(service_station ** root, uint32_t dist){
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
            return false;
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
    return true;
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
