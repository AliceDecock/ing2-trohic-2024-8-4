
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
    printf("\n=== VERIFICATION DE LA CONNEXITE ===\n");

    if (r->nb_especes == 0) {
        printf("Le reseau est vide.\n");
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
        printf("\nLe reseau est entierement connexe. Toutes les especes sont connectées.\n");
    } else {
        printf("\nLe reseau est entierement connexe. Il contient %d composantes connexes distinctes.\n", composantes);
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
            printf("- %s n'a pas de predecesseurs.\n", especes[i]);
        }
    }
}

// Analyse des niveaux trophiques pour une espèce donnée
void niveaux_trophiques(int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE], const char *espece_ciblee) {
    printf("\n=== Analyse des Niveaux Trophiques ===\n");
    printf("Espece cible : %s\n", espece_ciblee);

    // Trouver l'indice de l'espèce cible
    int target_index = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(especes[i], espece_ciblee) == 0) {
            target_index = i;
            break;
        }
    }

    if (target_index == -1) {
        printf("Espece non trouvee : %s\n", espece_ciblee);
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

    printf("Analyse des niveaux trophiques terminee pour %s.\n", espece_ciblee);
}


// Fonction récursive pour explorer les chaînes alimentaires
static void dfs_chain(int current, int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE], int *path, int *path_length) {
    path[(*path_length)++] = current;

    bool has_successor = false;
    for (int i = 0; i < n; i++) {
        if (adjacency_matrix[current][i] > 0) {
            has_successor = true;
            dfs_chain(i, n, species, adjacency_matrix, path, path_length);
        }
    }

    if (!has_successor) {
        // Afficher la chaîne alimentaire complète
        for (int i = 0; i < *path_length; i++) {
            printf("%s", species[path[i]]);
            if (i < *path_length - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    }

    // Retirer le nœud actuel du chemin
    (*path_length)--;
}

// Recherche des chaînes alimentaires à partir d'une espèce donnée
void find_food_chains(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE], const char *start_species) {
    printf("\n=== Recherche des chaines alimentaires ===\n");
    printf("Espece de depart : %s\n", start_species);

    // Trouver l'indice de l'espèce de départ
    int start_index = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(species[i], start_species) == 0) {
            start_index = i;
            break;
        }
    }

    if (start_index == -1) {
        printf("Espece non trouvee : %s\n", start_species);
        return;
    }

    // Tableau pour stocker le chemin actuel
    int path[MAX_ESPECE];
    int path_length = 0;

    // Appeler la fonction DFS depuis l'espèce de départ
    dfs_chain(start_index, n, species, adjacency_matrix, path, &path_length);
}


