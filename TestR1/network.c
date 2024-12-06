//
// Created by alice on 27/11/2024.
//

#include "network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_network(const char *filename, int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE], float populations[], float growth_rates[], float carrying_capacities[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Read the number of species
    if (fscanf(file, "%d", n) != 1) {
        fprintf(stderr, "Erreur : impossible de lire le nombre d'especes.\n");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    printf("Nombre d'especes : %d\n", *n);

    // Read species names
    for (int i = 0; i < *n; i++) {
        if (fscanf(file, "%s", species[i]) != 1) {
            fprintf(stderr, "Erreur : impossible de lire le nom de l'espece %d.\n", i);
            fclose(file);
            exit(EXIT_FAILURE);
        }
        printf("Espece lue : %s\n", species[i]);
    }

    // Read adjacency matrix
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(file, "%f", &adjacency_matrix[i][j]) != 1) {
                fprintf(stderr, "Erreur : impossible de lire la matrice d'adjacence (%d, %d).\n", i, j);
                fclose(file);
                exit(EXIT_FAILURE);
            }
        }
    }

    // Read or initialize populations
    printf("Lecture des populations initiales...\n");
    for (int i = 0; i < *n; i++) {
        if (fscanf(file, "%f", &populations[i]) != 1) {
            populations[i] = 10.0; // Default value if missing
        }
        printf(" - %s : Population = %.2f\n", species[i], populations[i]);
    }

    // Read or initialize growth rates
    printf("Lecture des taux de croissance...\n");
    for (int i = 0; i < *n; i++) {
        if (fscanf(file, "%f", &growth_rates[i]) != 1) {
            growth_rates[i] = 0.1; // Default value if missing
        }
        printf(" - %s : Taux de croissance = %.2f\n", species[i], growth_rates[i]);
    }

    // Read or initialize carrying capacities
    printf("Lecture des capacites de portage...\n");
    for (int i = 0; i < *n; i++) {
        if (fscanf(file, "%f", &carrying_capacities[i]) != 1) {
            carrying_capacities[i] = 100.0; // Default value if missing
        }
        printf(" - %s : Capacite de portage = %.2f\n", species[i], carrying_capacities[i]);
    }

    fclose(file);
    printf("Lecture du fichier terminee avec succes.\n");
}



// Fonction pour afficher la liste des especes
void display_species(int n, char species[][MAX_NAME_LENGTH]) {
    printf("Liste des especes :\n");
    for (int i = 0; i < n; i++) {
        printf("- %s\n", species[i]);
    }
}

// Fonction pour afficher la liste des arcs
void display_arcs(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE]) {
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
void
display_successors_predecessors(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE]) {
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