#ifndef CONNEXITE_H
#define CONNEXITE_H

void check_connectivity(int n, float adjacency_matrix[][MAX_SPECIES]);
void find_special_vertices(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES]);
void analyze_trophic_levels(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES], const char *target_species);
void remove_species(int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES], const char *target_species);
void simulate_population_dynamics(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES], float growth_rates[], float carrying_capacities[], float populations[], int iterations);

#endif
