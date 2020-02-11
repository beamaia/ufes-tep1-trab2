#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "properties.h"
#include "category.h"
#define MAX_NAME 61


/*
 * EN: Struct with information of a property.
 * PT: Estrutura com informacao de um imovel.
 */
struct property{
    Category cat;
    char *tag;
    char *property_owner;
    unsigned int id;
    float price;
};

/*
 * EN: Identify the property type based on its tag.
 * Returns 1 if lot of triangular shape.
 * Returns 2 if lot of rectangular shape.
 * Returns 3 if lot of trapezoidal shape.
 * Returns 4 if the property is a house.
 * Returns 5 if the property is an apartment.
 * Returns 0 if the type wasn't identified.
 * PT: Identifica o tipo do imovel baseado no seu tag. Retorna valores de 0-5.
 */
int identify_category(Property prop)
{
    if(!strcmp(prop->tag, "triang"))
        return 1;
    if(!strcmp(prop->tag, "retang"))
        return 2;
    if(!strcmp(prop->tag, "trapez"))
        return 3;
    if(!strcmp(prop->tag, "casa"))
        return 4;
    if(!strcmp(prop->tag, "apto"))
        return 5;
    return 0;
}

/*
 * EN: Initializes properties by mallocing it and with price and id equal to 0.
 * PT: Inicializa um imovel fazendo malloc e igualando preco e id a 0.
 */
Property initialize_property()
{
    Property prop = (Property) malloc(sizeof(struct property));
    if(prop == NULL)
    {
        printf("Error allocating memory");
        exit(1);
    }
    prop->price = 0;
    prop->id = 0;
    return prop;
}

/*
 * EN: Free all of the information that was malloc'd of a property and property itself.
 * PT: Libera toda informacao que foi mallocada de um imovel, alem do proprio imovel.
 */
void free_property(Property prop)
{
    free(prop->property_owner);
    free(prop->tag);
    free(prop);
}

/*
 * EN: Read property's information.
 * PT: Le a informacao do imovel.
 */
int read_property(Property prop, FILE *arc)
{
    char aux[7];        
    char aux_name[MAX_NAME];
    fscanf(arc, "%s%*c", aux);
    if(!feof(arc)) //In case the file is NULL and only after the use of fscanf that the value of feof is 1.
    {
        fscanf(arc, "%u%*c", &prop->id);
        if (prop->id)
        {
            prop->tag = (char *) malloc(sizeof(char) * (strlen(aux) + 1));
            if(prop->tag == NULL)
            {
                printf("Error allocating memory");
                exit(1);
            }
            strcpy(prop->tag, aux);
            fscanf(arc, "%[^\n]%*c", aux_name);
            prop->property_owner = (char *) malloc(sizeof(char) * (strlen(aux_name) + 1));
            if(prop->property_owner == NULL)
            {
                printf("Error allocating memory");
                exit(1);
            }
            strcpy(prop->property_owner, aux_name);
            return read_category(&prop->cat, identify_category(prop), arc);
        }
    }
    return 0;
}

/*
 * EN: Read id of a property that will be removed from the catalog.
 * PT: Le id dum imovel que sera excluido do catalogo.
 */
void read_property_to_be_removed(Property prop, FILE * arc)
{
    fscanf(arc, "%u%*c%*c", &prop->id);
}

/*
 * EN: Calls a function that calculates the area of the property.
 * PT: Chama uma funcao que calcula a area dum imovel.
 */
void area_property(Property prop)
{
   area_category(&prop->cat, identify_category(prop));
}

/*
 * EN: Calculates the property's price.
 * PT: Calcula o preco do imovel.
 */
void price_property(Property prop)
{
    prop->price = price_category(&prop->cat, identify_category(prop));
}

/*
 * EN: Compares the id of two properties. If they're the same, returns 2, if prop1 has an id of bigger value, returns 1, otherwise returns 0.
 * PT: Compara o id de dois imoveis. Se eles sao iguais, retorna 2, se prop1 tem um id maior, retorna 1, caso contrario retorna 0.
 */
int compare_id_property(Property prop1, Property prop2)
{
    if(prop1->id > prop2->id)
        return 1;
    if(prop1->id == prop2->id)
        return 2;
    return 0;
}

/*
 * EN: Returns the result of the comparison of room quantities between two properties. If they're the same, returns the result of compare_id_property.
 * PT: Retorna o valor duma comparacao de quantidade de quartos entre dois imoveis. Se a quantidade for igual, retorna o resultado da funcao
 * compare_id_property.
 */
int compare_room_property(Property prop1, Property prop2)
{
    int comp = compare_room_quantity_category(&prop1->cat, &prop2->cat, identify_category(prop1), identify_category(prop2));
    if(comp == 2)
    {
        if(!compare_id_property(prop1, prop2))
            return 1;
        else
            return 0;
    }

    return comp;
}

/*
 * EN: Returns the result of the comparison of the price of two properties. If they're the same, returns the result of compare_id_property.
 * PT: Retorna o valor duma comparacao do preco de dois imoveis. Se a quantidade for igual, retorna o resultado da funcao compare_id_property.
 */
int compare_price_property(Property prop1, Property prop2)
{
    if(prop1->price > prop2->price)
        return 1;
    if(prop1->price == prop2->price)
    {
        if (compare_id_property(prop1, prop2) == 1)
            return 1;
    }
    return 0;
}

/*
 * EN: Returns the result of the comparison of the area of two properties(lots only). If they're the same, returns the result of compare_id_property.
 * PT: Retorna o valor duma comparacao da area de dois imoveis(apenas terrenos). Se a quantidade for igual, retorna o resultado da funcao
 * compare_id_property.
 */
int compare_area_property(Property prop1, Property prop2)
{
    int comp = 0;
    if(identify_category(prop1) < 4 && identify_category(prop1) > 0)
    {
        if(identify_category(prop2) < 4 && identify_category(prop2) > 0)
        {
            comp = compare_area_category(&prop1->cat, &prop2->cat, identify_category(prop1), identify_category(prop2));
            if(comp == 2)
            {
                if(compare_id_property(prop1, prop2) == 1)
                    return 1;
                else
                    return 0;
            }
        }
    }
    return comp;
}

/*
 * EN: Returns 1 if the property is clayey, otherwise returns 0.
 * PT: Retorna 1 se o imovel e argiloso, caso contrario retorna 0.
 */
int check_if_property_clayey(Property prop)
{
    return check_if_clayey_category(&prop->cat, identify_category(prop));
}

/*
 * EN: Checks if house is above area_limit and if the price is under price_limit.
 * PT: Verifica se a casa esta acima de area_limit (limite de area) e se o preco esta abaxio de price_limit (limite do preco).
 */
int check_if_house_limit(Property prop, float price_limit, float area_limit)
{
    if(identify_category(prop) == 4)
    {
        if(check_if_house_limit_category(&prop->cat, identify_category(prop), area_limit))
        {
            if(prop->price < price_limit)
                return 1;
        }
    }

    return 0;
}

/*
 * EN: Returns the value of the property's id.
 * PT: Retorn o valor do id do imovel.
 */
unsigned int get_id(Property prop)
{
    return prop->id;
}

/*
 * EN: Shows property's id via printf.
 * PT: Apresenta o valor do id do imovel por printf.
 */
void print_id(Property prop)
{
    printf("%u", prop->id);
}


