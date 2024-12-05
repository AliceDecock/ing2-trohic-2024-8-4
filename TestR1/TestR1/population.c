#include <stdio.h>
#include <string.h>
#include "population.h"

void initialize_population(int n, PopulationData *pop_data) {
    for (int i = 0; i < n; i++) {
        pop_data->populations[i] = 10.0;           // Population initiale par défaut
        pop_data->growth_rates[i] = 0.1;          // Rythme de croissance par défaut
        pop_data->carrying_capacities[i] = 100.0; // Capacité de portage par défaut
    }
}

void update_population_dynamics(int n, float adjacency_matrix[][MAX_SPECIES], char species[][MAX_NAME_LENGTH], PopulationData *pop_data, int iterations) {
    float new_populations[MAX_SPECIES];
    for (int t = 0; t < iterations; t++) {
        printf("\nIteration %d:\n", t + 1);
        for (int i = 0; i < n; i++) {
            float adjusted_capacity = pop_data->carrying_capacities[i];
            for (int j = 0; j < n; j++) {
                if (adjacency_matrix[j][i] > 0) {
                    adjusted_capacity += adjacency_matrix[j][i] * pop_data->populations[j];
                }
            }

            new_populations[i] = pop_data->populations[i] + pop_data->growth_rates[i] * pop_data->populations[i] *
                                                            (1 - pop_data->populations[i] / adjusted_capacity);

            for (int j = 0; j < n; j++) {
                if (adjacency_matrix[i][j] > 0) {
                    new_populations[i] -= adjacency_matrix[i][j] * pop_data->populations[j];
                }
            }

            if (new_populations[i] < 0) {
                new_populations[i] = 0;
            }
        }

        for (int i = 0; i < n; i++) {
            pop_data->populations[i] = new_populations[i];
            printf("%s: %.2f\n", species[i], pop_data->populations[i]);
        }
    }
}

void display_population(int n, char species[][MAX_NAME_LENGTH], PopulationData *pop_data) {
    printf("\nPopulation actuelle :\n");
    for (int i = 0; i < n; i++) {
        printf("- %s: %.2f\n", species[i], pop_data->populations[i]);
    }
}

void adjust_parameters(int n, char species[][MAX_NAME_LENGTH], PopulationData *pop_data, float adjacency_matrix[][MAX_SPECIES]) {
    printf("\n=== Ajustement des Parametres ===\n");
    for (int i = 0; i < n; i++) {
        printf("Espece %s\n", species[i]);
        printf("Taux de croissance actuel : %.2f\n", pop_data->growth_rates[i]);
        printf("Nouvelle valeur (ou -1 pour conserver) : ");
        float new_r;
        scanf("%f", &new_r);
        if (new_r >= 0) pop_data->growth_rates[i] = new_r;

        printf("Capacite de portage actuelle : %.2f\n", pop_data->carrying_capacities[i]);
        printf("Nouvelle valeur (ou -1 pour conserver) : ");
        float new_k;
        scanf("%f", &new_k);
        if (new_k >= 0) pop_data->carrying_capacities[i] = new_k;
    }
}