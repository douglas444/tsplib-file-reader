# tsplib-file-reader

This program load data from a TSPLIB file to the structure indicated above.

`struct tspInfo {

    char *name,
         *comment,
         *type,
         *edge_weight_format,
         *edge_weight_type;

    int dimension;

    double **distances;

};`

Supported types: TSP
Supported edge weight types: EXPLICIT, EUC_2D
Supported edge weight format: UPPER_ROW

In specifications, spaces before and after the character ":" are needed.
Example: `<keyword> : <value>`


