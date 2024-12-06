
#ifndef DYNAMIQUE_H
#define DYNAMIQUE_H

#include "network.h"

// Functions for dynamic population management
void demarrersimulation(int n, char especes[][MAX_NAME_LENGTH], float populations[], float croissance[], float portage[], float antrophique[], float matrice_adjacence[][MAX_ESPECE], int iterations);
void pause_simulation();
void parametresespece(int n, char especes[][MAX_NAME_LENGTH], float croissance[], float portage[]);
void parametresantrophique(int n, char especes[][MAX_NAME_LENGTH], float antrophique[]);
void afficher_etat(int n, char especes[][MAX_NAME_LENGTH], float populations[]);
void sauv_etat(const char *nomfichier, int n, char especes[][MAX_NAME_LENGTH], float populations[], float croissance[], float portage[]);
void menudynamique(int n, char especes[][MAX_NAME_LENGTH], float populations[], float croissance[], float portage[], float antrophique[], float matrice_adjacence[][MAX_ESPECE]);

#endif // DYNAMIQUE_H
