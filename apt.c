#include <stdio.h>
#include "apt.h"

/*
 * EN: Read apartment's information from a file.
 * PT: Le informacao do apartmento de um arquivo.
 */
void read_apartment(Apartment *apt, FILE *arc)
{
    fscanf(arc, "%u%*c%u%*c%u%*c%f%*c%u%*c%c%*c%u%*c%*c", &apt->rooms,
                                                          &apt->parking,
                                                          &apt->floor,
                                                          &apt->area,
                                                          &apt->m2_price,
                                                          &apt->leisure_area,
                                                          &apt->max_floor);

}

/*
 * EN: Returns apartment's price after calculating it.
 * PT: Retorna o preco do apartamento depois de o calcular.
 */
float price_apartment(Apartment *apt)
{
    float leisure = 1;
    if(apt->leisure_area == 'S')
        leisure = 1.15;

    return (float) ((float) apt->m2_price * apt->area *(0.9 + (float) apt->floor/ apt->max_floor) * leisure);
}