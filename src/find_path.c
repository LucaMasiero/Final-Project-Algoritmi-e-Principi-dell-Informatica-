#include "find_path.h"

bool find_direct_path(service_station * start, service_station * finish){
    // Reinitialize path of each station
    start->station.shortest_path = 0;

    service_station * x = successor(start), * t = NULL;
    while(x != finish){     // otherwise when doing the comparisons we use the previous path values
        x->station.shortest_path = INT_MAX;
        x = successor(x);
    }

    x = start;
    while(x != finish){

        t = successor(x);
        while(t && x->station.max_autonomy >= t->station.dist - x->station.dist){
            if(t->station.shortest_path > x->station.shortest_path + 1){
                // we found a BETTER PATH for t
                t->station.shortest_path = x->station.shortest_path + 1;
                t->station.prev = &(x->station);
            }

            if(t == finish){
                // PATH DISCOVERED
                station_data * sd = &(t->station);
                while(sd != NULL){
                    printf("%u <-", sd->dist);
                    sd = sd->prev;
                }
                printf(" START\n");
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
    while(x != finish){

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
        station_data * sd = &(x->station);
        while(sd != NULL){
            printf("%u <-", sd->dist);
            sd = sd->prev;
        }
        printf(" START");
        return true;
    }

    return false;
}
