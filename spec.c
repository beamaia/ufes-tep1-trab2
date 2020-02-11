#include <stdio.h>
#include "spec.h"

void read_spec(Spec *s, FILE *arc)
{
    fscanf(arc, "%u%u%f%f%u%u%u", &s->percent_expensive,
                                  &s->prercent_clayey,
                                  &s->area_limit,
                                  &s->price_limit,
                                  &s->i,
                                  &s->j,
                                  &s->k);
}

void initialize_identifiers(Identifiers *id)
{
    id->i = 0;
    id->j = 0;
    id->k = 0;
}