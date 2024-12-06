#include "connexite.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour trouver l'indice d'une espèce dans le réseau
int trouver_espece(Reseau *r, const char *espece) {
    for (int i = 0; i < r->nb_especes; i++) {
        if (strcmp(r->especes[i], espece) == 0) {
            return i;
        }
    }
    return -1;
}

// DFS récursif
void dfs(Reseau *r, int espece_index, int *visite) {
    visite[espece_index] = 1;

    for (int i = 0; i < r->nb_relations; i++) {
        if (strcmp(r->especes[espece_index], r->relations[i].source) == 0) {
            int dest_index = trouver_espece(r, r->relations[i].destination);
            if (dest_index != -1 && !visite[dest_index]) {
                dfs(r, dest_index, visite);
            }
        } else if (strcmp(r->especes[espece_index], r->relations[i].destination) == 0) {
            int src_index = trouver_espece(r, r->relations[i].source);
            if (src_index != -1 && !visite[src_index]) {
                dfs(r, src_index, visite);
            }
        }
    }
}

// Vérification et affichage des composantes connexes
void verifier_connexite(Reseau *r) {
    printf("\n=== VÉRIFICATION DE LA CONNEXITÉ ===\n");

    if (r->nb_especes == 0) {
        printf("Le réseau est vide.\n");
        return;
    }

    int *visite = (int *)calloc(r->nb_especes, sizeof(int));
    int composantes = 0;

    printf("\n--- Composantes connexes ---\n");
    for (int i = 0; i < r->nb_especes; i++) {
        if (!visite[i]) {
            composantes++;
            printf("Composante %d : ", composantes);

            // Parcourir et afficher toutes les espèces de cette composante
            dfs(r, i, visite);

            for (int j = 0; j < r->nb_especes; j++) {
                if (visite[j]) {
                    printf("%s ", r->especes[j]);
                    visite[j] = -1; // Marquer comme déjà affiché pour cette composante
                }
            }
            printf("\n");
        }
    }

    // Vérification si le réseau entier est connexe
    if (composantes == 1) {
        printf("\nLe réseau est entièrement connexe. Toutes les espèces sont connectées.\n");
    } else {
        printf("\nLe réseau n'est pas entièrement connexe. Il contient %d composantes connexes distinctes.\n", composantes);
    }

    free(visite);
}

// Recherche des sommets sans prédécesseurs ou successeurs
void sommets_particuliers(int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE]) {
    printf("\n=== Sommets Particuliers ===\n");
    for (int i = 0; i < n; i++) {
        bool has_successors = false, has_predecessors = false;

        // Vérifie les successeurs
        for (int j = 0; j < n; j++) {
            if (matrice_adjacence[i][j] > 0) {
                has_successors = true;
                break;
            }
        }

        // Vérifie les prédécesseurs
        for (int j = 0; j < n; j++) {
            if (matrice_adjacence[j][i] > 0) {
                has_predecessors = true;
                break;
            }
        }

        if (!has_successors) {
            printf("- %s n'a pas de successeurs.\n", especes[i]);
        }

        if (!has_predecessors) {
            printf("- %s n'a pas de prédécesseurs.\n", especes[i]);
        }
    }
}

// Analyse des niveaux trophiques pour une espèce donnée
void niveaux_trophiques(int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE], const char *espece_ciblee) {
    printf("\n=== Analyse des Niveaux Trophiques ===\n");
    printf("Espèce cible : %s\n", espece_ciblee);

    // Trouver l'indice de l'espèce cible
    int target_index = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(especes[i], espece_ciblee) == 0) {
            target_index = i;
            break;
        }
    }

    if (target_index == -1) {
        printf("Espèce non trouvée : %s\n", espece_ciblee);
        return;
    }

    // Afficher les ascendants directs
    printf("Ascendants directs de %s :\n", espece_ciblee);
    for (int i = 0; i < n; i++) {
        if (matrice_adjacence[i][target_index] > 0) {
            printf("- %s (poids : %.2f)\n", especes[i], matrice_adjacence[i][target_index]);
        }
    }

    // Afficher les descendants directs
    printf("Descendants directs de %s :\n", espece_ciblee);
    for (int i = 0; i < n; i++) {
        if (matrice_adjacence[target_index][i] > 0) {
            printf("- %s (poids : %.2f)\n", especes[i], matrice_adjacence[target_index][i]);
        }
    }

    printf("Analyse des niveaux trophiques terminée pour %s.\n", espece_ciblee);
}