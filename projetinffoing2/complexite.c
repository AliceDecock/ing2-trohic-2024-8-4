//
// Created by meili on 06/12/2024.
//

#include <stdio.h>
#include <math.h> // Include math.h for fmax
#include "complexite.h"
#include "network.h"

// DFS utilisé pour calculer la hauteur trophique
int dfs_niveau(int current, float matrice_adjacence[][MAX_ESPECE], int visite[], int n, int hauteur) {
    visite[current] = 1;
    int max_hauteur = hauteur;

    for (int i = 0; i < n; i++) {
        if (matrice_adjacence[current][i] > 0 && !visite[i]) {
            max_hauteur = fmax(max_hauteur, dfs_niveau(i, matrice_adjacence, visite, n, hauteur + 1));
        }
    }

    visite[current] = 0;
    return max_hauteur;
}

// Fonction pour calculer la hauteur trophique maximale
int calculer_hauteur_trophique(int n, float matrice_adjacence[][MAX_ESPECE]) {
    int max_hauteur = 0;

    for (int i = 0; i < n; i++) {
        int visite[MAX_ESPECE] = {0};
        max_hauteur = fmax(max_hauteur, dfs_niveau(i, matrice_adjacence, visite, n, 0));
    }

    return max_hauteur;
}

// Fonction pour calculer la densité de liaison
float calculer_densite_liaison(int n, float matrice_adjacence[][MAX_ESPECE]) {
    int liens = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrice_adjacence[i][j] > 0) {
                liens++;
            }
        }
    }

    return (float)liens / (n * n);
}

void calculer_distribution_degres(int n, float matrice_adjacence[][MAX_ESPECE], int degre_entree[], int degre_sortie[]) {
    for (int i = 0; i < n; i++) {
        degre_entree[i] = 0;
        degre_sortie[i] = 0;

        for (int j = 0; j < n; j++) {
            if (matrice_adjacence[j][i] > 0) {
                degre_entree[i]++;
            }
            if (matrice_adjacence[i][j] > 0) {
                degre_sortie[i]++;
            }
        }
    }
}

// Fonction pour calculer et afficher la distribution des degrés
void calculer_distribution_degres_reseau(int n, float matrice_adjacence[][MAX_ESPECE], int degre_entree[], int degre_sortie[]) {
    // Calcul des degrés d'entrée et de sortie
    calculer_distribution_degres(n, matrice_adjacence, degre_entree, degre_sortie);

    // Déterminer le degré maximal
    int max_degree = 0;
    for (int i = 0; i < n; i++) {
        int total_degree = degre_entree[i] + degre_sortie[i];
        if (total_degree > max_degree) {
            max_degree = total_degree;
        }
    }

    // Initialiser les histogrammes
    int distribution_entree[max_degree + 1];
    int distribution_sortie[max_degree + 1];
    int distribution_totale[max_degree + 1];
    for (int i = 0; i <= max_degree; i++) {
        distribution_entree[i] = 0;
        distribution_sortie[i] = 0;
        distribution_totale[i] = 0;
    }

    // Remplir les histogrammes
    for (int i = 0; i < n; i++) {
        distribution_entree[degre_entree[i]]++;
        distribution_sortie[degre_sortie[i]]++;
        distribution_totale[degre_entree[i] + degre_sortie[i]]++;
    }

    // Afficher la distribution des degrés
    printf("\n\033[32m=== Distribution des Degres ===\033[0m\n");

    printf("Distribution des degres d'entree :\n");
    for (int i = 0; i <= max_degree; i++) {
        if (distribution_entree[i] > 0) {
            printf("- Degre %d : %d noeuds\n", i, distribution_entree[i]);
        }
    }

    printf("\nDistribution des degres de sortie :\n");
    for (int i = 0; i <= max_degree; i++) {
        if (distribution_sortie[i] > 0) {
            printf("- Degre %d : %d noeuds\n", i, distribution_sortie[i]);
        }
    }

    printf("\nDistribution des degres totaux :\n");
    for (int i = 0; i <= max_degree; i++) {
        if (distribution_totale[i] > 0) {
            printf("- Degre %d : %d noeuds\n", i, distribution_totale[i]);
        }
    }
}

// Analyse complète de la complexité du réseau
void analyser_complexite_reseau(int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE]) {
    printf("\033[31m=== Analyse de la Complexite du Reseau ===\033[0m\n");

    // Calculer la hauteur trophique
    int hauteur_trophique = calculer_hauteur_trophique(n, matrice_adjacence);
    printf("Hauteur trophique maximale : %d\n", hauteur_trophique);

    // Calculer la densité de liaison
    float densite = calculer_densite_liaison(n, matrice_adjacence);
    printf("Densite de liaison : %.3f\n", densite);

    // Calculer et afficher la distribution des degrés
    int degre_entree[MAX_ESPECE], degre_sortie[MAX_ESPECE];
    calculer_distribution_degres_reseau(n, matrice_adjacence, degre_entree, degre_sortie);
}
