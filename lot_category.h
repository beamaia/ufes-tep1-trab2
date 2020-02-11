/*********************************************************************
 * LOT_CATEGORY.H
 * EN: Library with functions and struct related to the different types of lots.
 * PT: Biblioteca com funcoes e estruturas relacionada as formas diferentes de terrenos.
 *********************************************************************/
#ifndef _LOT_CATEGORY
    #define _LOT_CATEGORY
    #include <stdio.h>
    #include "triangle.h"
    #include "rectangle.h"
    #include "trapezoid.h"

    /*
     * EN: Union with information related to different types of lots. Includes lot of triangular, rectangular or trapezoidal shape.
     * PT: União com informacoes relacionada as formas diferentes de terrenos. Incluide terrenos de forma triangular, retangular ou trapezoidal.
     */
    typedef union {
        Triangle tri;
        Rectangle rec;
        Trapezoid tra;
    } Lot_Union;

    void read_lot_union(Lot_Union *, int, FILE *);
    float area_lot_union(Lot_Union *, int);
#endif