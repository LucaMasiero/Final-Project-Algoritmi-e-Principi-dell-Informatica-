#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

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

#endif //STRUCTS_H
