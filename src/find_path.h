#ifndef FIND_PATH_H
#define FIND_PATH_H

    #include "struct.h"
    #include "station.h"
    #include "vehicle.h"

    bool find_direct_path(service_station * start, service_station * finish);

    bool find_inverse_path(service_station * start, service_station * finish);

#endif //FIND_PATH_H
