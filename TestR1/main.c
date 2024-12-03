#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "connexite.h"
#include "population.h"

void save_configuration(const char *filename, int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES], PopulationData *pop_data) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Erreur lors de la sauvegarde");
        return;
    }
    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s %.2f %.2f %.2f\n", species[i], pop_data->populations[i], pop_data->growth_rates[i], pop_data->carrying_capacities[i]);
    }
    fclose(file);
    printf("Configuration sauvegardée avec succès.\n");
}

void load_configuration(const char *filename, int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES], PopulationData *pop_data) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Erreur lors du chargement");
        return;
    }
    fscanf(file, "%d", n);
    for (int i = 0; i < *n; i++) {
        fscanf(file, "%s %f %f %f", species[i], &pop_data->populations[i], &pop_data->growth_rates[i], &pop_data->carrying_capacities[i]);
    }
    fclose(file);
    printf("Configuration chargée avec succès.\n");
}

int main() {
    int n;
    char species[MAX_SPECIES][MAX_NAME_LENGTH];
    float adjacency_matrix[MAX_SPECIES][MAX_SPECIES];
    PopulationData pop_data;

    char filename[100];
    printf("Veuillez saisir le nom du fichier reseau : ");
    scanf("%s", filename);

    read_network(filename, &n, species, adjacency_matrix, pop_data.populations, pop_data.growth_rates, pop_data.carrying_capacities);
    initialize_population(n, &pop_data);

    int choice;
    do {
        printf("\n=== Menu ===\n");
        printf("1. Afficher la liste des especes\n");
        printf("2. Afficher la liste des arcs\n");
        printf("3. Afficher les successeurs et predecesseurs des especes\n");
        printf("4. Verifier la connexite\n");
        printf("5. Rechercher des sommets particuliers\n");
        printf("6. Etude des niveaux trophiques et des chaines alimentaires\n");
        printf("7. Afficher les populations\n");
        printf("8. Simulation de la dynamique des populations\n");
        printf("9. Ajuster les parametres des especes\n");
        printf("10. Sauvegarder la configuration\n");
        printf("11. Charger une configuration\n");
        printf("12. Neutraliser une espece\n");
        printf("13. Quitter\n");
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
            case 7:
                display_population(n, species, &pop_data);
                break;
            case 8: {
                int iterations;
                printf("Entrez le nombre d'iterations pour la simulation : ");
                scanf("%d", &iterations);
                update_population_dynamics(n, adjacency_matrix, species, &pop_data, iterations);
                break;
            }
            case 9:
                adjust_parameters(n, species, &pop_data, adjacency_matrix);
                break;
            case 10:
                printf("Nom du fichier de sauvegarde : ");
                scanf("%s", filename);
                save_configuration(filename, n, species, adjacency_matrix, &pop_data);
                break;
            case 11:
                printf("Nom du fichier a charger : ");
                scanf("%s", filename);
                load_configuration(filename, &n, species, adjacency_matrix, &pop_data);
                break;
            case 12: {
                char target_species[MAX_NAME_LENGTH];
                printf("Entrez le nom de l'espece a neutraliser : ");
                scanf("%s", target_species);
                for (int i = 0; i < n; i++) {
                    if (strcmp(species[i], target_species) == 0) {
                        pop_data.populations[i] = 0.0;
                        printf("Espece %s neutralisee.\n", target_species);
                        break;
                    }
                }
                break;
            }
            case 13:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir une option valide.\n");
        }
    } while (choice != 13);

    return 0;
}
