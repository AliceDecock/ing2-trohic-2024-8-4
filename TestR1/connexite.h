#ifndef CONNEXITE_H
#define CONNEXITE_H

#include <stdio.h>
#include <string.h>

#define MAX_ESPECE 100
#define MAX_NAME_LENGTH 50

// Déclarations des fonctions principales

// Vérifie si le réseau est connexe
int is_connected(int n, float adjacency_matrix[][MAX_ESPECE]);

// Vérifie si le réseau est fortement connexe
int is_strongly_connected(int n, float adjacency_matrix[][MAX_ESPECE]);

// Identifie et affiche les composantes connexes
void find_connected_components(int n, float adjacency_matrix[][MAX_ESPECE]);

// Analyse complète de la connexité
void analyze_connectivity(int n, float adjacency_matrix[][MAX_ESPECE]);

// Recherche des sommets particuliers
void find_special_vertices(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE]);

// Analyse des niveaux trophiques et affichage des ascendants
void analyze_trophic_levels(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_ESPECE], const char *target_species);

#endif // CONNEXITE_H