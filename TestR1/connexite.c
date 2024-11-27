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
