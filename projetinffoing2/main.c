#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "connexite.h"
#include "centralite.h"

int main() {
    int n;
    char species[MAX_SPECIES][MAX_NAME_LENGTH];
    float adjacency_matrix[MAX_SPECIES][MAX_SPECIES];
    float populations[MAX_SPECIES];
    float growth_rates[MAX_SPECIES];
    float carrying_capacities[MAX_SPECIES];


    char filename[100];
    printf("Veuillez saisir le nom du fichier reseau : ");
    scanf("%s", filename);

    read_network(filename, &n, species, adjacency_matrix, populations, growth_rates, carrying_capacities);
    printf("Liste des especes chargees :\n");
    for (int i = 0; i < n; i++) {
        printf("- %s\n", species[i]);
    }

    printf("\nReseau charge avec succes depuis le fichier : %s\n", filename);

    int choice;
    do {
        printf("\n=== Menu ===\n");
        printf("1. Afficher la liste des especes\n");
        printf("2. Afficher la liste des arcs\n");
        printf("3. Afficher les successeurs et predecesseurs des especes\n");
        printf("4. Verifier la connexite\n");
        printf("5. Rechercher des sommets particuliers\n");
        printf("6. Etude des niveaux trophiques et des chaines alimentaires\n");
        printf("7. Simulation de la dynamique des populations\n");
        printf("8. Calculer la centralite des especes\n");
        printf("9. Simuler la disparition d'une espece\n");
        printf("10. Restaurer l'espece supprimee\n");
        printf("11. Quitter\n");
        printf("Veuillez choisir une option : ");


        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_species(n, species);
                break;
            case 2:
                display_arcs(n, species, adjacency_matrix);
                break;
            case 3:
                display_successors_predecessors(n, species, adjacency_matrix);
                break;
            case 4:
                check_connectivity(n, adjacency_matrix);
                break;
            case 5:
                find_special_vertices(n, species, adjacency_matrix);
                break;
            case 6: {
                char target_species[MAX_NAME_LENGTH];
                printf("Entrez le nom de l'espece a etudier : ");
                scanf("%s", target_species);
                analyze_trophic_levels(n, species, adjacency_matrix, target_species);
                break;
            }
            case 7: {
                int iterations;
                printf("Entrez le nombre d'iterations pour la simulation : ");
                scanf("%d", &iterations);
                simulate_population_dynamics(n, species, adjacency_matrix, growth_rates, carrying_capacities, populations, iterations);
                break;
            }
            case 8: {
                int in_degree[MAX_SPECIES], out_degree[MAX_SPECIES];
                float centrality[MAX_SPECIES];

                compute_degrees(n, adjacency_matrix, in_degree, out_degree);
                compute_betweenness_centrality(n, adjacency_matrix, centrality);

                printf("\nCentralite des especes :\n");
                for (int i = 0; i < n; i++) {
                    printf("%s : demi-degre interieur = %d, demi-degree exterieur = %d, centralite = %.2f\n",
                           species[i], in_degree[i], out_degree[i], centrality[i]);
                }
                break;
            }
            case 9: {
                char target_species[MAX_NAME_LENGTH];
                printf("Entrez le nom de l'espece a supprimer : ");
                scanf("%s", target_species);
                simulate_species_removal(&n, species, adjacency_matrix, target_species);
                break;
            }
            case 10:
                restore_species(&n, species, adjacency_matrix);
                break;
            case 11:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir une option valide.\n");
        }
    } while (choice != 6);

    return 0;
}