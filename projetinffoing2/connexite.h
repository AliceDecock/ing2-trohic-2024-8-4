//
// Created by meili on 30/11/2024.
//

#ifndef CONNEXITE_H
#define CONNEXITE_H

void check_connectivity(int n, float adjacency_matrix[][MAX_ESPECE]);
void find_special_vertices(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE]);
void analyze_trophic_levels(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE], const char *target_species);

#endif