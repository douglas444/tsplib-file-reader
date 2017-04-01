# tsplib-file-reader

This program loads data from a TSPLIB file to the structure indicated below.


    struct tspInfo {
        char *name,
            *type,
            *edge_weight_format,
            *edge_weight_type;

        int dimension;

        double **distances;
    };


Supported types: TSP, ATSP<br/>
Supported edge weight types: EXPLICIT, EUC_2D<br/>
Supported edge weight format: UPPER_ROW, LOWER_ROW, UPPER_DIAG_ROW, LOWER_DIAG_ROW, FULL_MATRIX<br/>


