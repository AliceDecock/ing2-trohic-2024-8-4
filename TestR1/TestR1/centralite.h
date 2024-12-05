
//
// Created by meili on 03/12/2024.
//

#ifndef CENTRALITE_H
#define CENTRALITE_H

void compute_degrees(int n, float adjacency_matrix[][MAX_ESPECE], int in_degree[], int out_degree[]);
void compute_betweenness_centrality(int n, float adjacency_matrix[][MAX_ESPECE], float centrality[]);
void simulate_species_removal(int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE], const char *target_species);
void restore_species(int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE]);
#endif
