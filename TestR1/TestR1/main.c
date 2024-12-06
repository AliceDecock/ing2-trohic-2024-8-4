#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "connexite.h"
#include "centralite.h"
#include "dynamique.h"
#include "dotgraphe.h"

#ifdef _WIN32
#include <windows.h>
#endif



// Fonction pour afficher le menu stylé avec des numéros en couleur
void display_menu() {
    printf("\033[31m=== Menu ===\033[0m\n");
    printf("\033[32m1\033[0m. Afficher la liste des especes\n");
    printf("\033[32m2\033[0m. Afficher la liste des arcs\n");
    printf("\033[32m3\033[0m. Afficher les successeurs et predecesseurs des especes\n");
    printf("\033[32m4\033[0m. Verifier la connexite\n");
    printf("\033[32m5\033[0m. Rechercher des sommets particuliers\n");
    printf("\033[32m6\033[0m. Etude des niveaux trophiques et des chaines alimentaires\n");
    printf("\033[32m7\033[0m. Calculer la centralite des especes\n");
    printf("\033[32m8\033[0m. Simuler la disparition d'une espece\n");
    printf("\033[32m9\033[0m. Restaurer l'espece supprimee\n");
    printf("\033[32m10\033[0m. Simulation de la dynamique des populations\n");
    printf("\033[32m11\033[0m. Quitter\n");
}

int main() {
    int n; // Nombre d'espèces dans le réseau
    char especes[MAX_ESPECE][MAX_NAME_LENGTH]; // Noms des espèces
    const char *output_dot_file = "reseau_trophique.dot"; // Fichier de sortie DOT
    float matrice_adjacence[MAX_ESPECE][MAX_ESPECE]; // Matrice d'adjacence du réseau
    float populations[MAX_ESPECE]; // Populations initiales des espèces
    float growth_rates[MAX_ESPECE]; // Taux de croissance des populations
    float carrying_capacities[MAX_ESPECE]; // Capacités de portage des espèces

    // Charger un fichier réseau
    char filename[100];
    printf("Veuillez saisir le nom du fichier reseau : ");
    scanf("%s", filename);

    // Lecture du réseau depuis le fichier
    printf("Lecture du fichier %s...\n", filename);
    read_network(filename, &n, especes, matrice_adjacence, populations, growth_rates, carrying_capacities);

    // Affichage des espèces lues
    //printf("Nombre d'especes : %d\n", n);
    //for (int i = 0; i < n; i++) {
    //    printf("Espece lue : %s\n", especes[i]);
    //}
    //printf("Lecture du fichier terminee avec succes.\n");

    // Génération du fichier DOT
    printf("Generation automatique du fichier DOT...\n");
    generate_dot_file(filename, output_dot_file);
    printf("Fichier DOT genere avec succes : %s\n", output_dot_file);

    int choice;
    do {
        display_menu(); // Affichage du menu
        printf("Veuillez choisir une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Option 1 choisie : Afficher la liste des especes.\n");
                printf("Liste des especes :\n");
                for (int i = 0; i < n; i++) {
                    printf("- %s\n", especes[i]);
                }
                break;
            case 2:
                printf("Option 2 choisie : Afficher la liste des arcs.\n");
                display_arcs(n, especes, matrice_adjacence);
                break;
            case 3:
                printf("Option 3 choisie : Afficher les successeurs et predecesseurs des especes.\n");
                display_successors_predecessors(n, especes, matrice_adjacence);
                break;
            case 4:
                printf("Option 4 choisie : Vérification de la connexité.\n");
                Reseau reseau = {
                        .nb_especes = n,
                        .nb_relations = 0
                };
                memcpy(reseau.especes, especes, sizeof(char) * n * MAX_NAME_LENGTH);
                verifier_connexite(&reseau);
                break;

            case 5:
                printf("Option 5 choisie : Rechercher des sommets particuliers.\n");
                find_special_vertices(n, especes, matrice_adjacence);
                break;

            case 6: {
                printf("Option 6 choisie : Etude des niveaux trophiques et des chaines alimentaires.\n");
                char target_species[MAX_NAME_LENGTH];
                printf("Entrez le nom de l'espèce à étudier : ");
                scanf("%s", target_species);
                analyze_trophic_levels(n, especes, matrice_adjacence, target_species);
                break;
            }

            case 7: {
                printf("Option 7 choisie : Calculer la centralite des especes.\n");
                int in_degree[MAX_ESPECE], out_degree[MAX_ESPECE];
                float centrality[MAX_ESPECE];

                compute_degrees(n, matrice_adjacence, in_degree, out_degree);
                compute_betweenness_centrality(n, matrice_adjacence, centrality);

                printf("\nCentralite des especes :\n");
                for (int i = 0; i < n; i++) {
                    printf("%s : demi-degre interieur = %d, demi-degre exterieur = %d, centralite = %.2f\n",
                           especes[i], in_degree[i], out_degree[i], centrality[i]);
                }
                break;
            }
            case 8: {
                printf("Option 8 choisie : Simuler la disparition d'une espece.\n");
                char target_species[MAX_NAME_LENGTH];
                printf("Entrez le nom de l'espece a supprimer : ");
                scanf("%s", target_species);
                simulate_species_removal(&n, especes, matrice_adjacence, target_species);
                break;
            }
            case 9:
                printf("Option 9 choisie : Restaurer l'espece supprimee.\n");
                restore_species(&n, especes, matrice_adjacence);
                break;
            case 10: {
                printf("Option 10 choisie : Simulation de la dynamique des populations.\n");
                int iterations;
                printf("Entrez le nombre d'iterations pour la simulation : ");
                scanf("%d", &iterations);
                simulate_population_dynamics(n, especes, matrice_adjacence, growth_rates, carrying_capacities, populations, iterations);
                break;
            }
            case 11:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir une option valide.\n");
        }

    } while (choice != 11);

    return 0;
}