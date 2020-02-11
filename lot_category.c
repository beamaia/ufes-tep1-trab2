#include "lot_category.h"
#include <stdio.h>
#include "triangle.h"
#include "rectangle.h"
#include "trapezoid.h"

/*
 * EN: Reads lot's based on its type (tag).
 * PT: Le o terreno de acordo com seu tipo;
 */
void read_lot_union(Lot_Union * lot, int tag, FILE * arc)
{
    switch (tag)
    {
        case 1:  read_triangle(&lot->tri, arc);
                 break;
        case 2:  read_rectangle(&lot->rec, arc);
                 break;
        case 3:  read_trapezoid(&lot->tra, arc);
                 break;
        default: return;
    }
}

/*
 * EN: Returns lot's area based on its type (tag).
 * PT: Retorna area do terreno de acordo com seu tipo.
 */
float area_lot_union(Lot_Union *lot, int tag)
{
    switch (tag)
    {
        case 1:  return area_triangle(&lot->tri);
        case 2:  return area_rectangle(&lot->rec);
        case 3:  return area_trapezoid(&lot->tra);
        default: return 0;
    }
}
