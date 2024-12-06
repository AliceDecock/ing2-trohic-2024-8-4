
//
// Created by meili on 03/12/2024.
//

#ifndef CENTRALITE_H
#define CENTRALITE_H

void calculerdegres(int n, float matrice_adjacence[][MAX_ESPECE], int degre_int[], int degre_ext[]);
void centralite_int(int n, float matrice_adjacence[][MAX_ESPECE], float centralite[]);
void suppression_espece(int *n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE], const char *espece_ciblee);
void restorer_espece(int *n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE]);
#endif
