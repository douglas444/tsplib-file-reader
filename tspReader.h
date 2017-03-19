#include <stdio.h>
#include <stdlib.h>

struct tspInfo {

    char *name,
         *type,
         *edge_weight_format,
         *edge_weight_type;

    int dimension;

    double **distances;

};

typedef struct tspInfo TspInfo;

void freeTspInfo(TspInfo *tspInfo);
TspInfo* read(FILE *file);
