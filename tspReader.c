#include "tspReader.h"
#include <string.h>
#include <math.h>

void freeTspInfo(TspInfo *tspInfo){

    int i;

    if(tspInfo->name != NULL) {
        free(tspInfo->name);
    }
    if(tspInfo->type != NULL) {
        free(tspInfo->type);
    }
    if(tspInfo->edge_weight_format != NULL) {
        free(tspInfo->edge_weight_format);
    }
    if(tspInfo->edge_weight_type != NULL) {
        free(tspInfo->edge_weight_type);
    }
    if(tspInfo->distances != NULL) {
        for(i = 0; i < tspInfo->dimension; ++i){
            free(tspInfo->distances[i]);
        }
        free(tspInfo->distances);
    }
}

void readSpecification(char *entry, char **keyword, char **value){

    int divisionIndex, i, j, count;
    char *line, *divisionPointer, *temp;

    count = 0;

    //Count space chars in the entry
    for(i = 0; i < strlen(entry); ++i){
        if(entry[i] == ' '){
            ++count;
        }
    }

    line = (char*) malloc(sizeof(char) * (strlen(entry) - count + 1));

    j = 0;

    //Copy the entry without spaces chars to the line array
    for(i = 0; i < strlen(entry) - count; ++i){

        while(entry[j] == ' '){
            ++j;
        }

        line[i] = entry[j];
        ++j;

    }
    line[strlen(entry) - count] = '\0';
    divisionPointer = strstr(line, ":");

    if(divisionPointer != NULL){

        divisionIndex = divisionPointer - line;

        *keyword = (char*) malloc(sizeof(char) * (divisionIndex + 1));
        strncpy(*keyword, line, divisionIndex);
        (*keyword)[divisionIndex] = '\0';

        temp = (char*) malloc(sizeof(char) * (strlen(line) - strlen(*keyword) - strlen(":") + 1));
        strcpy(temp, &line[divisionIndex + strlen(":")]);

        //temp contains the value string with a \n in the end
        *value = (char*) malloc(sizeof(char) * (strlen(temp)));
        strncpy(*value, temp, strlen(temp) - 1);
        (*value)[strlen(temp) -1] = '\0';

        free(temp);
    }

    free(line);

}

double calcDistance(double x1, double y1, double x2, double y2){

    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));

}

TspInfo* read(FILE *file){

    int i, j, id;
    double **coords;
    size_t n;
    char *line, *keyword, *value;
    TspInfo *tspInfo;

    if(file == NULL){
        printf("Error: File not found\n");
        exit(1);
    }

    line = NULL;
    keyword = NULL;
    value = NULL;

    tspInfo = (TspInfo*) malloc(sizeof(TspInfo));
    tspInfo->name = NULL;
    tspInfo->edge_weight_format = NULL;
    tspInfo->edge_weight_type = NULL;
    tspInfo->distances = NULL;
    tspInfo->dimension = -1;

    while(getline(&line, &n, file) != -1){

        //Specification part
        if(strstr(line, ":") != NULL)
        {

            readSpecification(line, &keyword, &value);

            if(strcmp("TYPE", keyword) == 0)
            {

                tspInfo->type = (char*) malloc(sizeof(char) * strlen(value));
                strcpy(tspInfo->type, value);

            }
            else if(strcmp("DIMENSION", keyword) == 0)
            {

                tspInfo->dimension = atoi(value);

            }
            else if(strcmp("EDGE_WEIGHT_FORMAT", keyword) == 0)
            {

                tspInfo->edge_weight_format = (char*) malloc(sizeof(char) * strlen(value));
                strcpy(tspInfo->edge_weight_format, value);

            }
            else if(strcmp("EDGE_WEIGHT_TYPE", keyword) == 0)
            {

                tspInfo->edge_weight_type = (char*) malloc(sizeof(char) * strlen(value));
                strcpy(tspInfo->edge_weight_type, value);

            }
            else if(strcmp("NAME", keyword) == 0)
            {

                tspInfo->name = (char*) malloc(sizeof(char) * strlen(value));
                strcpy(tspInfo->name, value);

            }


        }

        //Data part
        else if(!strcmp(line, "NODE_COORD_SECTION\n") || !strcmp(line, "EDGE_WEIGHT_SECTION\n"))
        {
            //Check if some needed specification is invalid or undefined
            if(strcmp(tspInfo->type, "TSP") != 0 ||
               tspInfo->dimension < 2 ||
               (strcmp(tspInfo->edge_weight_type, "EXPLICIT") == 0 && strcmp(tspInfo->edge_weight_format, "UPPER_ROW") != 0)){

                freeTspInfo(tspInfo);
                printf("Error: Invalid specifications\n");
                exit(1);

            }

            //For coords
            if(!strcmp(line, "NODE_COORD_SECTION\n"))
            {

                coords = (double**) malloc(sizeof(double*) * tspInfo->dimension);
                for(i = 0; i < tspInfo->dimension; ++i){

                    coords[i] = (double*) malloc(sizeof(double) * 2);
                    fscanf(file, "%d %lf %lf\n", &id, &coords[i][0], &coords[i][1]);
                }

                tspInfo->distances = (double**) malloc(sizeof(double*) * tspInfo->dimension);
                for(i = 0; i < tspInfo->dimension; ++i){

                    tspInfo->distances[i] = (double*) malloc(sizeof(double) * tspInfo->dimension);
                }

                for(i = 0; i < tspInfo->dimension; ++i){

                    for(j = 0; j < tspInfo->dimension; ++j){

                        tspInfo->distances[i][j] = calcDistance(coords[i][0], coords[i][1], coords[j][0], coords[j][1]);
                        tspInfo->distances[j][i] = tspInfo->distances[i][j];

                    }
                }

                for(i = 0; i < tspInfo->dimension; ++i){
                    free(coords[i]);
                }
                free(coords);

            }

            //For explicit matrix
            else
            {

                tspInfo->distances = (double**) malloc(sizeof(double*) * tspInfo->dimension);
                for(i = 0; i < tspInfo->dimension; ++i){
                    tspInfo->distances[i] = (double*) malloc(sizeof(double) * tspInfo->dimension);
                }

                for(i = 0; i < tspInfo->dimension; ++i)
                {
                    for(j = i + 1; j < tspInfo->dimension; ++j)
                    {

                        fscanf(file, "%lf ", &tspInfo->distances[i][j]);
                        tspInfo->distances[j][i] = tspInfo->distances[i][j];

                    }

                    fscanf(file, "\n");
                }

            }

        }

        if(line != NULL){
            free(line);
            line = NULL;
        }
        if(keyword != NULL){
            free(keyword);
            keyword = NULL;
        }
        if(value != NULL){
            free(value);
            value = NULL;
        }
    }

    return tspInfo;
}
