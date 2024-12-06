#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dynamique.h"

static int simulation_running = 0; // To track the state of the simulation

void start_simulation(int n, char species[][MAX_NAME_LENGTH], float populations[], float growth_rates[], float carrying_capacities[], float anthropic_impact[], int iterations) {
    printf("Demarrage de la simulation...\n");
    simulation_running = 1;

    for (int iter = 0; iter < iterations && simulation_running; iter++) {
        printf("\nIteration %d :\n", iter + 1);

        for (int i = 0; i < n; i++) {
            // Calculate growth and anthropic terms
            float growth_term = growth_rates[i] * populations[i] * (1 - populations[i] / carrying_capacities[i]);
            float anthropic_term = populations[i] * anthropic_impact[i];

            // Update population
            float old_population = populations[i];
            populations[i] += growth_term - anthropic_term;

            // Prevent negative population
            if (populations[i] < 0) {
                populations[i] = 0;
            }

            // Debugging: Display calculation details
            printf("Espece : %s | Population (ancienne) : %.2f | Croissance : %.2f | Impact anthropique : %.2f | Population (nouvelle) : %.2f\n",
                   species[i], old_population, growth_term, anthropic_term, populations[i]);
        }

        sleep(1); // Simulate real-time progress
    }
}


void pause_simulation() {
    printf("Simulation mise en pause.\n");
    simulation_running = 0;
}

void modify_species_parameters(int n, char species[][MAX_NAME_LENGTH], float growth_rates[], float carrying_capacities[]) {
    char species_name[MAX_NAME_LENGTH];
    printf("Entrez le nom de l'espece a modifier: ");
    scanf("%s", species_name);

    int found = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(species_name, species[i]) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Espece non trouve.\n");
        return;
    }

    printf("Entrez le nouveau taux de croissance pour %s: ", species_name);
    scanf("%f", &growth_rates[found]);
    printf("Entrez la nouvelle capacite de charge pour %s: ", species_name);
    scanf("%f", &carrying_capacities[found]);
    printf("Parametre mis a jour pour %s.\n", species_name);
}

void display_current_state(int n, char species[][MAX_NAME_LENGTH], float populations[]) {
    printf("\n Etat actuel:\n");
    for (int i = 0; i < n; i++) {
        printf(" - %s: %.2f\n", species[i], populations[i]);
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

void population_dynamics_menu(int n, char species[][MAX_NAME_LENGTH], float populations[], float growth_rates[], float carrying_capacities[], float anthropic_impact[]) {
    int choice;
    do {
        printf("\n=== SIMULATION DYNAMIQUE DES POPULATIONS ===\n");
        printf("1. Demarrer/Reprendre la simulation\n");
        printf("2. Pause\n");
        printf("3. Modifier les parametres d'une espece\n");
        printf("4. Afficher l'etat actuel\n");
        printf("5. Sauvegarder l'etat\n");
        printf("6. Retour au menu principal\n");
        printf("Veuillez choisir une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            {
                int iterations;
                printf("Entrez le nombre d'iterations: ");
                scanf("%d", &iterations);
                start_simulation(n, species, populations, growth_rates, carrying_capacities, anthropic_impact, iterations);
            }
                break;

            case 2:
                pause_simulation();
                break;

            case 3:
                modify_species_parameters(n, species, growth_rates, carrying_capacities);
                break;

            case 4:
                display_current_state(n, species, populations);
                break;

            case 5:
                save_state("simulation_state.txt", n, species, populations, growth_rates, carrying_capacities);
                break;

            case 6:
                printf("Retour au Menu...\n");
                break;

            default:
                printf("Choix invalide Veuillez reessayer.\n");
        }
    } while (choice != 6);
}
