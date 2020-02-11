/*********************************************************************
 * TRIANGLE.H
 * EN: Library with functions and structs related to the shape triangle.
 * PT: Biblioteca com funcoes e estruturas relacionada a forma triangulo.
 *********************************************************************/
#ifndef _TRIANGLE
    #define _TRIANGLE
    #include <stdio.h>

    /*
     * EN: Struct with information related to the shape triangle. Includes its base and height.
     * PT: Estrutura com informacoes relacionada a forma triangular. Inclui sua base e altura.
     */
    typedef struct{
        float base,
              height;
    } Triangle;

    void read_triangle(Triangle *, FILE *);
    float area_triangle(Triangle *);
#endif