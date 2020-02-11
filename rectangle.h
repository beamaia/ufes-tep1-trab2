/*********************************************************************
 * RECTANGLE.H
 * EN: Library with functions and struct related to the shape rectangle.
 * PT: Biblioteca com funcoes e estruturas relacionada a forma rectangle.
 *********************************************************************/
#ifndef _RECTANGLE
    #define _RECTANGLE
    #include <stdio.h>

    /*
     * EN: Struct with information related to the shape rectangle. Includes both of its sides.
     * PT: Estrutura com informacoes relacionada a forma retangular. Inclui ambos dos seus lados.
     */
    typedef struct{
        float side1,
              side2;
    } Rectangle;

    void read_rectangle(Rectangle *, FILE *);
    float area_rectangle(Rectangle *);
#endif