#ifndef CONNEXITE_H
#define CONNEXITE_H

#include <stdbool.h>
#include "network.h"

typedef struct {
    char espece[MAX_NAME_LENGTH];
    char source[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
    int nb_especes;
    int nb_relations;
} Relation;

// Structure pour le réseau trophique
typedef struct {
    int nb_especes;
    int nb_relations;
    char especes[MAX_ESPECE][MAX_NAME_LENGTH];
    Relation relations[MAX_ESPECE * MAX_ESPECE];
} Reseau;

// Prototypes
void dfs(Reseau *r, int espece_index, int *visite);
void verifier_connexite(Reseau *r);
void find_special_vertices(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE]);
void analyze_trophic_levels(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE], const char *target_species);

#endif // CONNEXITE_H