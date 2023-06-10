#include "vehicle.h"
#include <stdlib.h>

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

// DEBUG
void print_vehicles(vehicle * x){
    printf("\n");
    while(x){
        printf("Autonomy: %u; Qt: %u\n", x->autonomy, x->quantity);
        x = x->next;
    }
}
