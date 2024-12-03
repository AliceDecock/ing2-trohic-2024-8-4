
//
// Created by meili on 03/12/2024.
//
#ifndef DYNAMIQUE_H
#define DYNAMIQUE_H

float compute_adjusted_carrying_capacity(int index, int n, float adjacency_matrix[][MAX_ESPECE], float populations[], float base_capacity);

void simulate_population_dynamics( int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE],
                                   float growth_rates[], float carrying_capacities[], float populations[], int iterations);

#endif

