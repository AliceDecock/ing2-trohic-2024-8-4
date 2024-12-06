#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For memcpy
#include "network.h"
#include "connexite.h"
#include "centralite.h"
#include "dynamique.h"
#include "dotgraphe.h"
#include "complexite.h"

void afficher_menu() {
    printf("\033[31m=== Menu ===\033[0m\n");
    printf("\033[32m1\033[0m. Afficher la liste des especes\n");
    printf("\033[32m2\033[0m. Afficher la liste des arcs\n");
    printf("\033[32m3\033[0m. Afficher les successeurs et predecesseurs des especes\n");
    printf("\033[32m4\033[0m. Analyser la complexite du reseau\n");
    printf("\033[32m5\033[0m. Verifier la connexite\n");
    printf("\033[32m6\033[0m. Rechercher des sommets particuliers\n");
    printf("\033[32m7\033[0m. Etude des niveaux trophiques et des chaines alimentaires\n");
    printf("\033[32m8\033[0m. Calculer la centralite_int des especes\n");
    printf("\033[32m9\033[0m. Simuler la disparition d'une espece\n");
    printf("\033[32m10\033[0m. Restaurer l'espece supprimee\n");
    printf("\033[32m11\033[0m. Simulation de la dynamique des populations\n");
    printf("\033[32m12\033[0m. Quitter\n");
}

int main() {
    int n; // Number of especes in the network
    char especes[MAX_ESPECE][MAX_NAME_LENGTH]; // Species names
    const char *output_dot_file = "reseau_trophique.dot"; // DOT file for visualization
    float matrice_adjacence[MAX_ESPECE][MAX_ESPECE]; // Network adjacency matrix
    float populations[MAX_ESPECE]; // Initial especes populations
    float croissance[MAX_ESPECE]; // Growth rates for populations
    float portage[MAX_ESPECE]; // Carrying capacities for populations
    float anthropique[MAX_ESPECE] = {0.0}; // Anthropogenic impacts initialized to zero

    // Load network file
    char nomfichier[100];
    printf("\033[36mVeuillez saisir le nom du fichier reseau : \033[0m");
    scanf("%s", nomfichier);

    // Read the network
    printf("\033[36mLecture du fichier %s...\n\033[0m", nomfichier);
    reseau(nomfichier, &n, especes, matrice_adjacence, populations, croissance, portage);

    printf("\033[32mNombre d'especes : %d\n\033[0m", n);

    // Generate DOT file
    printf("Generation automatique du fichier DOT...\n");
    generer_dot(nomfichier, output_dot_file);

    int choix;
    do {
        afficher_menu();
        printf("\033[36mVeuillez choisir une option : \033[0m");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\033[32mOption 1 choisie : Afficher la liste des especes.\n\033[0m");
                afficher_especes(n, especes);
                break;

            case 2:
                printf("\033[32mOption 2 choisie : Afficher la liste des arcs.\n\033[0m");
                afficher_arcs(n, especes, matrice_adjacence);
                break;

            case 3:
                printf("\033[32mOption 3 choisie : Afficher les successeurs et predecesseurs des especes.\n\033[0m");
                successeurs_predecesseurs(n, especes, matrice_adjacence);
                break;
            case 4:
                printf("\033[32mOption 4 choisie : Analyse de la complexite du reseau.\n\033[0m");
                analyser_complexite_reseau(n, especes, matrice_adjacence);
                break;

            case 5:
                printf("Option 5 choisie : Vérification de la connexité.\n");
                Reseau reseau = {
                        .nb_especes = n,
                        .nb_relations = 0 // Initialize relations to 0 for testing
                };
                memcpy(reseau.especes, especes, sizeof(char) * n * MAX_NAME_LENGTH);
                verifier_connexite(&reseau);
                break;

            case 6:
                printf("\033[32mOption 6 choisie : Rechercher des sommets particuliers.\n\033[0m");
                sommets_particuliers(n, especes, matrice_adjacence);
                break;

            case 7: {
                printf("\033[32mOption 7 choisie : Etude des niveaux trophiques et des chaines alimentaires.\n\033[0m");
                char espece_ciblee[MAX_NAME_LENGTH];
                printf("\033[36mEntrez le nom de l'espece a etudier : \033[0m");
                scanf("%s", espece_ciblee);
                niveaux_trophiques(n, especes, matrice_adjacence, espece_ciblee);
                break;
            }

            case 8: {
                printf("\033[32mOption 8 choisie : Calculer la centralite des especes.\n\033[0m");
                int degre_int[MAX_ESPECE], degre_ext[MAX_ESPECE];
                float centralite[MAX_ESPECE];

                calculerdegres(n, matrice_adjacence, degre_int, degre_ext);
                centralite_int(n, matrice_adjacence, centralite);

                printf("\033[32m\nCentralite des especes :\n\033[0m");
                for (int i = 0; i < n; i++) {
                    printf("%s : Demi-degre interieur = %d, Demi-degre exterieur = %d, Centralite = %.2f\n",
                           especes[i], degre_int[i], degre_ext[i], centralite[i]);
                }
                break;
            }

            case 9: {
                printf("\033[32mOption 9 choisie : Simuler la disparition d'une espece.\n\033[0m");
                char espece_ciblee[MAX_NAME_LENGTH];
                printf("\033[36mEntrez le nom de l'espece a supprimer : \033[0m");
                scanf("%s", espece_ciblee);
                suppression_espece(&n, especes, matrice_adjacence, espece_ciblee);
                break;
            }

            case 10:
                printf("\033[32mOption 10 choisie : Restaurer l'espece supprimee.\n\033[0m");
                restorer_espece(&n, especes, matrice_adjacence);
                break;

            case 11:
                printf("\033[32mOption 11 choisie : Simulation de la dynamique des populations.\n\033[0m");
                menudynamique(n, especes, populations, croissance, portage, anthropique, matrice_adjacence);
                break;

            case 12:
                printf("\033[31mAu revoir !\n\033[0m");
                break;

            default:
                printf("\033[31mOption invalide. Veuillez choisir une option valide.\n\033[0m");
        }
    } while (choix != 11);

    return 0;
}