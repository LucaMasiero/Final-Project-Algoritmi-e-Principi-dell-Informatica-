#include "find_path.h"

void print_path(station_data * s){
    if(s == NULL) { return; }
    print_path(s->prev);
    printf("%u ", s->dist);
}

bool find_direct_path(service_station * start, service_station * finish){
    // Reinitialize path of each station
    start->station.shortest_path = 0;

    service_station * x = successor(start), * t = NULL;
    while(x != finish){     // otherwise when doing the comparisons we use the previous path values
        x->station.shortest_path = INT_MAX;
        x = successor(x);
    }

    x = start;
    while(x->station.shortest_path < INT_MAX){

        t = successor(x);
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
                return true;
            }

            t = successor(t);
        }
        x = successor(x);
    }
    return false;
}

bool find_inverse_path(service_station * start, service_station * finish){
    // Reinitialize path of each station
    start->station.shortest_path = 0;

    service_station * x = predecessor(start), * t = NULL;
    while(x != finish){     // otherwise when doing the comparisons we use the previous path values
        x->station.shortest_path = INT_MAX;
        x = predecessor(x);
    }

    x = start;
    while(x->station.shortest_path < INT_MAX){

        t = predecessor(x);

        while(t && x->station.max_autonomy >= x->station.dist - t->station.dist){
            if(t->station.shortest_path >= x->station.shortest_path + 1){
                // we found a BETTER PATH for t
                t->station.shortest_path = x->station.shortest_path + 1;
                t->station.prev = &(x->station);
            }

            t = predecessor(t);
        }
        x = predecessor(x);
    }

    if(x->station.prev){
        // PATH DISCOVERED
        print_path(x->station.prev);
        printf("%u\n", x->station.dist);    // print last station
        return true;
    }

    return false;
}
