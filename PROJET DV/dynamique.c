
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "dynamique.h"

static int simulation_running = 0; // To track the state of the simulation

void demarrersimulation(int n, char especes[][MAX_NAME_LENGTH], float populations[], float croissance[], float portage[], float anthropic_impact[], float adjacency_matrix[][MAX_ESPECE], int iterations) {
    printf("Demarrage de la simulation...\n");
    simulation_running = 1;

    float pollution_level = 0.0; // Simulated pollution level

    for (int iter = 0; iter < iterations && simulation_running; iter++) {
        printf("\nIteration %d :\n", iter + 1);

        pollution_level = 0.01 * iter; // Incremental pollution per iteration

        for (int i = 0; i < n; i++) {
            float growth_term = croissance[i] * populations[i] * (1 - populations[i] / portage[i]);
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
                   especes[i], old_population, growth_term, anthropic_term, predation_term, populations[i]);
        }

        sleep(1);
    }

    printf("Simulation terminee apres %d iterations.\n", iterations);
}

void pause_simulation() {
    printf("Simulation mise en pause.\n");
    simulation_running = 0;
}

void parametresespece(int n, char especes[][MAX_NAME_LENGTH], float croissance[], float portage[]) {
    char species_name[MAX_NAME_LENGTH];
    printf("Entrez le nom de l'espece a modifier : ");
    scanf("%s", species_name);

    int found = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(species_name, especes[i]) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Espece non trouvee.\n");
        return;
    }

    printf("Entrez le nouveau taux de croissance pour %s : ", species_name);
    scanf("%f", &croissance[found]);
    printf("Entrez la nouvelle capacite de charge pour %s : ", species_name);
    scanf("%f", &portage[found]);
    printf("Parametres mis a jour pour %s.\n", species_name);
}

void parametresantrophique(int n, char especes[][MAX_NAME_LENGTH], float antrophique[]) {
    char species_name[MAX_NAME_LENGTH];
    printf("Entrez le nom de l'espece pour modifier l'impact anthropique : ");
    scanf("%s", species_name);

    int found = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(species_name, especes[i]) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Espèce non trouvée.\n");
        return;
    }

    printf("Entrez le nouvel impact anthropique pour %s : ", species_name);
    scanf("%f", &antrophique[found]);
    printf("Impact anthropique mis a jour pour %s a %.2f.\n", species_name, antrophique[found]);
}

void afficher_etat(int n, char especes[][MAX_NAME_LENGTH], float populations[]) {
    printf("\nEtat actuel des populations :\n");
    for (int i = 0; i < n; i++) {
        printf(" - %s : %.2f\n", especes[i], populations[i]);
    }
}

void sauv_etat(const char *nomfichier, int n, char especes[][MAX_NAME_LENGTH], float populations[], float croissance[], float portage[]) {
    FILE *file = fopen(nomfichier, "w");
    if (file == NULL) {
        perror("Erreur lors de la sauvegarde de l'etat");
        return;
    }

    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        fprintf(file, "%s %.2f %.2f %.2f\n", especes[i], populations[i], croissance[i], portage[i]);
    }

    fclose(file);
    printf("Etat sauvegarde dans %s.\n", nomfichier);
}
void menudynamique(int n, char especes[][MAX_NAME_LENGTH], float populations[], float croissance[], float portage[], float anthropique[], float matrice_adjacence[][MAX_ESPECE]) {
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
                demarrersimulation(n, especes, populations, croissance, portage, anthropique,
                                   matrice_adjacence, iterations);
            }
                break;

            case 2:
                pause_simulation();
                break;

            case 3:
                parametresespece(n, especes, croissance, portage);
                break;

            case 4:
                parametresantrophique(n, especes, anthropique);
                break;

            case 5:
                afficher_etat(n, especes, populations);
                break;

            case 6:
                sauv_etat("simulation_state.txt", n, especes, populations, croissance, portage);
                break;

            case 7:
                printf("Retour au Menu...\n");
                break;

            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choice != 7);
}
