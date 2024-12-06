#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "network.h"
#include "centralite.h"
#include "dotgraphe.h"

// Stock temporaire pour une espèce supprimée
typedef struct {
    char nom[MAX_NAME_LENGTH];
    float adjacency_row[MAX_ESPECE];
    float adjacency_col[MAX_ESPECE];
    int valide; // Indique si une espèce supprimée est stockée
} RemovedSpecies;

RemovedSpecies removed_species = { .nom = "", .valide = 0 };

// Fonction pour écrire l'état actuel du réseau dans un fichier texte
void reseau_en_fichier(const char *nomfichier, int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE]) {
    FILE *file = fopen(nomfichier, "w");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier pour écriture");
        exit(EXIT_FAILURE);
    }

    // Écrire le nombre d'espèces
    fprintf(file, "%d\n", n);

    // Écrire les noms des espèces
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s\n", especes[i]);
    }

    // Écrire la matrice d'adjacence
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%.2f ", matrice_adjacence[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Etat du reseau ecrit dans le fichier : %s\n", nomfichier);
}

// Fonction pour restaurer une espèce supprimée
void restorer_espece(int *n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE]) {
    if (!removed_species.valide) {
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
    strcpy(especes[restored_index], removed_species.nom);

    // Restaurer les lignes et colonnes de la matrice
    for (int i = 0; i < *n; i++) {
        matrice_adjacence[i][restored_index] = removed_species.adjacency_col[i];
        matrice_adjacence[restored_index][i] = removed_species.adjacency_row[i];
    }

    printf("Espece %s restauree avec succès.\n", removed_species.nom);

    // Réinitialiser le stockage temporaire
    removed_species.valide = 0;

    // Écrire le réseau actuel dans un fichier temporaire
    reseau_en_fichier("network_state.txt", *n, especes, matrice_adjacence);

    // Regénérer le fichier DOT
    generer_dot("network_state.txt", "reseau_trophique.dot");
    printf("Fichier DOT regenere apres restauration.\n");
}

// Fonction pour supprimer une espèce
void suppression_espece(int *n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE], const char *espece_ciblee) {
    int target_index = -1;

    // Trouver l'index de l'espèce cible
    for (int i = 0; i < *n; i++) {
        if (strcmp(especes[i], espece_ciblee) == 0) {
            target_index = i;
            break;
        }
    }

    if (target_index == -1) {
        printf("Espece non trouvee : %s\n", espece_ciblee);
        return;
    }

    if (removed_species.valide) {
        printf("Une espece supprimee existe déjà. Restaurez-la avant de supprimer une nouvelle espece.\n");
        return;
    }

    // Stocker l'espèce supprimée
    strcpy(removed_species.nom, especes[target_index]);
    for (int i = 0; i < *n; i++) {
        removed_species.adjacency_row[i] = matrice_adjacence[target_index][i];
        removed_species.adjacency_col[i] = matrice_adjacence[i][target_index];
    }
    removed_species.valide = 1;

    printf("\nSuppression de l'espece : %s\n", espece_ciblee);

    // Supprimer les connexions dans la matrice
    for (int i = 0; i < *n; i++) {
        matrice_adjacence[target_index][i] = 0;
        matrice_adjacence[i][target_index] = 0;
    }

    // Supprimer l'espèce de la liste
    for (int i = target_index; i < *n - 1; i++) {
        strcpy(especes[i], especes[i + 1]);
    }

    // Réorganiser la matrice d'adjacence pour décaler les lignes et colonnes
    for (int i = target_index; i < *n - 1; i++) {
        for (int j = 0; j < *n; j++) {
            matrice_adjacence[i][j] = matrice_adjacence[i + 1][j];
            matrice_adjacence[j][i] = matrice_adjacence[j][i + 1];
        }
    }

    (*n)--;

    printf("L'espece %s a ete supprimee du reseau.\n", espece_ciblee);

    // Écrire le réseau actuel dans un fichier temporaire
    reseau_en_fichier("network_state.txt", *n, especes, matrice_adjacence);

    // Regénérer le fichier DOT
    generer_dot("network_state.txt", "reseau_trophique.dot");
    printf("Fichier DOT regenere apres suppression.\n");
}

// Calcul des demi-degrés intérieur et extérieur
void calculerdegres(int n, float matrice_adjacence[][MAX_ESPECE], int degre_int[], int degre_ext[]) {
    for (int i = 0; i < n; i++) {
        degre_int[i] = 0;
        degre_ext[i] = 0;
        for (int j = 0; j < n; j++) {
            if (matrice_adjacence[j][i] > 0) {
                degre_int[i]++;
            }
            if (matrice_adjacence[i][j] > 0) {
                degre_ext[i]++;
            }
        }
    }
}

// Calcul de la centralité d'intermédiarité
void centralite_int(int n, float matrice_adjacence[][MAX_ESPECE], float centralite[]) {
    for (int i = 0; i < n; i++) {
        centralite[i] = 0.0;
    }

    for (int s = 0; s < n; s++) {
        int visited[MAX_ESPECE] = {0};
        int queue[MAX_ESPECE];
        int front = 0, rear = 0;

        queue[rear++] = s;

        while (front < rear) {
            int current = queue[front++];
            for (int i = 0; i < n; i++) {
                if (matrice_adjacence[current][i] > 0 && !visited[i]) {
                    centralite[i]++;
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
        }
    }
}
