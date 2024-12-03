//
// Created by meili on 03/12/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "centralite.h"

// Calcul des demi-degrés intérieur et extérieur
void compute_degrees(int n, float adjacency_matrix[][MAX_SPECIES], int in_degree[], int out_degree[]) {
    for (int i = 0; i < n; i++) {
        in_degree[i] = 0;
        out_degree[i] = 0;
        for (int j = 0; j < n; j++) {
            if (adjacency_matrix[j][i] > 0) {
                in_degree[i]++;
            }
            if (adjacency_matrix[i][j] > 0) {
                out_degree[i]++;
            }
        }
    }
}

// Calcul de la centralité d'intermédiarité
void compute_betweenness_centrality(int n, float adjacency_matrix[][MAX_SPECIES], float centrality[]) {
    for (int i = 0; i < n; i++) {
        centrality[i] = 0.0;
    }

    for (int s = 0; s < n; s++) {
        int visited[MAX_SPECIES] = {0};
        int queue[MAX_SPECIES];
        int front = 0, rear = 0;

        queue[rear++] = s;

        while (front < rear) {
            int current = queue[front++];
            for (int i = 0; i < n; i++) {
                if (adjacency_matrix[current][i] > 0 && !visited[i]) {
                    centrality[i]++;
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
        }
    }
}

// Simulation de la disparition d'une espèce
void simulate_species_removal(int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES], const char *target_species) {
    int target_index = -1;

    for (int i = 0; i < *n; i++) {
        if (strcmp(species[i], target_species) == 0) {
            target_index = i;
            break;
        }
    }

    if (target_index == -1) {
        printf("Espece non trouvee : %s\n", target_species);
        return;
    }

    printf("\nSuppression de l'espece : %s\n", target_species);

    for (int i = 0; i < *n; i++) {
        adjacency_matrix[target_index][i] = 0;
        adjacency_matrix[i][target_index] = 0;
    }

    for (int i = target_index; i < *n - 1; i++) {
        strcpy(species[i], species[i + 1]);
        for (int j = 0; j < *n; j++) {
            adjacency_matrix[i][j] = adjacency_matrix[i + 1][j];
            adjacency_matrix[j][i] = adjacency_matrix[j][i + 1];
        }
    }

    (*n)--;

    printf("L'espece %s a ete supprimee du reseau.\n", target_species);
}

