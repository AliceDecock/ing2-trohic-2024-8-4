#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "centralite.h"

// Stock temporaire pour une espèce supprimée
typedef struct {
    char name[MAX_NAME_LENGTH];
    float adjacency_row[MAX_SPECIES];
    float adjacency_col[MAX_SPECIES];
} RemovedSpecies;

RemovedSpecies removed_species;

// Fonction pour restaurer une espèce supprimée
void restore_species(int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES]) {
    if (strlen(removed_species.name) == 0) {
        printf("Aucune espece supprimee à restaurer.\n");
        return;
    }

    int restored_index = *n;
    (*n)++;

    // Ajouter l'espèce dans la liste
    strcpy(species[restored_index], removed_species.name);

    // Restaurer les lignes et colonnes de la matrice
    for (int i = 0; i < *n; i++) {
        adjacency_matrix[i][restored_index] = removed_species.adjacency_col[i];
        adjacency_matrix[restored_index][i] = removed_species.adjacency_row[i];
    }

    printf("Espece %s restauree avec succes.\n", removed_species.name);

    // Réinitialiser le stockage temporaire
    memset(&removed_species, 0, sizeof(RemovedSpecies));
}

// Mise à jour de la fonction de suppression pour stocker les données
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

    // Stocker l'espèce supprimée
    strcpy(removed_species.name, species[target_index]);
    for (int i = 0; i < *n; i++) {
        removed_species.adjacency_row[i] = adjacency_matrix[target_index][i];
        removed_species.adjacency_col[i] = adjacency_matrix[i][target_index];
    }

    printf("\nSuppression de l'espece : %s\n", target_species);

    // Supprimer l'espèce de la matrice et de la liste
    for (int i = 0; i < *n; i++) {
        adjacency_matrix[target_index][i] = 0;
        adjacency_matrix[i][target_index] = 0;
    }

    for (int i = target_index; i < *n - 1; i++) {
        strcpy(species[i], species[i + 1]);
        for (int j = 0; j < *n; j++) {
            adjacency_matrix[i][j] = adjacency_matrix[i + 1][j];
            adjacency_matrix[j][i] = adjacency_matrix[j + 1][i];
        }
    }

    (*n)--;

    printf("L'espece %s a ete supprimee du reseau.\n", target_species);
}

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
