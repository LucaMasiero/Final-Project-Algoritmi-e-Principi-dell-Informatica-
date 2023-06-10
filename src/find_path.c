#include "find_path.h"

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
