#ifndef DYNAMIQUE_H
#define DYNAMIQUE_H

#include "network.h"

// Functions for dynamic population management
void start_simulation(int n, char species[][MAX_NAME_LENGTH], float populations[], float growth_rates[], float carrying_capacities[], float anthropic_impact[], float adjacency_matrix[][MAX_ESPECE], int iterations);
void pause_simulation();
void modify_species_parameters(int n, char species[][MAX_NAME_LENGTH], float growth_rates[], float carrying_capacities[]);
void display_current_state(int n, char species[][MAX_NAME_LENGTH], float populations[]);
void save_state(const char *filename, int n, char species[][MAX_NAME_LENGTH], float populations[], float growth_rates[], float carrying_capacities[]);
void population_dynamics_menu(int n, char species[][MAX_NAME_LENGTH], float populations[], float growth_rates[], float carrying_capacities[], float anthropic_impact[], float adjacency_matrix[][MAX_ESPECE]);

#endif // DYNAMIQUE_H