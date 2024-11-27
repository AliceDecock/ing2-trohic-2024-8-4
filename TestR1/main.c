#include <stdio.h>
#include <stdlib.h>
#include "network.h"
#include "connexite.h"

int main() {
    int n;
    char species[MAX_SPECIES][MAX_NAME_LENGTH];
    float adjacency_matrix[MAX_SPECIES][MAX_SPECIES];

    char filename[100];
    printf("Veuillez saisir le nom du fichier reseau : ");
    scanf("%s", filename);

    read_network(filename, &n, species, adjacency_matrix);
    printf("\nReseau charge avec succes depuis le fichier : %s\n", filename);

    int choice;
    do {
        printf("\n=== Menu ===\n");
        printf("1. Afficher la liste des especes\n");
        printf("2. Afficher la liste des arcs\n");
        printf("3. Afficher les successeurs et predecesseurs des especes\n");
        printf("4. Verifier la connexite\n");
        printf("5. Rechercher des sommets particuliers\n");
        printf("6. Quitter\n");
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
            case 6:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir une option valide.\n");
        }
    } while (choice != 6);

    return 0;
}
