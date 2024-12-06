#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "connexite.h"
#include "centralite.h"
#include "dynamique.h"
#include "dotgraphe.h"


// Function to display the styled menu with colored numbers
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
    int n; // Number of species in the network
    char species[MAX_ESPECE][MAX_NAME_LENGTH]; // Species names
    const char *output_dot_file = "reseau_trophique.dot"; // Fichier de sortie DOT
    float adjacency_matrix[MAX_ESPECE][MAX_ESPECE]; // Network adjacency matrix
    float populations[MAX_ESPECE]; // Initial species populations
    float growth_rates[MAX_ESPECE]; // Growth rates for populations
    float carrying_capacities[MAX_ESPECE]; // Carrying capacities for populations
    float anthropic_impact[MAX_ESPECE] = {0.0}; // Anthropogenic impacts initialized to zero

    // Charger un fichier reseau
    char filename[100];
    printf("\033[36mVeuillez saisir le nom du fichier reseau : \033[0m");
    scanf("%s", filename);

    // Lecture du réseau depuis le fichier
    printf("\033[36mLecture du fichier %s...\n\033[0m", filename);
    read_network(filename, &n, species, adjacency_matrix, populations, growth_rates, carrying_capacities);

    // Affichage des espèces lues
    printf("\033[32mNombre d'especes : %d\n\033[0m", n);
    for (int i = 0; i < n; i++) {
        //printf("\033[32mEspece lue : %s\n\033[0m", species[i]);
    }
    printf("\033[36mLecture du fichier terminee avec succes.\n\033[0m");


    // Génération du fichier DOT
    printf("Generation automatique du fichier DOT...\n");
    generate_dot_file(filename, output_dot_file);
    //printf("Fichier DOT genere avec succes : %s\n", output_dot_file);


    int choice;
    do {
        display_menu(); // Display the menu
        printf("\033[36mVeuillez choisir une option : \033[0m");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\033[32mOption 1 choisie : Afficher la liste des especes.\n\033[0m");
                display_species(n, species);
                break;
            case 2:
                printf("\033[32mOption 2 choisie : Afficher la liste des arcs.\n\033[0m");
                display_arcs(n, species, adjacency_matrix);
                break;
            case 3:
                printf("\033[32mOption 3 choisie : Afficher les successeurs et predecesseurs des especes.\n\033[0m");
                display_successors_predecessors(n, species, adjacency_matrix);
                break;
            case 4:
                printf("\033[32mOption 4 choisie : Verifier la connexite.\n\033[0m");
                analyze_connectivity(n, adjacency_matrix);
                break;
            case 5:
                printf("\033[32mOption 5 choisie : Rechercher des sommets particuliers.\n\033[0m");
                find_special_vertices(n, species, adjacency_matrix);
                break;
            case 6: {
                printf("\033[32mOption 6 choisie : Etude des niveaux trophiques et des chaines alimentaires.\n\033[0m");
                char target_species[MAX_NAME_LENGTH];
                printf("\033[36mEntrez le nom de l'espece a etudier : \033[0m");
                scanf("%s", target_species);
                analyze_trophic_levels(n, species, adjacency_matrix, target_species);
                break;
            }
            case 7: {
                printf("\033[32mOption 7 choisie : Calculer la centralite des especes.\n\033[0m");
                int in_degree[MAX_ESPECE], out_degree[MAX_ESPECE];
                float centrality[MAX_ESPECE];

                compute_degrees(n, adjacency_matrix, in_degree, out_degree);
                compute_betweenness_centrality(n, adjacency_matrix, centrality);

                printf("\033[32m\nCentralite des especes :\n\033[0m");
                for (int i = 0; i < n; i++) {
                    printf("%s : demi-degre interieur = %d, demi-degre exterieur = %d, centralite = %.2f\n",
                           species[i], in_degree[i], out_degree[i], centrality[i]);
                }
                break;
            }
            case 8: {
                printf("\033[32mOption 8 choisie : Simuler la disparition d'une espece.\n\033[0m");
                char target_species[MAX_NAME_LENGTH];
                printf("\033[36mEntrez le nom de l'espece a supprimer : \033[0m");
                scanf("%s", target_species);
                simulate_species_removal(&n, species, adjacency_matrix, target_species);
                break;
            }
            case 9:
                printf("\033[32mOption 9 choisie : Restaurer l'espece supprimee.\n\033[0m");
                restore_species(&n, species, adjacency_matrix);
                break;
            case 10:
                printf("\033[32mOption 10 choisie : Simulation de la dynamique des populations.\n\033[0m");
                population_dynamics_menu(n, species, populations, growth_rates, carrying_capacities, anthropic_impact, adjacency_matrix);
                break;

            case 11:
                printf("\033[31mAu revoir !\n\033[0m");
                break;
            default:
                printf("\033[31mOption invalide. Veuillez choisir une option valide.\n\033[0m");
        }
    } while (choice != 11);

    return 0;
}
