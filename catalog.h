#ifndef TRAB2EN_CATALOG_H
    #define TRAB2EN_CATALOG_H
    #include <stdio.h>
    #include "spec.h"
    #include "properties.h"
    #include "category.h"
    #include "lot.h"
    #include "lot_category.h"
    #include "triangle.h"
    #include "rectangle.h"
    #include "trapezoid.h"
    #include "house.h"
    #include "apt.h"

    typedef struct catalog * Catalog;

    Catalog initialize_catalog();
    void read_catalog(Catalog, FILE *);
    void expand_catalog(Catalog c);
    void include_in_catalog(Catalog, FILE *);
    void modify_in_catalog(Catalog, FILE *);
    void remove_from_catalog(Catalog, FILE *);
    void read_current(Catalog, FILE *);
    int are_there_properties(Catalog);
    void area_catalog(Catalog);
    void price_catalog(Catalog);
    void calculate_properties_information(Catalog);
    void sort(Catalog, int (*cmp)(Property, Property));
    int clayey_catalog_quantity(Catalog, Spec *);
    int properties_catalog_quantity(Catalog, Spec *);
    void create_clayey_catalog(Catalog, Catalog);
    void create_houses_catalog(Catalog, Catalog, Spec *);
    void sort_most_expensive_catalog(Catalog, Spec *, Identifiers *);
    void sort_creat_clayey_catalog(Catalog, Catalog, Spec *, Identifiers *);
    void sort_create_houses_catalog(Catalog, Catalog, Spec *, Identifiers *);
    void sort_create_all_catalogs(Catalog, Catalog, Catalog, Spec *, Identifiers *);
    void print_id_expensive_or_clayey_properties(Catalog, int);
    void print_limit_houses(Catalog);
    void print_id_catalogs(Catalog, Catalog, Catalog, Spec *, Identifiers *);
    void free_properties_informed(Catalog);
    void free_catalog(Catalog);
    void free_catalogs_and_properties_used(Catalog, Catalog, Catalog);

#endif
