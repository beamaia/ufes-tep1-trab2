#include <stdio.h>
#include "lot.h"
#include "lot_category.h"

/*
 * EN: Read lot's information from a file.
 * PT: Le informacao do terreno de um arquivo.
 */
void read_lot(Lot *lot, int tag, FILE *arc)
{
    fscanf(arc, "%c%u", &lot->soil_type,
                   &lot->price_m2);

    read_lot_union(&lot->lot, tag, arc);
}

/*
 * EN: Obtain lot area.
 * PT: Obtem a area do terreno.
 */
void area_lot(Lot *lot, int tag)
{
    lot->area = area_lot_union(&lot->lot, tag);
}

/*
 * EN: Returns lot price after it calculates it.
 * PT: Retorna valor do terreno apos o calcular.
 */
float price_lot(Lot *lot)
{
    switch (lot->soil_type)
    {
        case 'A': return (float) (0.9 * lot->area * lot->price_m2);
        case 'G': return (float) (1.3 * lot->area * lot->price_m2);
        case 'R': return (float) (1.1 * lot->area * lot->price_m2);
        default:  return 0;
    }
}

/*
 * EN: Returns true or false (1 or 0) whether the lot is clayey.
 * PT: Retorna verdade ou falso (1 ou 0) caso o terreno e argiloso.
 */
int is_lot_clayey(Lot * lot)
{
    if(lot->soil_type == 'G')
        return 1;
    return 0;
}

/*
 * EN: Compares area of two lots, returns 1 if lot1's area is smaller than lot2's area, 2 if they're the same, 0 if it's bigger.
 * PT: Compara a area de dois terrenos, retorna 1 se a area do lot1 e menor que a area do lot2, 2 se sao iguais, 0 se e maior.
 */
int compare_area_lot(Lot *lot1, Lot *lot2)
{
    if(lot1->area < lot2->area)
        return 1;
    if(lot1->area == lot2->area)
        return 2;
    return 0;
}