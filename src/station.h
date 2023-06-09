#ifndef STATION_H
#define STATION_H

    #include "struct.h"

    #define RED 'R'
    #define BLACK 'B'

    /***** RELATIONS *****/
    service_station * predecessor(service_station * x);

    service_station * successor(service_station * x);

    /***** MAIN OPERATIONS *****/
    service_station * new_station(uint32_t d);

    service_station * search_station(service_station * root, uint32_t dist);

service_station * add_station(service_station ** root, uint32_t dist);

    bool demolish_station(service_station ** root, service_station * z);

    void fixTreeAfterInsert(service_station ** root, service_station * s);

    void fixTreeAfterDelete(service_station ** root, service_station *s);

    /***** FREE *****/
    void free_tree(service_station * root);

#endif //STATION_H
