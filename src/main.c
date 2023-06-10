#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"
#include "station.h"
#include "vehicle.h"
#include "find_path.h"
#include "test.h"

// Correct
uint8_t strlen_m(char * str){
    char * end = str;
    for( ; *end != '\0'; end++){}
    return end - str;
}


int main(){

    service_station * root = NULL;
    char input[5666];
    char *token;
    uint8_t len;

    while( fgets(input, sizeof(input), stdin) ){
        token = strtok(input, " ");     // Read the command
        len = strlen_m(token);

        /******** AGGIUNGI-STAZIONE ********/
        if (len == 17){
            token = strtok(NULL, " ");
            service_station * s = add_station(&root, strtol(token, NULL, 10));

            if (s){
                printf("aggiunta\n");

                token = strtok(NULL, " ");      // read number of vehicles to add
                //uint16_t n_vehicles = strtol(token, NULL, 10);
                while ( (token = strtok(NULL, " ")) ){
                    add_vehicle(s, strtol(token, NULL, 10));
                }
            }else{
                printf("non aggiunta\n");
            }
            continue;
        }
        /******** AGGIUNGI-AUTO ********/
        if (len == 13){
            uint32_t dist, autonomy;

            token = strtok(NULL, " ");
            dist = strtol(token, NULL, 10);

            token = strtok(NULL, " ");
            autonomy = strtol(token, NULL, 10);
            if ( add_vehicle(search_station(root, dist), autonomy) ){
                printf("aggiunta\n");
            }else{
                printf("non aggiunta\n");
            }
            continue;
        }
        /******** ROTTAMA-AUTO ********/
        if (len == 12){
            uint32_t dist, autonomy;

            token = strtok(NULL, " ");
            dist = strtol(token, NULL, 10);

            token = strtok(NULL, " ");
            autonomy = strtol(token, NULL, 10);
            if ( demolish_vehicle(search_station(root, dist), autonomy) ){
                printf("rottamata\n");
            }else{
                printf("non rottamata\n");
            }
            continue;
        }
        /******** DEMOLISCI-STAZIONE : len=18 chars ********/
        if(input[0] == 'd'){
            token = strtok(NULL, " ");

            if ( demolish_station(&root, search_station(root, strtol(token, NULL, 10))) ){
                printf("demolita\n");
            }else{
                printf("non demolita\n");
            }
            continue;
        }
        /******** PIANIFICA-PERCORSO : len=18 chars ********/
        if (input[0] == 'p'){
            uint32_t start_dist, finish_dist;
            token = strtok(NULL, " ");
            start_dist = strtol(token, NULL, 10);

            token = strtok(NULL, " ");
            finish_dist = strtol(token, NULL, 10);

            if(start_dist < finish_dist){
                if( ! find_direct_path(search_station(root, start_dist), search_station(root, finish_dist)) ){
                    printf("nessun percorso\n");
                }
            }else{
                if( ! find_inverse_path(search_station(root, start_dist), search_station(root, finish_dist)) ){
                    printf("nessun percorso\n");
                }
            }
        }
    }

    free_tree(root);

    return 0;
}
