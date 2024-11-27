#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SPECIES 100
#define MAX_NAME_LENGTH 20

// Fonction pour lire le fichier reseau
void read_network(const char *filename, int *n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    fscanf(file, "%d", n); // Lire le nombre d'especes

    // Lire les noms des especes
    for (int i = 0; i < *n; i++) {
        fscanf(file, "%s", species[i]);
    }

    // Lire la matrice d'adjacence
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            fscanf(file, "%f", &adjacency_matrix[i][j]);
        }
    }

    fclose(file);
}

// Fonction pour afficher les successeurs et predecesseurs
void display_successors_predecessors(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES]) {
    char target[MAX_NAME_LENGTH];
    printf("Entrez le nom de l'espece a interroger : ");
    scanf("%s", target);

    int index = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(species[i], target) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Espece non trouvee.\n");
        return;
    }

    printf("Successeurs (qui sont manges par %s) :\n", target);
    for (int j = 0; j < n; j++) {
        if (adjacency_matrix[index][j] > 0) {
            printf("- %s (ponderation : %.1f)\n", species[j], adjacency_matrix[index][j]);
        }
    }

    printf("Predecesseurs (qui mangent %s) :\n", target);
    for (int i = 0; i < n; i++) {
        if (adjacency_matrix[i][index] > 0) {
            printf("- %s (ponderation : %.1f)\n", species[i], adjacency_matrix[i][index]);
        }
    }
}

// Fonction pour afficher les premiers maillons
void display_first_links(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES]) {
    printf("Premiers maillons (sans predecesseurs) :\n");
    for (int j = 0; j < n; j++) {
        int has_predecessor = 0;
        for (int i = 0; i < n; i++) {
            if (adjacency_matrix[i][j] > 0) {
                has_predecessor = 1;
                break;
            }
        }
        if (!has_predecessor) {
            printf("- %s\n", species[j]);
        }
    }
}

// Fonction pour afficher les derniers maillons
void display_last_links(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES]) {
    printf("Derniers maillons (sans successeurs) :\n");
    for (int i = 0; i < n; i++) {
        int has_successor = 0;
        for (int j = 0; j < n; j++) {
            if (adjacency_matrix[i][j] > 0) {
                has_successor = 1;
                break;
            }
        }
        if (!has_successor) {
            printf("- %s\n", species[i]);
        }
    }
}

// Fonction principale
int main() {
    int n; // Nombre d'especes
    char species[MAX_SPECIES][MAX_NAME_LENGTH]; // Noms des especes
    float adjacency_matrix[MAX_SPECIES][MAX_SPECIES]; // Matrice d'adjacence

    char filename[100];
    printf("Veuillez saisir le nom du fichier reseau : ");
    scanf("%s", filename);

    // Charger le reseau
    read_network(filename, &n, species, adjacency_matrix);
    printf("Reseau charge avec succes depuis le fichier : %s\n", filename);

    int choice;
    do {
        printf("\n=== Menu ===\n");
        printf("1. Afficher les successeurs et predecesseurs des sommets\n");
        printf("2. Afficher les premiers maillons (sans predecesseurs)\n");
        printf("3. Afficher les derniers maillons (sans successeurs)\n");
        printf("4. Quitter\n");
        printf("Veuillez choisir une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_successors_predecessors(n, species, adjacency_matrix);
                break;
            case 2:
                display_first_links(n, species, adjacency_matrix);
                break;
            case 3:
                display_last_links(n, species, adjacency_matrix);
                break;
            case 4:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir une option valide.\n");
        }
    } while (choice != 4);

    return 0;
}
