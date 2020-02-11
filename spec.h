#ifndef _SPEC
#define _SPEC
#include <stdio.h>

typedef struct{
    unsigned int percent_expensive,
                 prercent_clayey,
                 i,
                 j,
                 k;
    float area_limit,
          price_limit;
} Spec;

void read_spec(Spec *, FILE *);

typedef struct{
    unsigned int i, j, k;
} Identifiers;

void initialize_identifiers(Identifiers *);

#endif
