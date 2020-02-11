#include <stdio.h>
#include <stdlib.h>
#include "spec.h"
#include "catalog.h"
#include "properties.h"
#define MAX_PROP 50

/*
 * EN: Struct of a catalog of properties, with the quantity of how many properties there are and the max size of the vector (of properties).
 * PT: Estrutura dum catalogo de imoveis, com a quantidade de imoveis no catalogo e o tamanho maximo do vetor (de imoveis)
 */
struct catalog{
    Property *properties;
    int max_prop;
    int qt_prop;
};

/*
 * EN: Initializes the catalog by mallocing it and its vectors of properties, with the quantity of properties equal to 0 and the max size of the vector
 * equal to MAX_PROP.
 * PT: Inicializa o catalogo ao fazer malloc dele e do vetor de imoveis, com a quantidade propriedades igual a 0 e o tamanho max do vetor igual a MAX_PROP.
 */
Catalog initialize_catalog()
{
    Catalog c = (Catalog) malloc(sizeof(struct catalog));

    if(c == NULL)
    {
        printf("Error allocating memory");
        exit(1);
    }

    c->qt_prop = 0;
    c->max_prop = MAX_PROP;
    c->properties = (Property *) malloc(sizeof(Property) * c->max_prop);

    if(c->properties == NULL)
    {
        printf("Error allocating memory");
        exit(1);
    }

    return c;
}

/*
 * EN: Expands the size of the properties vector.
 * PT: Aumenta o tamanho do vetor de imoveis.
 */
void expand_catalog(Catalog c)
{
    c->max_prop += MAX_PROP;
    Property *aux = (Property *) malloc(sizeof(Property) * c->max_prop);

    if(aux == NULL)
    {
        printf("Error allocating memory");
        exit(1);
    }

    for(int i = 0; i < c->qt_prop; i++)
    {
        aux[i] = c->properties[i];
    }

    free(c->properties);
    c->properties = aux;
}

/*
 * EN: Reads catalog (file: catalogo.txt).
 * PT: Le catalogo (arquivo: catalogo.txt).
 */
void read_catalog(Catalog c, FILE * arc)
{
    while(!feof(arc))
    {
        if(c->qt_prop + 1 == c->max_prop)
            expand_catalog(c);

        c->properties[c->qt_prop] = initialize_property();
        if(read_property(c->properties[c->qt_prop], arc) && c->qt_prop < c->max_prop)
            c->qt_prop++;
        else
        {
            free(c->properties[c->qt_prop]);
            break;
        }
    }
}

/*
 * EN: Reads a property and afterwards includes it in the catalog.
 * PT: Le um imovel e depois o inclui ao catalogo.
 */
void include_in_catalog(Catalog c, FILE * arc)
{
    Property aux = initialize_property();
    read_property(aux, arc);
    if(c->qt_prop < c->max_prop)
        c->properties[c->qt_prop++] = aux;
}

/*
 * EN: Reads a property and afterwards finds a property with the same id in the catalog and changes its information.
 * PT: Le um imovel e depois encontra um imovel com o mesmo id no catalogo para altera suas informacoes.
 */
void modify_in_catalog(Catalog c, FILE * arc)
{
    Property aux = initialize_property();
    read_property(aux, arc);

    for(int i = 0; i < c->qt_prop; i++)
    {
        if(compare_id_property(c->properties[i], aux) == 2)
        {
            free_property(c->properties[i]);
            c->properties[i] = aux;
            return;
        }
    }
}

/*
 * EN: Reads an id and afterwards removes the property with the same id in the catalog. After removing it, shifts left the properties positioned after the
 * property that has been removed.
 * PT: Le um id e depois remove o imovel com o mesmo id no catalogo. Depois de o remover, desloca para a esquerda os imoveis posicionados
 * apos o imovel removido.
 */
void remove_from_catalog(Catalog c, FILE *arc)
{
    Property aux = initialize_property();
    read_property_to_be_removed(aux, arc);

    for(int i = 0; i < c->qt_prop && i < c->max_prop; i++)
    {
        if(compare_id_property(c->properties[i], aux) == 2)
        {
            free_property(c->properties[i]);
            free(aux);
            c->qt_prop--;
            for(int j = i; j < c->qt_prop && j < c->max_prop; j++)
            {
                c->properties[j] = c->properties[j + 1];
            }
            return;
        }
    }
}

