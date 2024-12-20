#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

typedef struct vehicle_s {
    // TODO
} vehicle;

struct station_data {
    uint32_t dist;               // Distance from the beginning of the highway
    uint32_t max_autonomy;       // maximum autonomy between the entire fleet of vehicles
    uint32_t currShortestPath;   // The shortest path found until this moment (Dijkstra)
    vehicle *fleet;              // RB-Tree of vehicles
    struct station_data *prev;   // Previous station in the shortest path (Dijkstra)
};

typedef struct station_node_s{
    uint8_t color;
    struct station_node_s * parent;
    struct station_node_s * left;
    struct station_data station;
    struct station_node_s * right;
} service_station;

#endif //STRUCTS_H
