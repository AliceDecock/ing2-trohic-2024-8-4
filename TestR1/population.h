#ifndef POPULATION_H
#define POPULATION_H

#include "network.h"

typedef struct {
    float populations[MAX_SPECIES];
    float growth_rates[MAX_SPECIES];
    float carrying_capacities[MAX_SPECIES];
} PopulationData;

// Déclaration des fonctions
void initialize_population(int n, PopulationData *pop_data);
void update_population_dynamics(int n, float adjacency_matrix[][MAX_SPECIES], char species[][MAX_NAME_LENGTH], PopulationData *pop_data, int iterations);
void display_population(int n, char species[][MAX_NAME_LENGTH], PopulationData *pop_data);
void adjust_parameters(int n, char species[][MAX_NAME_LENGTH], PopulationData *pop_data, float adjacency_matrix[][MAX_SPECIES]);

#endif
