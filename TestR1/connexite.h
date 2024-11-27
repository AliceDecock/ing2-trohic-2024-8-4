#ifndef CONNEXITE_H
#define CONNEXITE_H

void check_connectivity(int n, float adjacency_matrix[][MAX_SPECIES]);
void find_special_vertices(int n, char species[][MAX_NAME_LENGTH], float adjacency_matrix[][MAX_SPECIES]);

#endif
