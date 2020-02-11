/*********************************************************************
 * TRAPEZOID.H
 * EN: Library with functions and struct related to the shape trapezoid.
 * PT: Biblioteca com funcoes e estruturas relacionada a forma trapezio.
 *********************************************************************/
#ifndef _TRAPEZOID
    #define _TRAPEZOID
    #include <stdio.h>

    /*
     * EN: Struct with information related to the shape trapezoid. Includes both of its bases and its height.
     * PT: Estrutura com informacoes relacionada a forma trapezoidal. Inclui ambos de suas bases mais sua altura.
     */
    typedef struct{
        float base1,
              base2,
              height;
    } Trapezoid;
    
    void read_trapezoid(Trapezoid *, FILE *);
    float area_trapezoid(Trapezoid *);
#endif