/*
 * EN: Reads current information of the catalog (file: atual.txt), including, modifying or removing specific properties.
 * PT: Le a informacao atual dum catalogo (arquivo: atual.txt), incluindo, alterado ou excluindo imoveis especificos.
 */
void read_current(Catalog c, FILE * arc)
{
    char action;

    for(int i = 0; i < c->max_prop && !feof(arc); i++)
    {
        fscanf(arc, "%c%*c", &action);
        if(c->qt_prop == c->max_prop)
            expand_catalog(c);

        if(!feof(arc)) //In case the file is NULL and only after the use of fscanf that the value of feof is 1.
        {
            switch(action)
            {
                case 'i': include_in_catalog(c, arc);
                          break;
                case 'a': modify_in_catalog(c, arc);
                          break;
                case 'e': remove_from_catalog(c, arc);
                          break;
                default: return;
            }
        }
    }
}

/*
 * EN: Returns 1 if there are properties in the catalog.
 * PT: Retorna 1 se ha imoveis no catalogo.
 */
int are_there_properties(Catalog c)
{
    return c->qt_prop > 0;
}

/*
 * EN: Calculates the area of all properties.
 * PT: Calcula a area de todos imoveis.
 */
void area_catalog(Catalog c)
{
    for(int i = 0; i < c->qt_prop; i++)
    {
        area_property(c->properties[i]);
    }
}

/*
 * EN: Calculates the price of all properties.
 * PT: Calcula o preco de todos imoveis.
 */
void price_catalog(Catalog c)
{
    for(int i = 0; i < c->qt_prop; i++)
    {
        price_property(c->properties[i]);
    }
}

/*
 * EN: Calculates the area and price of all properties.
 * PT: Calcula a area e o preco de todos imoveis.
 */
void calculate_properties_information(Catalog properties)
{
    area_catalog(properties);
    price_catalog(properties);
}

/*
 * Bubble sort.
 */
void sort(Catalog c, int (*cmp)(Property, Property))
{
    Property aux;
    for(int i = 0; i < c->qt_prop - 1; i++)
    {
        for(int j = 0; j < c->qt_prop - i - 1; j++)
        {
            if((*cmp)(c->properties[j], c->properties[j + 1]))
            {
                aux = c->properties[j];
                c->properties[j] = c->properties[j + 1];
                c->properties[j + 1] = aux;
            }
        }
    }
}

/*
 * EN: Calculates how many clayey lots will be shown based on spec.
 * PT: Calcula quantos terrenos argiloso serao apresentados baseado no spec.
 */
int clayey_catalog_quantity(Catalog c, Spec *spec)
{
    return (int) spec->prercent_clayey * c->qt_prop / 100;
}

/*
 * EN: Calculates how many properties will be shown based on spec.
 * PT: Calcula quantos imoveis serao apresentados baseado no spec.
 */
int properties_catalog_quantity(Catalog c, Spec *spec)
{
    return (int) spec->percent_expensive * c->qt_prop / 100;
}

/*
 * EN: Creates catalog of clayey lots.
 * PT: Cria catalogo de terrenos argilosos.
 */
void create_clayey_catalog(Catalog src, Catalog dest)
{
    for(int i = 0; i < src->qt_prop; i++)
    {
        if(check_if_property_clayey(src->properties[i]))
        {
            dest->properties[dest->qt_prop] = src->properties[i];
            dest->qt_prop++;
        }
    }
}

/*
 * EN: Creates catalog of houses (with area and price in a certain limit).
 * PT: Cria catalogo de casas (coma area e preco dentro dum certo limite).
 */
void create_houses_catalog(Catalog src, Catalog dest, Spec *spec)
{
    for(int i = 0; i < src->qt_prop - 1; i++)
    {
        if(check_if_house_limit(src->properties[i], spec->price_limit, spec->area_limit))
            dest->properties[dest->qt_prop++] = src->properties[i];
    }
}

/*
 * EN: Sorts catalog by price. Find id (id->i) required by spec.
 * PT: Ordena catalogo por preco. Encontra id (id->i) requisitado pelo spec.
 */
void sort_most_expensive_catalog(Catalog c, Spec *spec, Identifiers *id)
{
    if(!c->qt_prop)
        return;

    sort(c, compare_price_property);
    int limit = properties_catalog_quantity(c, spec);
    if(!(spec->i > c->qt_prop || spec->i == 0))
        id->i = get_id(c->properties[spec->i - 1 + c->qt_prop - limit]);
}

