# tsplib-file-reader

This program load data from a TSPLIB file to the structure indicated below.


    struct tspInfo {
        char *name,
            *comment,
            *type,
            *edge_weight_format,
            *edge_weight_type;

        int dimension;

        double **distances;
    };


Supported types: TSP<br/>
Supported edge weight types: EXPLICIT, EUC_2D<br/>
Supported edge weight format: UPPER_ROW<br/>

In specifications, spaces before and after the character `:` are needed.<br/>
Example: `<keyword> : <value>`


