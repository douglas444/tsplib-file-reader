#include <stdio.h>
#include <stdlib.h>
#include "tspReader.h"

int main()
{
    FILE *f = fopen("d657.tsp", "r");
    TspInfo *tspInfo = read(f);

    printf("NAME : %s\n", tspInfo->name);
    printf("COMMENT : ");
    puts(tspInfo->comment);
    printf("TYPE : %s\n", tspInfo->type);
    printf("DIMENSION : %d\n", tspInfo->dimension);
    printf("EDGE_WEIGHT_TYPE : %s\n", tspInfo->edge_weight_type);
    if(tspInfo->edge_weight_format != NULL){
        printf("EDGE_WEIGHT_FORMAT : %s\n", tspInfo->edge_weight_format);
    }
    return 0;
}
