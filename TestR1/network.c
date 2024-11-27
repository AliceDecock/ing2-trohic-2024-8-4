//
// Created by alice on 27/11/2024.
//

#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour lire le fichier reseau
void read_network(const char *filename, int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", n); // Lire le nombre d'especes

    // Lire les noms des especes
    for (int i = 0; i < *n; i++) {
        fscanf(file, "%s", species[i]);
    }

    // Lire la matrice d'adjacence
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%f", &adjacency_matrix[i][j]);
        }
    }

    fclose(file);
}

// Fonction pour afficher la liste des especes
void display_species(int n, char species[][MAX_NAME_LENGTH]) {
    printf("Liste des especes :\n");
    for (int i = 0; i < n; i++) {
        printf("- %s\n", species[i]);
    }
}

// Fonction pour afficher la liste des arcs
void display_arcs(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES]) {
    printf("\nListe des arcs :\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjacency_matrix[i][j] > 0) {
                printf("- %s -> %s (Ponderation : %.2f)\n", species[i], species[j], adjacency_matrix[i][j]);
            }
        }
    }
}

// Fonction pour afficher les successeurs et predecesseurs d'une espece
void display_successors_predecessors(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES]) {
    char target[MAX_NAME_LENGTH];
    printf("\nEntrez le nom de l'espece a interroger : ");
    scanf("%s", target);

    int index = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(species[i], target) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Espece non trouvee.\n");
        return;
    }

    printf("Predecesseurs (manges par %s) :\n", target);
    for (int j = 0; j < n; j++) {
        if (adjacency_matrix[index][j] > 0) {
            printf("- %s (Ponderation : %.2f)\n", species[j], adjacency_matrix[index][j]);
        }
    }

    printf("Successeurs (qui mangent %s) :\n", target);
    for (int i = 0; i < n; i++) {
        if (adjacency_matrix[i][index] > 0) {
            printf("- %s (Ponderation : %.2f)\n", species[i], adjacency_matrix[i][index]);
        }
    }
}
