
//
// Created by alice on 27/11/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"

void reseau(const char *nomfichier, int *n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE], float populations[], float croissance[], float portage[]) {
    FILE *fichier = fopen(nomfichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    fscanf(fichier, "%d", n); // Lire le nombre d'especes

    // Lire les noms des especes
    for (int i = 0; i < *n; i++) {
        if (fscanf(fichier, "%s", especes[i]) != 1) {
            fprintf(stderr, "Erreur lors de la lecture du nom de l'espece %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    // Lire la matrice d'adjacence
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            if (fscanf(fichier, "%f", &matrice_adjacence[i][j]) != 1) {
                fprintf(stderr, "Erreur lors de la lecture de la matrice d'adjacence (%d, %d)\n", i, j);
                exit(EXIT_FAILURE);
            }
        }
    }

    // Initialiser les paramètres des populations
    for (int i = 0; i < *n; i++) {
        populations[i] = 10.0;           // Population initiale par défaut
        croissance[i] = 0.1;          // Rythme de croissance par défaut
        portage[i] = 100.0; // Capacité de portage par défaut
    }
    // Lire les populations initiales
    for (int i = 0; i < *n; i++) {
        fscanf(fichier, "%f", &populations[i]);
    }

    // Lire les taux de croissance
    for (int i = 0; i < *n; i++) {
        fscanf(fichier, "%f", &croissance[i]);
    }

    // Lire les capacités de portage
    for (int i = 0; i < *n; i++) {
        fscanf(fichier, "%f", &portage[i]);
    }

    fclose(fichier);
    printf("Lecture du fichier terminee avec succes.\n");
}

// Fonction pour afficher la liste des especes
void afficher_especes(int n, char especes[][MAX_NAME_LENGTH]) {
    printf("Liste des especes :\n");
    for (int i = 0; i < n; i++) {
        printf("- %s\n", especes[i]);
    }
}

// Fonction pour afficher la liste des arcs
void afficher_arcs(int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE]) {
    printf("\nListe des arcs :\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrice_adjacence[i][j] > 0) {
                printf("- %s -> %s (Ponderation : %.2f)\n", especes[i], especes[j], matrice_adjacence[i][j]);
            }
        }
    }
}

// Fonction pour afficher les successeurs et predecesseurs d'une espece
void
successeurs_predecesseurs(int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE]) {
    char cible[MAX_NAME_LENGTH];
    printf("\nEntrez le nom de l'espece a interroger : ");
    scanf("%s", cible);

    int index = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(especes[i], cible) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Espece non trouvee.\n");
        return;
    }

    printf("Predecesseurs (manges par %s) :\n", cible);
    for (int j = 0; j < n; j++) {
        if (matrice_adjacence[index][j] > 0) {
            printf("- %s (Ponderation : %.2f)\n", especes[j], matrice_adjacence[index][j]);
        }
    }

    printf("Successeurs (qui mangent %s) :\n", cible);
    for (int i = 0; i < n; i++) {
        if (matrice_adjacence[i][index] > 0) {
            printf("- %s (Ponderation : %.2f)\n", especes[i], matrice_adjacence[i][index]);
        }
    }
}
