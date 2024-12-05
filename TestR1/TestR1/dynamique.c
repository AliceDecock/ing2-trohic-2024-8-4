
//
// Created by meili on 03/12/2024.
//

#include <stdio.h>
#include <string.h>
#include "network.h"
#include "dynamique.h"

// Fonction pour calculer K ajusté pour une espèce
float compute_adjusted_carrying_capacity(int index, int n, float adjacency_matrix[][MAX_ESPECE], float populations[], float base_capacity) {
    float adjusted_capacity = base_capacity;
    for (int i = 0; i < n; i++) {
        if (adjacency_matrix[i][index] > 0) {
            adjusted_capacity += adjacency_matrix[i][index] * populations[i];
        }
    }
    return adjusted_capacity;
}

// Simulation de la dynamique des populations
void simulate_population_dynamics(
        int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE],
        float growth_rates[], float carrying_capacities[], float populations[], int iterations) {

    float new_populations[MAX_ESPECE];

    printf("\nSimulation de la dynamique des populations :\n");

    for (int t = 0; t < iterations; t++) {
        printf("\n--- Iteration %d ---\n", t + 1);

        for (int i = 0; i < n; i++) {
            // Calculer la capacité de portage ajustée en fonction des prédécesseurs
            float adjusted_capacity = compute_adjusted_carrying_capacity(i, n, adjacency_matrix, populations, carrying_capacities[i]);

            // Modèle logistique pour la croissance
            new_populations[i] = populations[i] + growth_rates[i] * populations[i] * (1 - populations[i] / adjusted_capacity);

            // Retirer les prédations par les successeurs
            for (int j = 0; j < n; j++) {
                if (adjacency_matrix[i][j] > 0) {
                    // Pondérer la prédation par un coefficient multiplicateur
                    new_populations[i] -= 0.5 * adjacency_matrix[i][j] * populations[j];
                }
            }
            // Assurer une population positive
            if (new_populations[i] < 0) {
                new_populations[i] = 0;
            }
        }

        // Mettre à jour les populations
        for (int i = 0; i < n; i++) {
            populations[i] = new_populations[i];
            printf("%s: %.2f\n", species[i], populations[i]);
        }
    }

    printf("\nSimulation terminee.\n");
}