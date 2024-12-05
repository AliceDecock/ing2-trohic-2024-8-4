#ifndef CONNEXITE_H
#define CONNEXITE_H

#include <stdbool.h>
#include "network.h"

// Vérifie si le réseau est connexe (graphe non-orienté)
bool is_connected(int n, float adjacency_matrix[][MAX_ESPECE]);

// Vérifie si le réseau est fortement connexe (graphe orienté)
bool is_strongly_connected(int n, float adjacency_matrix[][MAX_ESPECE]);

// Analyse complète de la connexité du réseau
void analyze_connectivity(int n, float adjacency_matrix[][MAX_ESPECE]);

// Trouve et affiche les composantes connexes du réseau
void find_connected_components(int n, float adjacency_matrix[][MAX_ESPECE]);

// Recherche et affiche les sommets sans prédécesseurs ou successeurs
void find_special_vertices(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE]);
void analyze_trophic_levels(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE], const char *target_species);


#endif // CONNEXITE_H