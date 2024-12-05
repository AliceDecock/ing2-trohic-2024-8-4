#include "connexite.h"
#include <stdio.h>
#include <string.h>
#include "connexite.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Fonction auxiliaire : recherche en profondeur (DFS)
static void dfs(int node, int n, float adjacency_matrix[][MAX_ESPECE], bool visited[]) {
    visited[node] = true;
    for (int i = 0; i < n; i++) {
        if (adjacency_matrix[node][i] > 0 && !visited[i]) {
            dfs(i, n, adjacency_matrix, visited);
        }
    }
}

// Vérifie si le graphe est connexe
bool is_connected(int n, float adjacency_matrix[][MAX_ESPECE]) {
    bool visited[MAX_ESPECE] = {false};
    dfs(0, n, adjacency_matrix, visited);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return false; // Si un sommet n'est pas visité, le graphe n'est pas connexe
        }
    }
    return true;
}

// Vérifie si le graphe est fortement connexe
bool is_strongly_connected(int n, float adjacency_matrix[][MAX_ESPECE]) {
    // Étape 1 : Vérification de connexité avec la matrice normale
    bool visited[MAX_ESPECE] = {false};
    dfs(0, n, adjacency_matrix, visited);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return false;
        }
    }

    // Étape 2 : Vérification avec la matrice transposée
    float transposed[MAX_ESPECE][MAX_ESPECE] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transposed[j][i] = adjacency_matrix[i][j];
        }
    }

    memset(visited, 0, sizeof(visited));
    dfs(0, n, transposed, visited);

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            return false;
        }
    }

    return true;
}

// Analyse complète de la connexité
void analyze_connectivity(int n, float adjacency_matrix[][MAX_ESPECE]) {
    printf("\n=== Analyse de la Connexité ===\n");

    if (is_connected(n, adjacency_matrix)) {
        printf("Le réseau est connexe.\n");
    } else {
        printf("Le réseau n'est pas connexe.\n");
    }

    if (is_strongly_connected(n, adjacency_matrix)) {
        printf("Le réseau est fortement connexe.\n");
    } else {
        printf("Le réseau n'est pas fortement connexe.\n");
    }

    find_connected_components(n, adjacency_matrix);
}

// Trouve et affiche les composantes connexes
void find_connected_components(int n, float adjacency_matrix[][MAX_ESPECE]) {
    bool visited[MAX_ESPECE] = {false};
    int component[MAX_ESPECE] = {0};
    int component_count = 0;

    printf("\nComposantes connexes :\n");
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            component_count++;
            dfs(i, n, adjacency_matrix, visited);
            printf("Composante %d : ", component_count);
            for (int j = 0; j < n; j++) {
                if (visited[j] && component[j] == 0) {
                    printf("%d ", j);
                    component[j] = component_count;
                }
            }
            printf("\n");
        }
    }
}

// Recherche des sommets sans prédécesseurs ou successeurs
void find_special_vertices(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE]) {
    printf("\n=== Sommets Particuliers ===\n");
    for (int i = 0; i < n; i++) {
        bool has_successors = false, has_predecessors = false;

        // Vérifie les successeurs
        for (int j = 0; j < n; j++) {
            if (adjacency_matrix[i][j] > 0) {
                has_successors = true;
                break;
            }
        }

        // Vérifie les prédécesseurs
        for (int j = 0; j < n; j++) {
            if (adjacency_matrix[j][i] > 0) {
                has_predecessors = true;
                break;
            }
        }

        if (!has_successors) {
            printf("- %s n'a pas de successeurs.\n", species[i]);
        }

        if (!has_predecessors) {
            printf("- %s n'a pas de prédécesseurs.\n", species[i]);
        }
    }
}
// Analyse des niveaux trophiques pour une espèce donnée
void analyze_trophic_levels(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE], const char *target_species) {
    printf("\n=== Analyse des Niveaux Trophiques ===\n");
    printf("Espèce cible : %s\n", target_species);

    // Trouver l'indice de l'espèce cible
    int target_index = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(species[i], target_species) == 0) {
            target_index = i;
            break;
        }
    }

    if (target_index == -1) {
        printf("Espèce non trouvée : %s\n", target_species);
        return;
    }

    // Afficher les ascendants directs
    printf("Ascendants directs de %s :\n", target_species);
    for (int i = 0; i < n; i++) {
        if (adjacency_matrix[i][target_index] > 0) {
            printf("- %s (poids : %.2f)\n", species[i], adjacency_matrix[i][target_index]);
        }
    }

    // Afficher les descendants directs
    printf("Descendants directs de %s :\n", target_species);
    for (int i = 0; i < n; i++) {
        if (adjacency_matrix[target_index][i] > 0) {
            printf("- %s (poids : %.2f)\n", species[i], adjacency_matrix[target_index][i]);
        }
    }

    // Analyse supplémentaire (si nécessaire)
    printf("Analyse des niveaux trophiques terminée pour %s.\n", target_species);
}