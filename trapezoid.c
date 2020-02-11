#include <stdio.h>
#include "trapezoid.h"

/*
 * EN: Reads bases and height of the trapezoid from a file.
 * PT: Le as bases e a altura do trapezio de um arquivo.
 */
void read_trapezoid(Trapezoid * tra, FILE * arc)
{
    fscanf(arc, "%f%*c%f%*c%f%*c%*c", &tra->base1, &tra->base2, &tra->height);
}

/*
 * EN: Returns the area of a trapezoid after calculating it.
 * PT: Retorna o valor da area de um retangulo apos o calcular.
 */
float area_trapezoid(Trapezoid *tra)
{
    return (float) ((tra->base1 + tra->base2) * tra->height / 2.0); // Casting float in case the multiplication is of double value
}