#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "connexite.h"
#include "centralite.h"
#include "dynamique.h"

int main() {
    int n;
    char especes[MAX_ESPECE][MAX_NAME_LENGTH];
    float matrice_adjacence[MAX_ESPECE][MAX_ESPECE];
    float populations[MAX_ESPECE];
    float growth_rates[MAX_ESPECE];
    float carrying_capacities[MAX_ESPECE];


    char filename[100];
    printf("Veuillez saisir le nom du fichier reseau : ");
    scanf("%s", filename);

    read_network(filename, &n, especes, matrice_adjacence, populations, growth_rates, carrying_capacities);
    printf("Liste des especes chargees :\n");
    for (int i = 0; i < n; i++) {
        printf("- %s\n", especes[i]);
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
        printf("7. Calculer la centralite des especes\n");
        printf("8. Simuler la disparition d'une espece\n");
        printf("9. Restaurer l'espece supprimee\n");
        printf("10. Simulation de la dynamique des populations\n");
        printf("11. Quitter\n");
        printf("Veuillez choisir une option : ");


        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_species(n, especes);
                break;
            case 2:
                display_arcs(n, especes, matrice_adjacence);
                break;
            case 3:
                display_successors_predecessors(n, especes, matrice_adjacence);
                break;
            case 4:
                check_connectivity(n, matrice_adjacence);
                break;
            case 5:
                find_special_vertices(n, especes, matrice_adjacence);
                break;
            case 6: {
                char target_species[MAX_NAME_LENGTH];
                printf("Entrez le nom de l'espece a etudier : ");
                scanf("%s", target_species);
                analyze_trophic_levels(n, especes, matrice_adjacence, target_species);
                break;
            }
            case 7: {
                int in_degree[MAX_ESPECE], out_degree[MAX_ESPECE];
                float centrality[MAX_ESPECE];

                compute_degrees(n, matrice_adjacence, in_degree, out_degree);
                compute_betweenness_centrality(n, matrice_adjacence, centrality);

                printf("\nCentralite des especes :\n");
                for (int i = 0; i < n; i++) {
                    printf("%s : demi-degre interieur = %d, demi-degree exterieur = %d, centralite = %.2f\n",
                           especes[i], in_degree[i], out_degree[i], centrality[i]);
                }
                break;
            }
            case 8: {
                char target_species[MAX_NAME_LENGTH];
                printf("Entrez le nom de l'espece a supprimer : ");
                scanf("%s", target_species);
                simulate_species_removal(&n, especes, matrice_adjacence, target_species);
                break;
            }
            case 9:
                restore_species(&n, especes, matrice_adjacence);
                break;
            case 10: {
                int iterations;
                printf("Entrez le nombre d'iterations pour la simulation : ");
                scanf("%d", &iterations);
                simulate_population_dynamics(
                        n, especes, matrice_adjacence, growth_rates, carrying_capacities, populations, iterations);
                break;
            }
            case 11:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir une option valide.\n");
        }
    } while (choice != 6);

    return 0;
}