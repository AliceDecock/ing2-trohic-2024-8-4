
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"

// Fonction pour verifier la connexite du reseau
void check_connectivity(int n, float adjacency_matrix[][MAX_SPECIES]) {
    int visited[MAX_SPECIES] = {0};
    int queue[MAX_SPECIES];
    int front = 0, rear = 0;

    queue[rear++] = 0;
    visited[0] = 1;

    while (front < rear) {
        int current = queue[front++];
        for (int i = 0; i < n; i++) {
            if (adjacency_matrix[current][i] > 0 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    int is_connected = 1;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            is_connected = 0;
            break;
        }
    }

    if (is_connected) {
        printf("Le reseau est connexe.\n");
    } else {
        printf("Le reseau n'est pas connexe. Il peut etre divise en sous-ecosystemes.\n");
    }
}

// Fonction pour rechercher des sommets particuliers
void find_special_vertices(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES]) {
    printf("Derniers maillons (pas de successeurs) :\n");
    for (int j = 0; j < n; j++) {
        int has_predecessor = 0;
        for (int i = 0; i < n; i++) {
            if (adjacency_matrix[i][j] > 0) {
                has_predecessor = 1;
                break;
            }
        }
        if (!has_predecessor) {
            printf("- %s\n", species[j]);
        }
    }

    printf("\nProducteurs primaires (pas de predecesseurs) :\n");
    for (int i = 0; i < n; i++) {
        int has_successor = 0;
        for (int j = 0; j < n; j++) {
            if (adjacency_matrix[i][j] > 0) {
                has_successor = 1;
                break;
            }
        }
        if (!has_successor) {
            printf("- %s\n", species[i]);
        }
    }

    printf("\nEspeces avec une seule source d'alimentation :\n");
    for (int j = 0; j < n; j++) {
        int count_predecessors = 0;
        for (int i = 0; i < n; i++) {
            if (adjacency_matrix[i][j] > 0) {
                count_predecessors++;
            }
        }
        if (count_predecessors == 1) {
            printf("- %s\n", species[j]);
        }
    }
}

// Fonction pour analyser les niveaux trophiques et afficher les ascendants
void print_ascendants(int current_index, int depth, int n, float adjacency_matrix[][MAX_SPECIES], char species[][MAX_NAME_LENGTH], int processed[]) {
    for (int i = 0; i < n; i++) {
        if (adjacency_matrix[i][current_index] > 0 && !processed[i]) {
            printf("%*s%s --> %s\n", depth * 4, "", species[i], species[current_index]);
            processed[i] = 1;
            print_ascendants(i, depth + 1, n, adjacency_matrix, species, processed);
        }
    }
}

void analyze_trophic_levels(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES], const char *target_species) {
    int target_index = -1;

    // Trouver l'index de l'espèce cible
    for (int i = 0; i < n; i++) {
        if (strcmp(species[i], target_species) == 0) {
            target_index = i;
            break;
        }
    }

    if (target_index == -1) {
        printf("Espece non trouvee : %s\n", target_species);
        return;
    }

    printf("\nEtude des niveaux trophiques et des chaines alimentaires pour l'espece : %s\n", target_species);

    printf("\nGraphe des ascendants :\n");
    int processed[MAX_SPECIES] = {0};
    print_ascendants(target_index, 0, n, adjacency_matrix, species, processed);

    printf("\nNiveaux trophiques :\n");
    int trophic_levels[MAX_SPECIES] = {0};
    trophic_levels[target_index] = 1;

    for (int level = 1; level <= n; level++) {
        int changes = 0;
        for (int j = 0; j < n; j++) {
            if (trophic_levels[j] == level) {
                for (int i = 0; i < n; i++) {
                    if (adjacency_matrix[i][j] > 0 && trophic_levels[i] == 0) {
                        trophic_levels[i] = level + 1;
                        changes = 1;
                    }
                }
            }
        }
        if (!changes) break;
    }

    int max_level = 0;
    for (int i = 0; i < n; i++) {
        if (trophic_levels[i] > 0) {
            printf("Niveau %d: %s\n", trophic_levels[i], species[i]);
            if (trophic_levels[i] > max_level) {
                max_level = trophic_levels[i];
            }
        }
    }

    printf("\nLe niveau trophique maximal dans le reseau est : %d\n", max_level);
    printf("Dans les reseaux trophiques en general, le niveau trophique maximal est limite par la disponibilite de l'energie et sa perte a chaque niveau trophique.\n");
}

// Fonction pour supprimer une espèce
void remove_species(int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES], const char *target_species) {
    int target_index = -1;

    // Trouver l'index de l'espèce à supprimer
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

// Fonction pour simuler la dynamique des populations
void simulate_population_dynamics(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES], float growth_rates[], float carrying_capacities[], float populations[], int iterations) {
    float new_populations[MAX_SPECIES];

    printf("\nSimulation de la dynamique des populations :\n");

    for (int t = 0; t < iterations; t++) {
        printf("\nIteration %d:\n", t + 1);

        for (int i = 0; i < n; i++) {
            float adjusted_capacity = carrying_capacities[i];
            for (int j = 0; j < n; j++) {
                if (adjacency_matrix[j][i] > 0) {
                    adjusted_capacity += adjacency_matrix[j][i] * populations[j];
                }
            }

            new_populations[i] = populations[i] + growth_rates[i] * populations[i] * (1 - populations[i] / adjusted_capacity);

            for (int j = 0; j < n; j++) {
                if (adjacency_matrix[i][j] > 0) {
                    new_populations[i] -= adjacency_matrix[i][j] * populations[j];
                }
            }

            if (new_populations[i] < 0) {
                new_populations[i] = 0;
            }
        }

        for (int i = 0; i < n; i++) {
            populations[i] = new_populations[i];
            printf("%s: %.2f\n", species[i], populations[i]);
        }
    }

    printf("\nSimulation terminee.\n");
}