/*
 * EN: Creates catalog of clayey lots and sorts it by area. Find id (id->j) required by spec.
 * PT: Cria catalogo de terrenos argilosos e ordena por area. Encontra id (id->j) requisitado pelo spec.
 */
void sort_creat_clayey_catalog(Catalog src, Catalog dest, Spec *spec, Identifiers *id)
{
    create_clayey_catalog(src, dest);
    if(!dest->qt_prop)
        return;

    sort(dest, compare_area_property);
    int limit = clayey_catalog_quantity(dest, spec);

    if(!(spec->j > dest->qt_prop || spec->j == 0))
        id->j = get_id(dest->properties[spec->j - 1 + dest->qt_prop - limit]);
}

/*
 * EN: Creates catalog of houses and sorts it by room quantity. Find id (id->k) required by spec.
 * PT: Cria catalogo de casas e ordena por quantidade de quartos. Encontra id (id->k) requisitado pelo spec.
 */
void sort_create_houses_catalog(Catalog src, Catalog dest, Spec *spec, Identifiers *id)
{
    create_houses_catalog(src, dest, spec);
    if(!dest->qt_prop)
        return;

    sort(dest, compare_room_property);

    if(!(spec->k > dest->qt_prop || spec->k == 0))
        id->k = get_id(dest->properties[spec->k - 1]);
}

/*
 * EN: Creates and sorts all catalogs.
 * PT: Cria e ordena todos catalogos.
 */
void sort_create_all_catalogs(Catalog properties, Catalog clayey, Catalog houses, Spec *spec, Identifiers *id)
{
    sort_creat_clayey_catalog(properties, clayey, spec, id);
    sort_create_houses_catalog(properties, houses, spec, id);
    sort_most_expensive_catalog(properties, spec, id);
}

/*
 * EN: Show ids of the most expesive properties in the catalog after a certain position (limit).
 * PT: Mostre o ids dos imoveis mais caros do catalogo depois duma dada posicao (limit).
 */
void print_id_expensive_or_clayey_properties(Catalog c, int limit)
{
    for(int i = c->qt_prop - limit ; i < c->qt_prop; i++)
    {
        print_id(c->properties[i]);
        if(i != c->qt_prop - 1)
            printf(", ");
    }
    if(c->qt_prop)
        printf("\n");
}

/*
 * EN: Show ids of the houses in the catalog.
 * PT: Mostre o ids das casas do catalogo.
 */
void print_limit_houses(Catalog c)
{
    for(int i = 0; i < c->qt_prop; i++)
    {
        print_id(c->properties[i]);
        if(i != c->qt_prop - 1)
            printf(", ");
    }
    if(c->qt_prop)
        printf("\n");
}

/*
 * EN: Show the sum of the Identifiers (i, j and k) and the ids of each catalog based on a certain restriction.
 * PT: Mostre a soma dos Identifiers (i, j e k) e os ids de cada catalogo baseado numa certa restricao.
 */
void print_id_catalogs(Catalog cat, Catalog clayey, Catalog house, Spec * spec, Identifiers * id)
{
    int sum = (int)(id->i + id->j + id->k);
    printf("%d\n", sum);
    print_id_expensive_or_clayey_properties(cat, properties_catalog_quantity(cat, spec));
    print_id_expensive_or_clayey_properties(clayey, clayey_catalog_quantity(clayey, spec));
    print_limit_houses(house);

}

/*
 * EN: Free all properties that were mallo'd.
 * PT: Libera todas as propriedades que foram mallocadas.
 */
void free_properties_informed(Catalog c)
{
    for(int i = 0; i < c->qt_prop; i++)
        free_property(c->properties[i]);

}

/*
 * EN: Free properties vector and catalog.
 * PT: Libera vetor de imoveis e catalogo.
 */
void free_catalog(Catalog c)
{
    free(c->properties);
    free(c);
}

/*
 * EN: Free all of the catalogs, except the main one (only it's properties are freed). The main catalog is later freed in main.c.
 * PT: Libera todos os catalogos, exceto o principal (apenas seus imoveis sao liberados). O catalogo principal e liberado na main.c.
 */
void free_catalogs_and_properties_used(Catalog main, Catalog second, Catalog third)
{
    free_properties_informed(main);
    free_catalog(second);
    free_catalog(third);
}