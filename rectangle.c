#include <stdio.h>
#include "rectangle.h"

/*
 * EN: Reads sides (length and height) of the rectangle from a file.
 * PT: Le lados (comprimento e altura) do retangulo de um arquivo.
 */
void read_rectangle(Rectangle * rec, FILE *arc)
{
    fscanf(arc, "%f%*c%f%*c%*c", &rec->side1, &rec->side2);
}

/*
 * EN: Returns the area of a rectangle after calculating it.
 * PT: Retorna o valor da area de um retangulo apos o calcular.
 */
float area_rectangle(Rectangle * rec)
{
    return rec->side1 * rec->side2;  // Casting float in case the multiplication is of double value
}