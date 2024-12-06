
#ifndef NETWORK_H
#define NETWORK_H

#define MAX_ESPECE 100
#define MAX_SPECIES MAX_ESPECE  // Si les deux concepts sont identiques
#define MAX_NAME_LENGTH 50

// Déclarations des fonctions
void reseau(const char *nomfichier, int *n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE], float populations[], float croissance[], float portage[]);
void afficher_especes(int n, char especes[][MAX_NAME_LENGTH]);
void afficher_arcs(int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE]);
void successeurs_predecesseurs(int n, char especes[][MAX_NAME_LENGTH], float matrice_adjacence[][MAX_ESPECE]);

#endif
