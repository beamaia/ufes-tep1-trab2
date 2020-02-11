#include <stdio.h>
#include <stdlib.h>
#include "spec.h"
#include "catalog.h"

int main()
{
    char arq_path1[150], arq_path2[150], arq_path3[150];
    scanf("%s", arq_path1);
    FILE *arc_cat = fopen(arq_path1, "r");
    scanf("%s", arq_path2);
    FILE *arc_current = fopen(arq_path2, "r");
    scanf("%s", arq_path3);
    FILE *arc_spec = fopen(arq_path3, "r");

    if(arc_cat == NULL || arc_current == NULL || arc_spec == NULL)
    {
        printf("One of the files were not found\n");
        exit(1);
    }

    Catalog properties, clayey, houses;
    Spec spec;
    Identifiers id;

    properties = initialize_catalog();
    read_catalog(properties, arc_cat);
    read_current(properties, arc_current);
    read_spec(&spec, arc_spec);
    initialize_identifiers(&id);


    if(are_there_properties(properties))
    {
        clayey = initialize_catalog();
        houses = initialize_catalog();
        calculate_properties_information(properties);
        sort_create_all_catalogs(properties, clayey, houses, &spec, &id);
        print_id_catalogs(properties, clayey, houses, &spec, &id);
        free_catalogs_and_properties_used(properties, clayey, houses);
    }
    else
        printf("0");
    free_catalog(properties);

    fclose(arc_cat);
    fclose(arc_current);
    fclose(arc_spec);
    return 0;
}