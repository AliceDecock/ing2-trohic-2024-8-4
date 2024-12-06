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
void sommets_particuliers(int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE]);
void niveaux_trophiques(int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE], const char *espece_ciblee);

#endif // CONNEXITE_H