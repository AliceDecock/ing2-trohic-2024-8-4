#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "centralite.h"
#include "dotgraphe.h"

// Stock temporaire pour une espèce supprimée
typedef struct {
    char name[MAX_NAME_LENGTH];
    float adjacency_row[MAX_ESPECE];
    float adjacency_col[MAX_ESPECE];
    int valid; // Indique si une espèce supprimée est stockée
} RemovedSpecies;

RemovedSpecies removed_species = { .name = "", .valid = 0 };

// Fonction pour écrire l'état actuel du réseau dans un fichier texte
void write_network_to_file(const char *filename, int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE]) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier pour écriture");
        exit(EXIT_FAILURE);
    }

    // Écrire le nombre d'espèces
    fprintf(file, "%d\n", n);

    // Écrire les noms des espèces
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s\n", species[i]);
    }

    // Écrire la matrice d'adjacence
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%.2f ", adjacency_matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Etat du reseau ecrit dans le fichier : %s\n", filename);
}

// Fonction pour restaurer une espèce supprimée
void restore_species(int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE]) {
    if (!removed_species.valid) {
        printf("Aucune espece supprimee à restaurer.\n");
        return;
    }

    if (*n >= MAX_ESPECE) {
        printf("Impossible de restaurer l'espece. Limite maximale atteinte.\n");
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

    printf("Espece %s restauree avec succès.\n", removed_species.name);

    // Réinitialiser le stockage temporaire
    removed_species.valid = 0;

    // Écrire le réseau actuel dans un fichier temporaire
    write_network_to_file("network_state.txt", *n, species, adjacency_matrix);

    // Regénérer le fichier DOT
    generate_dot_file("network_state.txt", "reseau_trophique.dot");
    printf("Fichier DOT regenere apres restauration.\n");
}

// Fonction pour supprimer une espèce
void simulate_species_removal(int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE], const char *target_species) {
    int target_index = -1;

    // Trouver l'index de l'espèce cible
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

    if (removed_species.valid) {
        printf("Une espece supprimee existe déjà. Restaurez-la avant de supprimer une nouvelle espece.\n");
        return;
    }

    // Stocker l'espèce supprimée
    strcpy(removed_species.name, species[target_index]);
    for (int i = 0; i < *n; i++) {
        removed_species.adjacency_row[i] = adjacency_matrix[target_index][i];
        removed_species.adjacency_col[i] = adjacency_matrix[i][target_index];
    }
    removed_species.valid = 1;

    printf("\nSuppression de l'espece : %s\n", target_species);

    // Supprimer les connexions dans la matrice
    for (int i = 0; i < *n; i++) {
        adjacency_matrix[target_index][i] = 0;
        adjacency_matrix[i][target_index] = 0;
    }

    // Supprimer l'espèce de la liste
    for (int i = target_index; i < *n - 1; i++) {
        strcpy(species[i], species[i + 1]);
    }

    // Réorganiser la matrice d'adjacence pour décaler les lignes et colonnes
    for (int i = target_index; i < *n - 1; i++) {
        for (int j = 0; j < *n; j++) {
            adjacency_matrix[i][j] = adjacency_matrix[i + 1][j];
            adjacency_matrix[j][i] = adjacency_matrix[j][i + 1];
        }
    }

    (*n)--;

    printf("L'espece %s a ete supprimee du reseau.\n", target_species);

    // Écrire le réseau actuel dans un fichier temporaire
    write_network_to_file("network_state.txt", *n, species, adjacency_matrix);

    // Regénérer le fichier DOT
    generate_dot_file("network_state.txt", "reseau_trophique.dot");
    printf("Fichier DOT regenere apres suppression.\n");
}

// Calcul des demi-degrés intérieur et extérieur
void compute_degrees(int n, float adjacency_matrix[][MAX_ESPECE], int in_degree[], int out_degree[]) {
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
void compute_betweenness_centrality(int n, float adjacency_matrix[][MAX_ESPECE], float centrality[]) {
    for (int i = 0; i < n; i++) {
        centrality[i] = 0.0;
    }

    for (int s = 0; s < n; s++) {
        int visited[MAX_ESPECE] = {0};
        int queue[MAX_ESPECE];
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