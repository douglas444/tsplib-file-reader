#include <stdio.h>
#include <stdlib.h>
#include "tspReader.h"

int main()
{
    int i, j;

    FILE *f = fopen("../gr17.tsp", "r");
    TspInfo *tspInfo = read(f);

    printf("NAME : %s\n", tspInfo->name);
    printf("TYPE : %s\n", tspInfo->type);
    printf("DIMENSION : %d\n", tspInfo->dimension);
    printf("EDGE_WEIGHT_TYPE : %s\n", tspInfo->edge_weight_type);
    if(tspInfo->edge_weight_format != NULL){
        printf("EDGE_WEIGHT_FORMAT : %s\n", tspInfo->edge_weight_format);
    }

    for(i = 0; i < tspInfo->dimension; ++i){
        for(j = 0; j < tspInfo->dimension; ++j){
            if(i != j)
                printf("\t%2.lf ", tspInfo->distances[i][j]);
            else
                printf("\tXXX ");
        }
        printf("\n");
    }

    return 0;
}
