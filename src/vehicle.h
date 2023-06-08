#ifndef VEHICLE_H
#define VEHICLE_H

    #include "struct.h"

    bool add_vehicle(service_station * station, uint32_t a);

    /**
     * @return true if the vehicle was demolished, false if there were
     *         no vehicle with that autonomy ("non rottamato")
     */
    bool demolish_vehicle(service_station * station, uint32_t a);

    /****** DEBUG ******/
    void print_vehicles(vehicle * x);

#endif //VEHICLE_H
