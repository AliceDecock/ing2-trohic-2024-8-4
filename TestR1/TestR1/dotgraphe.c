#include "dotgraphe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100

void generate_dot_file(const char *input_file, const char *output_file) {
    FILE *input = fopen(input_file, "r");
    FILE *output = fopen(output_file, "w");

    if (!input || !output) {
        perror("Erreur lors de louverture du fichier");
        exit(EXIT_FAILURE);
    }

    int node_count;
    fscanf(input, "%d", &node_count); // Lire le nombre de nœuds

    char nodes[MAX_NODES][50]; // Stocker les noms des nœuds
    for (int i = 0; i < node_count; i++) {
        fscanf(input, "%s", nodes[i]);
    }

    // Écrire dans le fichier DOT avec personnalisation
    fprintf(output, "digraph trophic_network {\n");
    fprintf(output, "    node [style=filled, fillcolor=lightblue, fontcolor=black];\n");
    fprintf(output, "    edge [color=gray, fontsize=10];\n");

    for (int i = 0; i < node_count; i++) {
        for (int j = 0; j < node_count; j++) {
            float weight;
            fscanf(input, "%f", &weight);
            if (weight > 0) {
                fprintf(output, "    \"%s\" -> \"%s\" [label=\"%.1f\", color=blue, penwidth=%.1f];\n",
                        nodes[i], nodes[j], weight, weight); // Poids utilisé pour la largeur de ligne
            }
        }
    }

    fprintf(output, "}\n");
    fclose(input);
    fclose(output);
    printf("Fichier DOT genere avec succes : %s\n", output_file);
}
