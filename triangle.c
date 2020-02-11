#include <stdio.h>
#include "triangle.h"

/*
 * EN: Reads base and height of the triangle from a file.
 * PT: Le a base e a altura do triangulo de um arquivo.
 */
void read_triangle(Triangle *tri, FILE *arc)
{
    fscanf(arc,"%f%*c%f%*c%*c", &tri->base, &tri->height);
}

/*
 * EN: Returns the area of a triangle after calculating it.
 * PT: Retorna o valor da area de um triangulo apos o calcular.
 */
float area_triangle(Triangle *tri)
{
    return (float) (tri->base * tri->height / 2.0); // Casting float in case the multiplication is of double value
}
