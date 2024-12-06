
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "connexite.h"

#define MAX_ESPECE 100

// Fonction pour vérifier si un graphe est connexe
int is_connected(int n, float adjacency_matrix[][MAX_ESPECE]) {
    int visited[MAX_ESPECE] = {0};
    int queue[MAX_ESPECE];
    int front = 0, rear = 0;

    // Parcours en largeur (BFS)
    queue[rear++] = 0; // Commencer avec le sommet 0
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

    // Vérifier si tous les sommets ont été visités
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return 0; // Le graphe n'est pas connexe
        }
    }
    return 1; // Le graphe est connexe
}

// Fonction pour vérifier la connexité forte
int is_strongly_connected(int n, float adjacency_matrix[][MAX_ESPECE]) {
    int visited[MAX_ESPECE];
    int queue[MAX_ESPECE];
    int front, rear;

    // Vérifier la connexité dans le graphe original
    memset(visited, 0, sizeof(visited));
    front = rear = 0;
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

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return 0; // Pas fortement connexe
        }
    }

    // Transposer le graphe
    float transposed[MAX_ESPECE][MAX_ESPECE] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjacency_matrix[i][j] > 0) {
                transposed[j][i] = adjacency_matrix[i][j];
            }
        }
    }

    // Vérifier la connexité dans le graphe transposé
    memset(visited, 0, sizeof(visited));
    front = rear = 0;
    queue[rear++] = 0;
    visited[0] = 1;

    while (front < rear) {
        int current = queue[front++];
        for (int i = 0; i < n; i++) {
            if (transposed[current][i] > 0 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return 0; // Pas fortement connexe
        }
    }

    return 1; // Fortement connexe
}

// Fonction pour identifier les composantes connexes
void find_connected_components(int n, float adjacency_matrix[][MAX_ESPECE]) {
    int visited[MAX_ESPECE] = {0};
    int queue[MAX_ESPECE];
    int front, rear, component = 0;

    printf("Composantes connexes :\n");

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            printf("Composante %d : ", ++component);
            front = rear = 0;
            queue[rear++] = i;
            visited[i] = 1;

            while (front < rear) {
                int current = queue[front++];
                printf("%d ", current);
                for (int j = 0; j < n; j++) {
                    if (adjacency_matrix[current][j] > 0 && !visited[j]) {
                        visited[j] = 1;
                        queue[rear++] = j;
                    }
                }
            }
            printf("\n");
        }
    }
}

// Fonction principale pour analyser la connexité
void analyze_connectivity(int n, float adjacency_matrix[][MAX_ESPECE]) {
    if (is_connected(n, adjacency_matrix)) {
        printf("Le reseau est connexe.\n");

        if (is_strongly_connected(n, adjacency_matrix)) {
            printf("Le reseau est fortement connexe.\n");
        } else {
            printf("Le reseau est faiblement connexe.\n");
        }

        find_connected_components(n, adjacency_matrix);
    } else {
        printf("Le reseau n'est pas connexe.\n");
    }
}


// Fonction pour rechercher des sommets particuliers
void find_special_vertices(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE]) {
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
void print_ascendants(int current_index, int depth, int n, float adjacency_matrix[][MAX_ESPECE], char species[][MAX_NAME_LENGTH], int processed[]) {
    for (int i = 0; i < n; i++) {
        if (adjacency_matrix[i][current_index] > 0 && !processed[i]) {
            printf("%*s%s --> %s\n", depth * 4, "", species[i], species[current_index]);
            processed[i] = 1;
            print_ascendants(i, depth + 1, n, adjacency_matrix, species, processed);
        }
    }
}

void analyze_trophic_levels(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE], const char *target_species) {
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
    int processed[MAX_ESPECE] = {0};
    print_ascendants(target_index, 0, n, adjacency_matrix, species, processed);

    printf("\nNiveaux trophiques :\n");
    int trophic_levels[MAX_ESPECE] = {0};
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

