
//
// Created by meili on 06/12/2024.
//

#ifndef COMPLEXITE_H
#define COMPLEXITE_H

#include "network.h"

// Déclarations des fonctions
int calculer_hauteur_trophique(int n, float matrice_adjacence[][MAX_ESPECE]);
float calculer_densite_liaison(int n, float matrice_adjacence[][MAX_ESPECE]);
void calculer_distribution_degres(int n, float matrice_adjacence[][MAX_ESPECE], int degre_entree[], int degre_sortie[]);
void analyser_complexite_reseau(int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE]);
void calculer_distribution_degres_reseau(int n, float matrice_adjacence[][MAX_ESPECE], int degre_entree[], int degre_sortie[]);

#endif // COMPLEXITE_H

