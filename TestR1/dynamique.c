#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dynamique.h"

static int simulation_running = 0; // To track the state of the simulation

void start_simulation(int n, char species[][MAX_NAME_LENGTH], float populations[], float growth_rates[], float carrying_capacities[], float anthropic_impact[], float adjacency_matrix[][MAX_ESPECE], int iterations) {
    printf("Demarrage de la simulation...\n");
    simulation_running = 1;

    float pollution_level = 0.0; // Simulated pollution level

    for (int iter = 0; iter < iterations && simulation_running; iter++) {
        printf("\nIteration %d :\n", iter + 1);

        pollution_level = 0.01 * iter; // Incremental pollution per iteration

        for (int i = 0; i < n; i++) {
            float growth_term = growth_rates[i] * populations[i] * (1 - populations[i] / carrying_capacities[i]);
            float anthropic_term = populations[i] * (anthropic_impact[i] + pollution_level);

            float predation_term = 0.0;
            for (int j = 0; j < n; j++) {
                if (adjacency_matrix[j][i] > 0) {
                    predation_term += adjacency_matrix[j][i] * populations[j];
                }
            }

            float old_population = populations[i];
            populations[i] += growth_term - anthropic_term - predation_term;

            if (populations[i] < 0) {
                populations[i] = 0;
            }

            printf("\033[32mEspece : %s\033[0m | \033[33mPopulation (ancienne) : %.2f\033[0m | \033[34mCroissance : %.2f\033[0m | \033[31mImpact anthropique : %.2f\033[0m | \033[35mPredation : %.2f\033[0m | \033[36mPopulation (nouvelle) : %.2f\033[0m\n",
                   species[i], old_population, growth_term, anthropic_term, predation_term, populations[i]);
        }

        sleep(1);
    }

    printf("Simulation terminee apres %d iterations.\n", iterations);
}

void pause_simulation() {
    printf("Simulation mise en pause.\n");
    simulation_running = 0;
}

void modify_species_parameters(int n, char species[][MAX_NAME_LENGTH], float growth_rates[], float carrying_capacities[]) {
    char species_name[MAX_NAME_LENGTH];
    printf("Entrez le nom de l'espece a modifier : ");
    scanf("%s", species_name);

    int found = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(species_name, species[i]) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Espece non trouvee.\n");
        return;
    }

    printf("Entrez le nouveau taux de croissance pour %s : ", species_name);
    scanf("%f", &growth_rates[found]);
    printf("Entrez la nouvelle capacite de charge pour %s : ", species_name);
    scanf("%f", &carrying_capacities[found]);
    printf("Parametres mis a jour pour %s.\n", species_name);
}

void modify_anthropic_impact(int n, char species[][MAX_NAME_LENGTH], float anthropic_impact[]) {
    char species_name[MAX_NAME_LENGTH];
    printf("Entrez le nom de l'espece pour modifier l'impact anthropique : ");
    scanf("%s", species_name);

    int found = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(species_name, species[i]) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Espèce non trouvée.\n");
        return;
    }

    printf("Entrez le nouvel impact anthropique pour %s : ", species_name);
    scanf("%f", &anthropic_impact[found]);
    printf("Impact anthropique mis a jour pour %s a %.2f.\n", species_name, anthropic_impact[found]);
}

void display_current_state(int n, char species[][MAX_NAME_LENGTH], float populations[]) {
    printf("\nEtat actuel des populations :\n");
    for (int i = 0; i < n; i++) {
        printf(" - %s : %.2f\n", species[i], populations[i]);
    }
}

void save_state(const char *filename, int n, char species[][MAX_NAME_LENGTH], float populations[], float growth_rates[], float carrying_capacities[]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Erreur lors de la sauvegarde de l'etat");
        return;
    }

    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s %.2f %.2f %.2f\n", species[i], populations[i], growth_rates[i], carrying_capacities[i]);
    }

    fclose(file);
    printf("Etat sauvegarde dans %s.\n", filename);
}
void population_dynamics_menu(int n, char species[][MAX_NAME_LENGTH], float populations[], float growth_rates[], float carrying_capacities[], float anthropic_impact[], float adjacency_matrix[][MAX_ESPECE]) {
    int choice;
    do {
        printf("\n=== SIMULATION DYNAMIQUE DES POPULATIONS ===\n");
        printf("1. Demarrer/Reprendre la simulation\n");
        printf("2. Pause\n");
        printf("3. Modifier les parametres d'une espece\n");
        printf("4. Modifier l'impact anthropique d'une espece\n");
        printf("5. Afficher l'etat actuel\n");
        printf("6. Sauvegarder l'etat\n");
        printf("7. Retour au menu principal\n");
        printf("Veuillez choisir une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int iterations;
                printf("Entrez le nombre d'iterations : ");
                scanf("%d", &iterations);
                start_simulation(n, species, populations, growth_rates, carrying_capacities, anthropic_impact, adjacency_matrix, iterations);
            }
                break;

            case 2:
                pause_simulation();
                break;

            case 3:
                modify_species_parameters(n, species, growth_rates, carrying_capacities);
                break;

            case 4:
                modify_anthropic_impact(n, species, anthropic_impact);
                break;

            case 5:
                display_current_state(n, species, populations);
                break;

            case 6:
                save_state("simulation_state.txt", n, species, populations, growth_rates, carrying_capacities);
                break;

            case 7:
                printf("Retour au Menu...\n");
                break;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice != 7);
}
